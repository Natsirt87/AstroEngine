#include "PhysicsBox.h"

PhysicsBox::PhysicsBox(EntityManager* entityMgr)
	: PhysicsEntity(entityMgr), m_rect(new sf::RectangleShape(sf::Vector2f(5, 5)))
{
	m_name = "PhysicsBox";
}

PhysicsBox::~PhysicsBox()
{
	delete m_rect;
}

void PhysicsBox::Create(float sizeX, float sizeY)
{
	m_rect->setOrigin(sizeX / 2.f, sizeY / 2.f);
	m_rect->setSize(sf::Vector2f(sizeX, sizeY));
	boxFixture = rigidbody.AddBox(sizeX, sizeY, b2Vec2(0, 0), 0);
	boxFixture->SetDensity((sizeX * sizeY) / 20);
	rigidbody.ResetMassData();

	SetSize(sizeX, sizeY);
}

void PhysicsBox::PhysicsCollisionStart(Entity* other)
{
	
}

void PhysicsBox::PhysicsCollisionEnd(Entity* other)
{
}

void PhysicsBox::Update(float dt)
{
	PhysicsEntity::Update(dt);
	m_rect->setPosition(m_position);
	m_rect->setRotation(GetAngle());
}

void PhysicsBox::Draw(sf::RenderWindow* wind)
{
	wind->draw(*m_rect);
}

void PhysicsBox::OnKinematicCollision(Entity* other)
{
	//std::cout << "Matthew is gay" << std::endl;
}
