#include "State_Game.h"
#include "PhysicsBox.h"
#include "TestShip.h"
#include "Box2D/Common/b2Draw.h"

State_Game::State_Game(StateManager* stateManager)
	: BaseState(stateManager),
	m_backTex(new sf::Texture()),
	m_debugDraw(*m_stateMgr->GetContext()->m_wind->GetRenderWindow()),
	m_world(nullptr), m_ship(nullptr), m_player(nullptr), m_debugDrawMode(false) {}

State_Game::~State_Game() {}

void State_Game::OnCreate()
{
	m_world = m_stateMgr->GetContext()->m_world;
	m_world->SetDebugDraw(&m_debugDraw);
	m_debugDraw.SetFlags(b2Draw::e_shapeBit);

	TextureManager* texMgr = m_stateMgr->GetContext()->m_textureManager;
	EntityManager* entityMgr = m_stateMgr->GetContext()->m_entityManager;
	sf::Vector2u windowSize = m_stateMgr->GetContext()->
		m_wind->GetRenderWindow()->getSize();

	m_view.setSize(windowSize.x, windowSize.y);
	m_view.setCenter(windowSize.x / 2.f, windowSize.y / 2.f);

	entityMgr->Add(EntityType::Player, "Playerboi", true);
	m_ship = (TestShip*)entityMgr->Find("Playerboi");
	m_ship->SetPosition(windowSize.x / 2.f, windowSize.y / 2.f);

	for (int i = 0; i < 256; i++)
	{
		entityMgr->Add(EntityType::PhysicsObject, "Box" + std::to_string(i), false);
		PhysicsBox* box = (PhysicsBox*)entityMgr->Find("Box" + std::to_string(i));

		float boxLengthX = rand() % 200 + 20;
		float boxLengthY = rand() % 300 + 20;

		int rowSize = 20;
		float boxPosX = (i % rowSize) * 500 - 3500;
		float boxPosY = (i / rowSize) * 500 - 5500;

		float boxVelocityX = rand() % 300 + 30;
		float boxVelocityY = rand() % 300 + 30;
		
		box->Create(boxLengthX, boxLengthY);
		box->SetPosition(boxPosX, boxPosY);
		box->SetVelocity(boxVelocityX, boxVelocityY);
	}

	if (texMgr->RequireResource("FNebula2")) { m_backTex = texMgr->GetResource("FNebula2"); }
	m_backTex->setSmooth(false);
	m_background.setTexture(*m_backTex);
	m_background.setScale(3, 3);
	m_background.setOrigin(m_backTex->getSize().x / 2.f, m_backTex->getSize().y / 2.f);

	EventManager* eventMgr = m_stateMgr->GetContext()->m_eventManager;
	eventMgr->AddCallback(StateType::Game, "Game_Pause", &State_Game::Pause, this);
	eventMgr->AddCallback(StateType::Game, "Game_MenuReturn", &State_Game::MainMenu, this);
	eventMgr->AddCallback(StateType::Game, "Game_Zoom", &State_Game::zoom, this);
	eventMgr->AddCallback(StateType::Game, "Game_ToggleDebug", &State_Game::toggleDebug, this);
}

void State_Game::OnDestroy()
{
	EventManager* eventMgr = m_stateMgr->GetContext()->m_eventManager;
	eventMgr->RemoveCallback(StateType::Game, "Game_Pause");
	eventMgr->RemoveCallback(StateType::Game, "Game_MenuReturn");
	eventMgr->RemoveCallback(StateType::Game, "Game_Zoom");
	eventMgr->RemoveCallback(StateType::Game, "Game_ToggleDebug");
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
	m_world->Step(dt, 8, 3, m_taskExecutor);
}

void State_Game::Draw()
{
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	window->draw(m_background);
	m_stateMgr->GetContext()->m_entityManager->Draw();
	
	if (m_debugDrawMode) m_world->DrawDebugData();
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

void State_Game::toggleDebug(EventDetails* details)
{
	m_debugDrawMode = !m_debugDrawMode;
}
