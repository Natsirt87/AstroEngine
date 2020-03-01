#include "BaseComponent.h"

BaseComponent::BaseComponent(Entity* owner) : m_owner(owner) {}

BaseComponent::~BaseComponent() {}

Entity* BaseComponent::GetOwner() { return m_owner; }
