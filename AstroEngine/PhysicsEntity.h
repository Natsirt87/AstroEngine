#pragma once
#include "BaseEntity.h"
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

	virtual void Move(float x, float y) override;
	virtual void SetVelocity(float x, float y) override;
	virtual void AddVelocity(float x, float y) override;
	
	void ApplyAngularImpulse(float impulse);
	void ApplyForce(const sf::Vector2f& force, const sf::Vector2f& point);
	void ApplyForceToCenter(const sf::Vector2f& force);
	void ApplyLinearImpulse(const sf::Vector2f& impulse, const sf::Vector2f& point);
	void ApplyLinearImpulseToCenter(const sf::Vector2f& impulse);
	void ApplyTorque(float torque);

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow* wind) = 0;

protected:
	virtual void OnEntityCollision(BaseEntity* other) = 0;

	b2World* m_world;
	b2Body* m_body;
	b2BodyDef m_bodyDef;
	
};

