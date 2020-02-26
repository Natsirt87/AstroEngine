#include "State_Game.h"
#include "PhysicsBox.h"
#include "TestShip.h"

State_Game::State_Game(StateManager* stateManager)
	: BaseState(stateManager),
	m_backTex(new sf::Texture()) {}

State_Game::~State_Game() {}

void State_Game::OnCreate()
{
	m_world = m_stateMgr->GetContext()->m_world;

	TextureManager* texMgr = m_stateMgr->GetContext()->m_textureManager;
	EntityManager* entityMgr = m_stateMgr->GetContext()->m_entityManager;
	sf::Vector2u windowSize = m_stateMgr->GetContext()->
		m_wind->GetRenderWindow()->getSize();

	m_view.setSize(windowSize.x, windowSize.y);
	m_view.setCenter(windowSize.x / 2.f, windowSize.y / 2.f);

	entityMgr->Add(EntityType::Player, "Playerboi");
	m_ship = (TestShip*)entityMgr->Find("Playerboi");
	m_ship->SetPosition(windowSize.x / 2.f, windowSize.y / 2.f);

	entityMgr->Add(EntityType::PhysicsObject, "Box1");
	entityMgr->Add(EntityType::PhysicsObject, "Box2");
	entityMgr->Add(EntityType::PhysicsObject, "Box3");
	entityMgr->Add(EntityType::PhysicsObject, "Box4");
	PhysicsBox* box1 = (PhysicsBox*)entityMgr->Find("Box1");
	PhysicsBox* box2 = (PhysicsBox*)entityMgr->Find("Box2");
	PhysicsBox* box3 = (PhysicsBox*)entityMgr->Find("Box3");
	PhysicsBox* box4 = (PhysicsBox*)entityMgr->Find("Box4");
	box1->Create(50, 100);
	box2->Create(100, 70);
	box3->Create(20, 10);
	box4->Create(30, 100);
	box1->SetPosition(windowSize.x / 2.f - 500, windowSize.y / 2.f);
	box2->SetPosition(windowSize.x / 2.f + 500, windowSize.y / 2.f);
	box3->SetPosition(windowSize.x / 2.f, windowSize.y / 2.f + 500);
	box4->SetPosition(windowSize.x / 2.f, windowSize.y / 2.f - 500);
	box1->SetVelocity(100, 0);
	box2->SetVelocity(-100, 0);
	box3->SetVelocity(0, -100);
	box4->SetVelocity(0, 100);

	if (texMgr->RequireResource("FNebula2")) { m_backTex = texMgr->GetResource("FNebula2"); }
	m_backTex->setSmooth(false);
	m_background.setTexture(*m_backTex);
	m_background.setScale(3, 3);
	m_background.setOrigin(m_backTex->getSize().x / 2.f, m_backTex->getSize().y / 2.f);

	EventManager* eventMgr = m_stateMgr->GetContext()->m_eventManager;
	eventMgr->AddCallback(StateType::Game, "Game_Pause", &State_Game::Pause, this);
	eventMgr->AddCallback(StateType::Game, "Game_MenuReturn", &State_Game::MainMenu, this);
	eventMgr->AddCallback(StateType::Game, "Game_Zoom", &State_Game::zoom, this);
}

void State_Game::OnDestroy()
{
	EventManager* eventMgr = m_stateMgr->GetContext()->m_eventManager;
	eventMgr->RemoveCallback(StateType::Game, "Game_Pause");
	eventMgr->RemoveCallback(StateType::Game, "Game_MenuReturn");
	eventMgr->RemoveCallback(StateType::Game, "Game_Zoom");
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}

void State_Game::Update(const sf::Time& time)
{
	const float dt = time.asSeconds();
	m_stateMgr->GetContext()->m_entityManager->Update(dt);

	m_view.setCenter(m_ship->GetPosition());
	m_stateMgr->GetContext()->m_wind->GetRenderWindow()->setView(m_view);
	m_background.setPosition(m_ship->GetPosition());
	m_world->Step(dt, 8, 3);
}

void State_Game::Draw()
{
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	window->draw(m_background);
	m_stateMgr->GetContext()->m_entityManager->Draw();
}

void State_Game::MainMenu(EventDetails* details)
{
	m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails* details)
{
	m_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game::zoom(EventDetails* details)
{
	if (details->m_mouseWheelDelta < 0) { m_view.zoom(1.05); m_background.scale(sf::Vector2f(1.04, 1.04));  }
	else { m_view.zoom(0.95); m_background.scale(sf::Vector2f(0.96, 0.96)); }
}
