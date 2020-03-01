#include "TestShip.h"
#include "StateManager.h"

TestShip::TestShip(EntityManager* entityMgr) 
	: PhysicsEntity(entityMgr),
	m_spriteSheet(m_entityMgr->GetContext()->m_textureManager, this),
	thrustForce(200),
	rotationTorque(150)
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

void TestShip::PhysicsCollisionStart(Entity* other)
{
}

void TestShip::PhysicsCollisionEnd(Entity* other)
{
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

void TestShip::OnKinematicCollision(Entity* other)
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

	b2Vec2 hullPoints[7] =
	{
		b2Vec2(0, -53),
		b2Vec2(12, -47),
		b2Vec2(12, 22),
		b2Vec2(16, 36),
		b2Vec2(-16, 36),
		b2Vec2(12, -22),
		b2Vec2(-12, -47)
	};
	b2Fixture* hullFixture = rigidbody.AddPolygon(hullPoints, 7);
	
	b2Vec2 wingPoints[4] =
	{
		b2Vec2(-12, -14),
		b2Vec2(-67, -1),
		b2Vec2(-75, 17),
		b2Vec2(-12, 12)
	};
	b2Fixture* wingLFixture = rigidbody.AddPolygon(wingPoints, 4);

	wingPoints[0] = b2Vec2(12, -14);
	wingPoints[1] = b2Vec2(67, -1);
	wingPoints[2] = b2Vec2(75, 17);
	wingPoints[3] = b2Vec2(12, 12);
	b2Fixture* wingRFixture = rigidbody.AddPolygon(wingPoints, 4);

	hullFixture->SetDensity(20);
	wingLFixture->SetDensity(20);
	wingRFixture->SetDensity(20);
	rigidbody.ResetMassData();
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

		float fx = cos(conv::DTR(GetAngle() - 90)) * thrustForce;
		float fy = sin(conv::DTR(GetAngle() - 90)) * thrustForce;

		rigidbody.ApplyForceToCenter(sf::Vector2f(fx, fy));
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

	float desiredAngle = conv::RTD(atan2f(dy, dx)) + 90;

	if (desiredAngle < 0)
	{
		desiredAngle = fmod(desiredAngle, 360);
		while (desiredAngle < 0)
		{
			desiredAngle += 360.0;
		}
	}

	float bodyAngle = rigidbody.GetAngle();
	float nextAngle = bodyAngle + rigidbody.GetAngularVelocity() / 4.0;
	float totalRotation = desiredAngle - nextAngle;

	while (totalRotation < -180) totalRotation += 360;
	while (totalRotation > 180) totalRotation -= 360;
	
	float torque = totalRotation < 0 ? -rotationTorque : rotationTorque;
	rigidbody.ApplyTorque(torque);
}