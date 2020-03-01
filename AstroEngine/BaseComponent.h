#pragma once
#include "Entity.h"

class BaseComponent
{
public:
	BaseComponent(Entity* owner);
	~BaseComponent();

	Entity* GetOwner();

private:
	Entity* m_owner;
};

