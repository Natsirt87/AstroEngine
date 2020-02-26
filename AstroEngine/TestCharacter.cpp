#include "TestCharacter.h"
#include "EntityManager.h"

TestCharacter::TestCharacter(EntityManager* entityMgr) 
	:BaseEntity(entityMgr),
	m_spriteSheet(m_entityMgr->GetContext()->m_textureManager)
{
	m_name = "TestCharacter";
	m_spriteSheet.LoadSheet("Data/SpriteSheets/PlaceholderShip.sheet");
	m_spriteSheet.SetAnimation("Idle", false, false);
	SetSize(m_spriteSheet.GetSpriteSize().x, m_spriteSheet.GetSpriteSize().y);

	EventManager* eventMgr = m_entityMgr->GetContext()->m_eventManager;
	eventMgr->AddCallback(StateType::Game, "Game_StartThrust", &TestCharacter::thrust, this);
	eventMgr->AddCallback(StateType::Game, "Game_StopThrust", &TestCharacter::thrust, this);
}

TestCharacter::~TestCharacter() 
{
	EventManager* eventMgr = m_entityMgr->GetContext()->m_eventManager;
	eventMgr->RemoveCallback(StateType::Game, "Game_StartThrust");
	eventMgr->RemoveCallback(StateType::Game, "Game_StopThrust");
}

float TestCharacter::GetAngle() { return m_angle; }

void TestCharacter::SetAngle(float angle) { m_angle = angle; }

void TestCharacter::thrust(EventDetails* details)
{
	if (details->m_name == "Game_StartThrust")
	{
		if (m_spriteSheet.GetCurrentAnim()->GetName() != "Idle")
		{ return; }

		m_spriteSheet.SetAnimation("StartThrust", true, true, "Thrust");
		
	}
	else
	{
		m_spriteSheet.SetAnimation("StopThrust", true, false, "Idle");
	}
}

void TestCharacter::doAngle()
{
	sf::Window* window = m_entityMgr->GetContext()->m_wind->GetRenderWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

	float dx = mousePos.x - m_spriteSheet.GetSpritePosition().x;
	float dy = mousePos.y - m_spriteSheet.GetSpritePosition().y;

	SetAngle(atan2(dy, dx) * 57.2958 + 90);
}

void TestCharacter::OnEntityCollision(BaseEntity* other)
{
	std::cout << m_name << " overlapped with " << other->GetName() << std::endl;
}

void TestCharacter::Update(float dt)
{
	BaseEntity::Update(dt);
	m_spriteSheet.Update(dt);

	doAngle();

	m_spriteSheet.SetSpritePosition(m_position);
	m_spriteSheet.SetSpriteRotation(m_angle);
}

void TestCharacter::Draw(sf::RenderWindow* wind)
{
	m_spriteSheet.Draw(wind);
}