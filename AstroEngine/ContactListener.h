#pragma once
#include "Rigidbody.h"

/* Custom contact listener that calls the collision functions for things
that collide (currently only rigidbodies). */

class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) override
	{
		void* object1 = contact->GetFixtureA()->GetBody()->GetUserData();
		void* object2 = contact->GetFixtureB()->GetBody()->GetUserData();
		Rigidbody* body1 = static_cast<Rigidbody*>(object1);
		Rigidbody* body2 = static_cast<Rigidbody*>(object2);

		body1->OnCollisionStart(body2);
		body2->OnCollisionStart(body1);
	}

	void EndContact(b2Contact* contact) override
	{
		void* object1 = contact->GetFixtureA()->GetBody()->GetUserData();
		void* object2 = contact->GetFixtureB()->GetBody()->GetUserData();
		Rigidbody* body1 = static_cast<Rigidbody*>(object1);
		Rigidbody* body2 = static_cast<Rigidbody*>(object2);

		body1->OnCollisionEnd(body2);
		body2->OnCollisionEnd(body1);
	}

	// This lets you process and filter BeginContact callbacks as they arise from multiple threads.
	virtual bool BeginContactImmediate(b2Contact* contact, uint32 threadId)
	{
		return true;
	}

	// This lets you process and filter EndContact callbacks as they arise from multiple threads.
	virtual bool EndContactImmediate(b2Contact* contact, uint32 threadId)
	{
		return true;
	}

	// This lets you process and filter PreSolve callbacks as they arise from multiple threads.
	virtual bool PreSolveImmediate(b2Contact* contact, const b2Manifold* oldManifold, uint32 threadId)
	{
		return false;
	}

	// This lets you process and filter PostSolve callbacks as they arise from multiple threads.
	virtual bool PostSolveImmediate(b2Contact* contact, const b2ContactImpulse* impulse, uint32 threadId)
	{
		return false;
	}
};

