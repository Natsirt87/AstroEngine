#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

enum class EntityType{ 
	Base, 
	PhysicsObject, 
	Enemy, 
	Player, 
	Friendly 
};

class EntityManager;
class BaseEntity
{
	friend class EntityManager;
public:
	BaseEntity(EntityManager* entityMgr);
	virtual ~BaseEntity();

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
	virtual void Draw(sf::RenderWindow* wind) = 0;

protected:
	void updateAABB();

	//What this entity does to the other entity that collides/overlaps with AABB
	virtual void OnEntityCollision(BaseEntity* other) = 0;

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

