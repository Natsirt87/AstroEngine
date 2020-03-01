#pragma once
#include "PhysicsEntity.h"

class PhysicsBox : public PhysicsEntity
{
public:
	PhysicsBox(EntityManager* entityMgr);
	virtual ~PhysicsBox() override;

	void Create(float sizeX, float sizeY);

	virtual void PhysicsCollisionStart(Entity* other) override;
	virtual void PhysicsCollisionEnd(Entity* other) override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* wind) override;

protected:
	virtual void OnKinematicCollision(Entity* other);
	
	b2Fixture* boxFixture;
	sf::RectangleShape* m_rect;
};

