#include "Entity.h"

Entity::Entity(EntityManager* entityMgr) 
	: m_entityMgr(entityMgr), m_name("BaseEntity"),
	m_type(EntityType::Base), m_id(0) {}

Entity::~Entity() {}

const sf::Vector2f& Entity::GetPosition() const { return m_position; }
const sf::Vector2f& Entity::GetVelocity() const { return m_velocity; }
const sf::Vector2f& Entity::GetSize() const { return m_size; }
std::string Entity::GetName() const { return m_name; }
unsigned int Entity::GetId() const { return m_id; }
EntityType Entity::GetType() const { return m_type; }

void Entity::SetPosition(float x, float y)
{
	m_position = sf::Vector2f(x, y);
}

void Entity::SetPosition(const sf::Vector2f& pos)
{
	m_position = pos;
}

void Entity::SetSize(float x, float y)
{
	m_size = sf::Vector2f(x, y);
}

void Entity::SetVelocity(float x, float y)
{
	m_velocity = sf::Vector2f(x, y);
}

void Entity::Update(float dt)
{
	sf::Vector2f deltaPos = m_velocity * dt;
	m_position += deltaPos;
	updateAABB();
}

void Entity::updateAABB()
{
	m_AABB = sf::FloatRect(m_position.x - (m_size.x / 2), m_position.y - (m_size.y / 2), m_size.x, m_size.y);
}