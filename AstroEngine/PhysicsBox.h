#pragma once
#include "PhysicsEntity.h"

/* A basic test of physics and collision, just a white box with physics. */

class PhysicsBox : public PhysicsEntity
{
public:
	PhysicsBox(EntityManager* entityMgr);
	virtual ~PhysicsBox() override;

	void Create(float sizeX, float sizeY);

	virtual void PhysicsCollisionStart(Entity* other) override;
	virtual void PhysicsCollisionEnd(Entity* other) override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderTexture* render) override;

protected:
	virtual void updateAABB() override;
	virtual void OnKinematicCollision(Entity* other) override;
	
	b2Fixture* boxFixture;
	sf::RectangleShape* m_rect;
};

