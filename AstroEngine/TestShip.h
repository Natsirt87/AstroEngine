#pragma once
#include "PhysicsEntity.h"
#include "SpriteSheet.h"

/* A ship for testing systems in the game engine, also
acts as an example for how to use certain things. */

enum class AnimState{ Thrusting, Idle };

class TestShip : public PhysicsEntity
{
public:
	TestShip(EntityManager* entityMgr);
	virtual ~TestShip();

	virtual void PhysicsCollisionStart(Entity* other) override;
	virtual void PhysicsCollisionEnd(Entity* other) override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* wind) override;

protected:
	virtual void OnKinematicCollision(Entity* other);

	void spriteSheetSetup();
	void physicsSetup();

	void animate();
	void thrust(EventDetails* details);
	void rotateToMouse();
	
	float thrustForce;
	float rotationTorque;

	SpriteSheet m_spriteSheet;
	AnimState animState;
};

