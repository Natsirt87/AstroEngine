#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(EntityManager* entityMgr) 
	: Entity(entityMgr), rigidbody(entityMgr->GetContext()->m_world, this)
{ 
	m_type = EntityType::PhysicsObject; 
	rigidbody.RegisterCollisionFunctions(
		&PhysicsEntity::PhysicsCollisionStart, 
		&PhysicsEntity::PhysicsCollisionEnd, this);
}

PhysicsEntity::~PhysicsEntity()
{}

float PhysicsEntity::GetAngle()
{
	return rigidbody.GetAngle();
}

void PhysicsEntity::SetPosition(float x, float y)
{
	rigidbody.SetPosition(x, y);
}

void PhysicsEntity::SetPosition(const sf::Vector2f& pos)
{
	rigidbody.SetPosition(pos);
}

void PhysicsEntity::SetAngle(float angle)
{
	rigidbody.SetAngle(angle);
}

void PhysicsEntity::SetVelocity(float x, float y)
{
	rigidbody.SetVelocity(x, y);
}

void PhysicsEntity::Update(float dt)
{
	m_position = rigidbody.GetPosition();
	m_velocity = rigidbody.GetVelocity();
	updateAABB();
}
