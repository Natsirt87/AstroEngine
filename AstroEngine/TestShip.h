#pragma once
#include "PhysicsEntity.h"
#include "SpriteSheet.h"
#include "SoundEmitter.h"
#include "SoundListener.h"

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
	virtual void Draw(sf::RenderTexture* render) override;

	void SetZoom(float zoom);

protected:
	virtual void OnKinematicCollision(Entity* other);

	void spriteSheetSetup();
	void physicsSetup();

	void animate();
	void thrust(EventDetails* details);
	void playThrustSound();
	void stopThrustSound();
	void rotateToMouse();
	
	float m_thrustForce;
	float m_rotationTorque;

	int m_thrustSoundID;

	float m_zoom;

	SpriteSheet m_spriteSheet;
	AnimState m_animState;
	SoundEmitter m_soundEmitter;
	SoundListener m_soundListener;
};

