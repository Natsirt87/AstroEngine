#pragma once
#include "PhysicsEntity.h"
#include "box2d\b2_world_callbacks.h"
#include "box2d/b2_contact.h"
class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) override
	{
		void* object1 = contact->GetFixtureA()->GetBody()->GetUserData();
		void* object2 = contact->GetFixtureB()->GetBody()->GetUserData();
		PhysicsEntity* entity1 = static_cast<PhysicsEntity*>(object1);
		PhysicsEntity* entity2 = static_cast<PhysicsEntity*>(object2);

		std::cout << entity1->GetName() << " collided with " << entity2->GetName() << std::endl;

		entity1->PhysicsCollisionStart(entity2);
		entity2->PhysicsCollisionStart(entity1);
	}

	void EndContact(b2Contact* contact) override
	{
		void* object1 = contact->GetFixtureA()->GetBody()->GetUserData();
		void* object2 = contact->GetFixtureB()->GetBody()->GetUserData();
		PhysicsEntity* entity1 = static_cast<PhysicsEntity*>(object1);
		PhysicsEntity* entity2 = static_cast<PhysicsEntity*>(object2);

		entity1->PhysicsCollisionEnd(entity2);
		entity2->PhysicsCollisionEnd(entity1);
	}
};

