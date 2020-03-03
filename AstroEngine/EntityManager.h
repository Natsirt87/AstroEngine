#pragma once
#include <unordered_map>
#include <functional>
#include "Entity.h"

/* Manages all entities and is responsible for calling their update and
draw methods.*/

using EntityContainer = std::unordered_map<
	unsigned int, Entity*>;
using EntityFactory = std::unordered_map<
	EntityType, std::function<Entity*(void)>>;
using EntityList = std::vector<Entity*>;

class SharedContext;

class EntityManager
{
public:
	EntityManager(SharedContext* context, unsigned int maxEntities);
	~EntityManager();
	
	int Add(const EntityType& type,
		const std::string& name,
		bool kinematic);
	Entity* Find(unsigned int id);
	Entity* Find(const std::string& name);
	void Remove(unsigned int id);

	void Update(float dt);
	void Draw();

	void Purge();

	SharedContext* GetContext();

private:
	template<class T>
	void RegisterEntity(const EntityType& type)
	{
		m_entityFactory[type] = [this]() -> Entity*
		{
			return new T(this);
		};
	}

	void processRemovals();
	void kinematicCollisionCheck();

	EntityContainer m_entities;
	EntityFactory m_entityFactory;
	EntityList m_kinematicEntities;
	SharedContext* m_context;
	unsigned int m_idCounter;
	unsigned int m_maxEntities;

	std::vector<unsigned int> m_entitiesToRemove;
};

