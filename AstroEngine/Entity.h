#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics.hpp"

/* The abstract parent of all entities, contains base functionality common
to every entity. */

enum class EntityType{ 
	Base, 
	PhysicsObject, 
	Enemy, 
	Player, 
	Friendly 
};

class EntityManager;
class Entity
{
	friend class EntityManager;
public:
	Entity(EntityManager* entityMgr);
	virtual ~Entity();

	virtual const sf::Vector2f& GetPosition()const;
	virtual const sf::Vector2f& GetVelocity()const;

	const sf::Vector2f& GetSize()const; //Get size of AABB
	std::string GetName()const;
	unsigned int GetId()const;
	EntityType GetType()const;

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& pos);

	void SetSize(float x, float y); //Set size of AABB

	virtual void SetVelocity(float x, float y);

	virtual void Update(float dt);
	virtual void Draw(sf::RenderTexture* render) = 0;

protected:

	/* Just sets m_AABB to a rectangle based on m_size, if child entity has a
	visual component (sprite or shape) being displayed that can rotate, make
	sure to set it to that visual component's global bounding box. */
	virtual void updateAABB(); 

	//What this entity does to the other entity that collides/overlaps with AABB
	virtual void OnKinematicCollision(Entity* other) = 0;

	std::string m_name;
	EntityType m_type;
	unsigned int m_id; //Entity ID in entity manager
	sf::Vector2f m_position; //Current position
	sf::Vector2f m_positionOld; //Position before entity moved
	sf::Vector2f m_velocity; //Current velocity
	sf::Vector2f m_maxVelocity; //Max velocity 
	sf::Vector2f m_size; //Size of AABB bounding box
	sf::FloatRect m_AABB; //Basic bounding box for simple collisions/overlaps (e.g. triggers or culling)

	EntityManager* m_entityMgr;
};

