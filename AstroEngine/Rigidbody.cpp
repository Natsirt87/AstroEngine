#include "Rigidbody.h"

Rigidbody::Rigidbody(b2World* world, Entity* owner) 
	: BaseComponent(owner), m_world(world)
{
	m_bodyDef.type = b2BodyType::b2_dynamicBody;
	m_bodyDef.position.Set(0, 0);
	m_bodyDef.fixedRotation = false;
	m_bodyDef.angle = 0;
	m_body = m_world->CreateBody(&m_bodyDef);
	m_body->SetUserData(this);
}

Rigidbody::~Rigidbody()
{
	m_world->DestroyBody(m_body);
	m_colliders.clear();
	m_colliders.shrink_to_fit();
}

b2Fixture* Rigidbody::AddBox(float sizeX, float sizeY, const b2Vec2& offset, float angle)
{
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	b2PolygonShape* shape = new b2PolygonShape();

	float b2SizeX = conv::PTM(sizeX);
	float b2SizeY = conv::PTM(sizeY);
	float b2Angle = conv::DTR(angle);
	b2Vec2 b2Offset(conv::PTM(offset.x), conv::PTM(offset.y));

	shape->SetAsBox(b2SizeX / 2.0, b2SizeY / 2.0, b2Offset, angle);
	fixtureDef->shape = shape;
	fixtureDef->density = 1;
	fixtureDef->friction = 0.5;
	m_colliders.emplace_back(fixtureDef, shape);
	

	return m_body->CreateFixture(fixtureDef);
}

b2Fixture* Rigidbody::AddPolygon(b2Vec2* points, int32 count)
{
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	b2PolygonShape* shape = new b2PolygonShape();

	for (int i = 0; i < count; i++)
	{
		b2Vec2 p = points[i];
		points[i] = b2Vec2(conv::PTM(p.x), conv::PTM(p.y));
	}

	shape->Set(points, count);
	fixtureDef->shape = shape;
	fixtureDef->density = 1;
	fixtureDef->friction = 0.5;
	m_colliders.emplace_back(fixtureDef, shape);

	return m_body->CreateFixture(fixtureDef);
}

b2Fixture* Rigidbody::AddCircle(float radius, const b2Vec2& offset)
{
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	b2CircleShape* shape = new b2CircleShape();
	b2Vec2 b2Offset(conv::PTM(offset.x), conv::PTM(offset.y));

	shape->m_radius = conv::PTM(radius);
	shape->m_p = b2Offset;
	fixtureDef->shape = shape;
	fixtureDef->density = 1;
	fixtureDef->friction = 0.5;
	m_colliders.emplace_back(fixtureDef, shape);

	return m_body->CreateFixture(fixtureDef);
}

void Rigidbody::RemoveCollider(b2Fixture* fixture)
{
	m_body->DestroyFixture(fixture);
}

void Rigidbody::OnCollisionStart(Rigidbody* other)
{
	if (m_collisionStart != nullptr)
	{
		Entity* otherEntity = other->GetOwner();
		m_collisionStart(otherEntity);
	}
}

void Rigidbody::OnCollisionEnd(Rigidbody* other)
{
	if (m_collisionEnd != nullptr)
	{
		Entity* otherEntity = other->GetOwner();
		m_collisionEnd(otherEntity);
	}
}

const sf::Vector2f& Rigidbody::GetPosition()
{
	return sf::Vector2f(conv::MTP(m_body->GetPosition().x), conv::MTP(m_body->GetPosition().y));
}

const sf::Vector2f& Rigidbody::GetVelocity()
{
	return sf::Vector2f(conv::MTP(m_body->GetLinearVelocity().x), conv::MTP(m_body->GetLinearVelocity().y));
}

float Rigidbody::GetAngularVelocity()
{
	return conv::MTP(m_body->GetAngularVelocity());
}

float Rigidbody::GetInertia()
{
	return m_body->GetInertia();
}

float Rigidbody::GetAngle()
{
	return conv::RTD(m_body->GetAngle());
}

void Rigidbody::SetPosition(float x, float y)
{
	m_body->SetTransform(b2Vec2(conv::PTM(x), conv::PTM(y)), m_body->GetAngle());
}

void Rigidbody::SetPosition(const sf::Vector2f& pos)
{
	m_body->SetTransform(b2Vec2(conv::PTM(pos.x), conv::PTM(pos.y)), m_body->GetAngle());
}

void Rigidbody::SetVelocity(float x, float y)
{
	m_body->SetLinearVelocity(b2Vec2(conv::PTM(x), conv::PTM(y)));
}

void Rigidbody::SetAngularVelocity(float v)
{
	m_body->SetAngularVelocity(v);
}

void Rigidbody::SetAngle(float angle)
{
	m_body->SetTransform(m_body->GetPosition(), conv::DTR(angle));
}

void Rigidbody::ApplyAngularImpulse(float impulse)
{
	m_body->ApplyAngularImpulse(impulse, true);
}

void Rigidbody::ApplyForce(const sf::Vector2f& force, const sf::Vector2f& point)
{
	b2Vec2 f(force.x, force.y);
	b2Vec2 p(point.x, point.y);
	m_body->ApplyForce(f, p, true);
}

void Rigidbody::ApplyForceToCenter(const sf::Vector2f& force)
{
	m_body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void Rigidbody::ApplyLinearImpulse(const sf::Vector2f& impulse, const sf::Vector2f& point)
{
	b2Vec2 i(impulse.x, impulse.y);
	b2Vec2 p(point.x, point.y);
	m_body->ApplyLinearImpulse(i, p, true);
}

void Rigidbody::ApplyLinearImpulseToCenter(const sf::Vector2f& impulse)
{
	m_body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), true);
}

void Rigidbody::ApplyTorque(float torque)
{
	m_body->ApplyTorque(torque, true);
}

void Rigidbody::ResetMassData()
{
	m_body->ResetMassData();
}
