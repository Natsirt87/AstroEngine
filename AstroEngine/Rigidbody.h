#pragma once
#include "box2d/box2d.h"
#include <SFML/System/Vector2.hpp>

class Rigidbody
{
public:
	Rigidbody();
	~Rigidbody();

	const b2Fixture* AddBox(float sizeX, float sizeY, float offsetX, 
		float offsetY, float restitution, float density, float friction);
	const b2Fixture* AddPolygon(const b2Vec2* points, int32 count, 
		float restitution, float density, float friction);
	const b2Fixture* AddCircle(float radius, const b2Vec2& offset, 
		float restitution, float density, float friction);

	const sf::Vector2f& GetPosition();
	const sf::Vector2f& GetVelocity();
	float GetAngle();

	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f& pos);
	void SetVelocity(float x, float y);
	void SetAngle(float angle);

	void ApplyAngularImpulse(float impulse);
	void ApplyForce(const sf::Vector2f& force, const sf::Vector2f& point);
	void ApplyForceToCenter(const sf::Vector2f& force);
	void ApplyLinearImpulse(const sf::Vector2f& impulse, const sf::Vector2f& point);
	void ApplyLinearImpulseToCenter(const sf::Vector2f& impulse);
	void ApplyTorque(float torque);

private:
	b2World* m_world;
	b2Body* m_body;
	b2BodyDef m_bodyDef;
};

