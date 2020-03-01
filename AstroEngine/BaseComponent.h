#pragma once
#include "Entity.h"

/* The very simple parent component class, contains the only common
functionality between components, that being the idea of an owner. */

class BaseComponent
{
public:
	BaseComponent(Entity* owner);
	~BaseComponent();

	Entity* GetOwner();

private:
	Entity* m_owner;
};

