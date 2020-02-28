#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(EntityManager* entityMgr) 
	: BaseEntity(entityMgr), physicsBody(entityMgr->GetContext()->m_world)
{ m_type = EntityType::PhysicsObject; }

PhysicsEntity::~PhysicsEntity()
{}

float PhysicsEntity::GetAngle()
{
	return physicsBody.GetAngle();
}

void PhysicsEntity::SetPosition(float x, float y)
{
	physicsBody.SetPosition(x, y);
}

void PhysicsEntity::SetPosition(const sf::Vector2f& pos)
{
	physicsBody.SetPosition(pos);
}

void PhysicsEntity::SetAngle(float angle)
{
	physicsBody.SetAngle(angle);
}

void PhysicsEntity::SetVelocity(float x, float y)
{
	physicsBody.SetVelocity(x, y);
}

void PhysicsEntity::Update(float dt)
{
	m_position = physicsBody.GetPosition();
	m_velocity = physicsBody.GetVelocity();
	
	updateAABB();
}
