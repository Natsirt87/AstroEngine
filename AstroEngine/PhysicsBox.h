#pragma once
#include "PhysicsEntity.h"

class PhysicsBox : public PhysicsEntity
{
public:
	PhysicsBox(EntityManager* entityMgr);
	virtual ~PhysicsBox() override;

	void Create(float sizeX, float sizeY);

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* wind) override;

protected:
	virtual void OnEntityCollision(BaseEntity* other);

	b2PolygonShape m_boxShape;
	b2FixtureDef m_fixtureDef;
	sf::RectangleShape m_rect;
};

