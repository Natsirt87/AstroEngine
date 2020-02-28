#pragma once
#include "BaseEntity.h"
#include "Rigidbody.h"
#include "SharedContext.h"

class PhysicsEntity : public BaseEntity
{
public:
	PhysicsEntity(EntityManager* entityMgr);
	virtual ~PhysicsEntity() override;

	float GetAngle();

	void SetPosition(float x, float y) override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetAngle(float angle);

	virtual void SetVelocity(float x, float y) override;
	
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow* wind) = 0;

protected:
	virtual void OnEntityCollision(BaseEntity* other) = 0;
	
	Rigidbody physicsBody; 
	
};

