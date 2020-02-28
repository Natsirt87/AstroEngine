#pragma once
#include "PhysicsEntity.h"
#include "SpriteSheet.h"

enum class AnimState{ Thrusting, Idle };

class TestShip : public PhysicsEntity
{
public:
	TestShip(EntityManager* entityMgr);
	virtual ~TestShip();

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* wind) override;

protected:
	virtual void OnEntityCollision(BaseEntity* other);

	void spriteSheetSetup();
	void physicsSetup();

	void animate();
	void thrust(EventDetails* details);
	void rotateToMouse();
	
	b2Fixture* boxFixture;
	SpriteSheet m_spriteSheet;
	AnimState animState;
};

