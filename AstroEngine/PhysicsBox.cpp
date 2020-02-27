#include "PhysicsBox.h"

PhysicsBox::PhysicsBox(EntityManager* entityMgr)
	: PhysicsEntity(entityMgr), m_rect(sf::Vector2f(5, 5))
{
	m_name = "PhysicsBox";
}

PhysicsBox::~PhysicsBox()
{
	m_world->DestroyBody(m_body);
}

void PhysicsBox::Create(float sizeX, float sizeY)
{
	m_rect.setOrigin(sizeX / 2.f, sizeY / 2.f);
	m_rect.setSize(sf::Vector2f(sizeX, sizeY));
	m_boxShape.SetAsBox(conv::PTM(sizeX) / 2.f, conv::PTM(sizeY) / 2.f);
	m_fixtureDef.shape = &m_boxShape;
	m_fixtureDef.density = 200;
	m_body->CreateFixture(&m_fixtureDef);

	b2CircleShape circle;

	SetSize(sizeX, sizeY);
}

void PhysicsBox::Update(float dt)
{
	PhysicsEntity::Update(dt);
	m_rect.setPosition(m_position);
	m_rect.setRotation(GetAngle());
}

void PhysicsBox::Draw(sf::RenderWindow* wind)
{
	wind->draw(m_rect);
}

void PhysicsBox::OnEntityCollision(BaseEntity* other)
{
	//std::cout << "Non phyics overlap isn't cool enough for this physics object" << std::endl;
}
