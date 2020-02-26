#pragma once
#include "BaseEntity.h"
#include "StateManager.h"
#include "SpriteSheet.h"

class TestCharacter : public BaseEntity
{
	friend class EntityManager;
public:
	TestCharacter(EntityManager* entityMgr);
	virtual ~TestCharacter();

	float GetAngle();
	void SetAngle(float angle);

	virtual void OnEntityCollision(BaseEntity* other);

	virtual void Update(float dt);
	void Draw(sf::RenderWindow* wind);

protected:
	void thrust(EventDetails* details);
	void doAngle();

	SpriteSheet m_spriteSheet;
	float m_angle;
};

