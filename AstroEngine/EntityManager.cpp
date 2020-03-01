#include "EntityManager.h"
#include "SharedContext.h"
#include "PhysicsBox.h"
#include "TestShip.h"

EntityManager::EntityManager(SharedContext* context, unsigned int maxEntities) 
	: m_context(context), m_maxEntities(maxEntities), m_idCounter(0)
{
	//Register all entity types here
	RegisterEntity<TestShip>(EntityType::Player);
	RegisterEntity<PhysicsBox>(EntityType::PhysicsObject);
}

EntityManager::~EntityManager() { Purge(); }

int EntityManager::Add(const EntityType& type, const std::string& name, bool kinematic)
{
	auto itr = m_entityFactory.find(type);
	if (itr == m_entityFactory.end()) { return -1; }
	Entity* entity = itr->second();
	entity->m_id = m_idCounter;
	if (name != "") { entity->m_name = name; }

	m_entities.emplace(m_idCounter, entity);

	if (kinematic) { m_kinematicEntities.push_back(entity); }

	m_idCounter++;
	return m_idCounter - 1;
}

Entity* EntityManager::Find(unsigned int id)
{
	auto itr = m_entities.find(id);
	if (itr == m_entities.end()) { return nullptr; }
	return itr->second;
}

Entity* EntityManager::Find(const std::string& name)
{
	for (auto& itr : m_entities)
	{
		if (itr.second->GetName() == name)
		{
			return itr.second;
		}
	}
	return nullptr;
}

void EntityManager::Remove(unsigned int id)
{
	m_entitiesToRemove.emplace_back(id);
}

void EntityManager::Update(float dt)
{
	for (auto& itr : m_entities)
	{
		itr.second->Update(dt);
	}

	kinematicCollisionCheck();
	processRemovals();
}

void EntityManager::Draw()
{
	sf::RenderWindow* wnd = m_context->m_wind->GetRenderWindow();
	sf::FloatRect viewSpace = m_context->m_wind->GetViewSpace();

	for (auto& itr : m_entities)
	{
		if (!viewSpace.intersects(itr.second->m_AABB)) { continue; }
		itr.second->Draw(wnd);
	}
}

void EntityManager::Purge()
{
	for (auto& itr : m_entities)
	{
		delete itr.second;
	}
	m_entities.clear();
	m_idCounter = 0;
}

SharedContext* EntityManager::GetContext() { return m_context; }

void EntityManager::processRemovals()
{
	while (m_entitiesToRemove.begin() != m_entitiesToRemove.end())
	{
		unsigned int id = m_entitiesToRemove.back();
		auto itr = m_entities.find(id);
		if (itr != m_entities.end())
		{
			std::cout << "Removing entity: " << itr->second->GetId() << std::endl;
			delete itr->second;
			m_entities.erase(itr);
		}
		m_entitiesToRemove.pop_back();
	}
}

void EntityManager::kinematicCollisionCheck()
{
	if (m_entities.empty()) { return; }

	for (int i = 0; i < m_kinematicEntities.size(); i++)
	{
		for (int j = i + 1; j < m_kinematicEntities.size(); j++)
		{
			Entity* first = m_kinematicEntities[i];
			Entity* second = m_kinematicEntities[j];

			if (first->m_AABB.intersects(second->m_AABB))
			{
				first->OnKinematicCollision(second);
				second->OnKinematicCollision(first);
			}
		}
	}
}
