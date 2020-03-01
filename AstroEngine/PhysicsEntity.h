#pragma once
#include "Entity.h"
#include "Rigidbody.h"
#include "SharedContext.h"

/* A helpful little abstract class that just does stuff to 
a rigidbody when Entity methods are called. */

class PhysicsEntity : public Entity
{
public:
	PhysicsEntity(EntityManager* entityMgr);
	virtual ~PhysicsEntity() override;

	float GetAngle();

	void SetPosition(float x, float y) override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetAngle(float angle);

	virtual void SetVelocity(float x, float y) override;

	virtual void PhysicsCollisionStart(Entity* other) = 0;
	virtual void PhysicsCollisionEnd(Entity* other) = 0;
	
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow* wind) = 0;

	Rigidbody rigidbody;
protected:
	virtual void OnKinematicCollision(Entity* other) = 0;
	
};

