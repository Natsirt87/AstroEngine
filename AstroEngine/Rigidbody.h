#pragma once
#include <vector>
#include "Converter.h"
#include "box2d/box2d.h"
#include <SFML/System/Vector2.hpp>

using Collider = std::pair<b2FixtureDef*, b2Shape*>;
using ColliderContainer = std::vector<Collider>;

class Rigidbody
{
public:
	Rigidbody(b2World* world);
	~Rigidbody();

	b2Fixture* AddBox(float sizeX, float sizeY, const b2Vec2& offset, float angle); //Add a box fixture to the body
	b2Fixture* AddPolygon(const b2Vec2* points, int32 count); //Add a polygon fixture to the body
	b2Fixture* AddCircle(float radius, const b2Vec2& offset); //Add a circle fixture to the body

	void RemoveCollider(b2Fixture* fixture); //Remove a fixture from the body

	//Standard getters
	const sf::Vector2f& GetPosition();
	const sf::Vector2f& GetVelocity();
	float GetAngle();

	//Standard Setters
	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f& pos);
	void SetVelocity(float x, float y);
	void SetAngularVelocity(float v);
	void SetAngle(float angle);

	//Exposed Box2d body getters
	float GetAngularVelocity();
	float GetInertia();

	//Exposed Box2d body manipulation methods
	void ApplyAngularImpulse(float impulse);
	void ApplyForce(const sf::Vector2f& force, const sf::Vector2f& point);
	void ApplyForceToCenter(const sf::Vector2f& force);
	void ApplyLinearImpulse(const sf::Vector2f& impulse, const sf::Vector2f& point);
	void ApplyLinearImpulseToCenter(const sf::Vector2f& impulse);
	void ApplyTorque(float torque);
	void ResetMassData();

private:
	b2World* m_world;
	b2Body* m_body;
	b2BodyDef m_bodyDef;
	ColliderContainer m_colliders;
};

