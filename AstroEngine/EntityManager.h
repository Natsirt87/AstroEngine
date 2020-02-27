#pragma once
#include <unordered_map>
#include <functional>
#include "BaseEntity.h"

using EntityContainer = std::unordered_map<
	unsigned int, BaseEntity*>;
using EntityFactory = std::unordered_map<
	EntityType, std::function<BaseEntity*(void)>>;

class SharedContext;

class EntityManager
{
public:
	EntityManager(SharedContext* context, unsigned int maxEntities);
	~EntityManager();
	
	int Add(const EntityType& type,
		const std::string& name = "");
	BaseEntity* Find(unsigned int id);
	BaseEntity* Find(const std::string& name);
	void Remove(unsigned int id);

	void Update(float dt);
	void Draw();

	void Purge();

	SharedContext* GetContext();

private:
	template<class T>
	void RegisterEntity(const EntityType& type)
	{
		m_entityFactory[type] = [this]() -> BaseEntity*
		{
			return new T(this);
		};
	}

	void processRemovals();
	void entityCollisionCheck();

	EntityContainer m_entities;
	EntityFactory m_entityFactory;
	SharedContext* m_context;
	unsigned int m_idCounter;
	unsigned int m_maxEntities;

	std::vector<unsigned int> m_entitiesToRemove;
};

