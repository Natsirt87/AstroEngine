#include "TestShip.h"
#include "StateManager.h"

TestShip::TestShip(EntityManager* entityMgr) 
	: PhysicsEntity(entityMgr),
	m_spriteSheet(m_entityMgr->GetContext()->m_textureManager)
{
	spriteSheetSetup();
	physicsSetup();

	EventManager* eventMgr = m_entityMgr->GetContext()->m_eventManager;
	eventMgr->AddCallback(StateType::Game, "Game_StartThrust", &TestShip::thrust, this);
	eventMgr->AddCallback(StateType::Game, "Game_StopThrust", &TestShip::thrust, this);
}

TestShip::~TestShip()
{
	EventManager* eventMgr = m_entityMgr->GetContext()->m_eventManager;
	eventMgr->RemoveCallback(StateType::Game, "Game_StartThrust");
	eventMgr->RemoveCallback(StateType::Game, "Game_StopThrust");
}

void TestShip::Update(float dt)
{
	PhysicsEntity::Update(dt);
	rotateToMouse();
	m_spriteSheet.Update(dt);
	m_spriteSheet.SetSpritePosition(m_position);
	m_spriteSheet.SetSpriteRotation(GetAngle());
	
	animate();
}

void TestShip::Draw(sf::RenderWindow* wind)
{
	m_spriteSheet.Draw(wind);
}

void TestShip::OnEntityCollision(BaseEntity* other)
{
}

void TestShip::spriteSheetSetup()
{
	m_name = "TestShip";
	m_spriteSheet.LoadSheet("Data/SpriteSheets/PlaceholderShip.sheet");
	m_spriteSheet.SetAnimation("Idle", false, false);
	SetSize(m_spriteSheet.GetSpriteSize().x, m_spriteSheet.GetSpriteSize().y);

	animState = AnimState::Idle;
}

void TestShip::physicsSetup()
{
	sf::Vector2i size = m_spriteSheet.GetSpriteSize();
	boxFixture = physicsBody.AddBox(size.x, size.y, b2Vec2(0, 0), 0);
}

void TestShip::animate()
{
	if (animState == AnimState::Thrusting)
	{
		if (m_spriteSheet.GetCurrentAnim()->GetName() != "Idle")
		{ return; }
		m_spriteSheet.SetAnimation("StartThrust", true, true, "Thrust");
	}
	else
	{
		if (m_spriteSheet.GetCurrentAnim()->GetName() != "Thrust")
		{ return; }
		m_spriteSheet.SetAnimation("StopThrust", true, false, "Idle");
	}
}

void TestShip::thrust(EventDetails* details)
{
	if (details->m_name == "Game_StartThrust")
	{
		animState = AnimState::Thrusting;

		float fx = cos(conv::DTR(GetAngle() - 90)) * 50;
		float fy = sin(conv::DTR(GetAngle() - 90)) * 50;

		physicsBody.ApplyForceToCenter(sf::Vector2f(fx, fy));
	}
	else
	{
		animState = AnimState::Idle;
	}
}

void TestShip::rotateToMouse()
{
	sf::Window* window = m_entityMgr->GetContext()->m_wind->GetRenderWindow();
	sf::Vector2u windowSize = window->getSize();
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

	float dx = mousePos.x - windowSize.x/2.f;
	float dy = mousePos.y - windowSize.y/2.f;

	SetAngle(conv::RTD(atan2f(dy, dx)) + 90);
}
