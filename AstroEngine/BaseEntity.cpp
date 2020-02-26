#include "BaseEntity.h"

BaseEntity::BaseEntity(EntityManager* entityMgr) 
	: m_entityMgr(entityMgr), m_name("BaseEntity"),
	m_type(EntityType::Base), m_id(0) {}

BaseEntity::~BaseEntity() {}

const sf::Vector2f& BaseEntity::GetPosition() const { return m_position; }
const sf::Vector2f& BaseEntity::GetVelocity() const { return m_velocity; }
const sf::Vector2f& BaseEntity::GetSize() const { return m_size; }
std::string BaseEntity::GetName() const { return m_name; }
unsigned int BaseEntity::GetId() const { return m_id; }
EntityType BaseEntity::GetType() const { return m_type; }

void BaseEntity::SetPosition(float x, float y)
{
	m_position = sf::Vector2f(x, y);
	updateAABB();
}

void BaseEntity::SetPosition(const sf::Vector2f& pos)
{
	m_position = pos;
	updateAABB();
}

void BaseEntity::SetSize(float x, float y)
{
	m_size = sf::Vector2f(x, y);
	updateAABB();
}

void BaseEntity::Move(float x, float y)
{
	m_positionOld = m_position;
	m_position += sf::Vector2f(x, y);
	updateAABB();
}

void BaseEntity::SetVelocity(float x, float y)
{
	m_velocity = sf::Vector2f(x, y);
}

void BaseEntity::AddVelocity(float x, float y)
{
	m_velocity += sf::Vector2f(x, y);
}

void BaseEntity::Update(float dt)
{
	sf::Vector2f deltaPos = m_velocity * dt;
	Move(deltaPos.x, deltaPos.y);
}

void BaseEntity::updateAABB()
{
	m_AABB = sf::FloatRect(m_position.x - (m_size.x / 2), m_position.y - (m_size.y / 2), m_size.x, m_size.y);
}