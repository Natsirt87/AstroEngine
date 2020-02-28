#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(EntityManager* entityMgr) 
	: BaseEntity(entityMgr)
{
	m_type = EntityType::PhysicsObject;
	m_world = m_entityMgr->GetContext()->m_world;

	m_bodyDef.type = b2BodyType::b2_dynamicBody;
	m_bodyDef.position.Set(0, 0);
	m_bodyDef.angle = 0;
	m_body = m_world->CreateBody(&m_bodyDef);
}

PhysicsEntity::~PhysicsEntity()
{
	m_world->DestroyBody(m_body);
}

float PhysicsEntity::GetAngle()
{
	return conv::RTD(m_body->GetAngle());
}

void PhysicsEntity::SetPosition(float x, float y)
{
	m_body->SetTransform(b2Vec2(conv::PTM(x), conv::PTM(y)), m_body->GetAngle());
}

void PhysicsEntity::SetPosition(const sf::Vector2f& pos)
{
	m_body->SetTransform(b2Vec2(conv::PTM(pos.x), conv::PTM(pos.y)), m_body->GetAngle());
}

void PhysicsEntity::SetAngle(float angle)
{
	m_body->SetTransform(m_body->GetPosition(), conv::DTR(angle));
}

void PhysicsEntity::Move(float x, float y)
{
	m_positionOld = m_position;
	m_position += sf::Vector2f(x, y);
	m_body->SetTransform(b2Vec2(conv::PTM(m_position.x), conv::PTM(m_position.y)), m_body->GetAngle());
}

void PhysicsEntity::SetVelocity(float x, float y)
{
	m_body->SetLinearVelocity(b2Vec2(conv::PTM(x), conv::PTM(y)));
}

void PhysicsEntity::AddVelocity(float x, float y)
{
	m_velocity += sf::Vector2f(x, y);
	m_body->SetLinearVelocity(b2Vec2(conv::PTM(m_velocity.x), conv::PTM(m_velocity.y)));
}

void PhysicsEntity::ApplyAngularImpulse(float impulse)
{
	m_body->ApplyAngularImpulse(impulse, true);
}

 void PhysicsEntity::ApplyForce(const sf::Vector2f& force, const sf::Vector2f& point)
{
	 b2Vec2 f(force.x, force.y);
	 b2Vec2 p(point.x, point.y);
	 m_body->ApplyForce(f, p, true);
}

 void PhysicsEntity::ApplyForceToCenter(const sf::Vector2f& force)
 {
	 m_body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
 }

 void PhysicsEntity::ApplyLinearImpulse(const sf::Vector2f& impulse, const sf::Vector2f& point)
 {
	 b2Vec2 i(impulse.x, impulse.y);
	 b2Vec2 p(point.x, point.y);
	 m_body->ApplyLinearImpulse(i, p, true);
 }

 void PhysicsEntity::ApplyLinearImpulseToCenter(const sf::Vector2f& impulse)
 {
	 m_body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), true);
 }

 void PhysicsEntity::ApplyTorque(float torque)
 {
	 m_body->ApplyTorque(torque, true);
 }

void PhysicsEntity::Update(float dt)
{
	m_position = sf::Vector2f(conv::MTP(m_body->GetPosition().x), conv::MTP(m_body->GetPosition().y));
	m_velocity = sf::Vector2f(conv::MTP(m_body->GetLinearVelocity().x), conv::MTP(m_body->GetLinearVelocity().y));
	
	updateAABB();
}
