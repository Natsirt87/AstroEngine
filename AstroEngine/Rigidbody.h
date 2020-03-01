#pragma once
#include <vector>
#include <functional>
#include "Converter.h"
#include "Box2D/Box2D.h"
#include <SFML/System/Vector2.hpp>
#include "BaseComponent.h"

using CollisionFunction = std::function<void(Entity* other)>;
using Collider = std::pair<b2FixtureDef*, b2Shape*>;
using ColliderContainer = std::vector<Collider>;

class Rigidbody : public BaseComponent
{
public:
	Rigidbody(b2World* world, Entity* owner);
	~Rigidbody();

	b2Fixture* AddBox(float sizeX, float sizeY, const b2Vec2& offset, float angle); //Add a box fixture to the body
	b2Fixture* AddPolygon(b2Vec2* points, int32 count); //Add a polygon fixture to the body
	b2Fixture* AddCircle(float radius, const b2Vec2& offset); //Add a circle fixture to the body

	void RemoveCollider(b2Fixture* fixture); //Remove a fixture from the body
	void OnCollisionStart(Rigidbody* other);
	void OnCollisionEnd(Rigidbody* other);

	template<class T>
	void RegisterCollisionFunctions(void(T::* collisionStart)(Entity*),
		void(T::* collisionEnd)(Entity*), T* instance)
	{
		auto funcStart = std::bind(collisionStart, instance, std::placeholders::_1);
		auto funcEnd = std::bind(collisionEnd, instance, std::placeholders::_1);
		m_collisionStart = funcStart;
		m_collisionEnd = funcEnd;
	}

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

	//Exposed Box2d body setters

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

	CollisionFunction m_collisionStart;
	CollisionFunction m_collisionEnd;
};

