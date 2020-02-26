#pragma once
#include "box2d/box2d.h"
#include "Converter.h"
#include "Window.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "EntityManager.h"

struct SharedContext
{
	SharedContext() : 
		m_wind(nullptr), 
		m_eventManager(nullptr),
		m_textureManager(nullptr),
		m_entityManager(nullptr),
		m_world(nullptr) {}


	Window* m_wind;
	EventManager* m_eventManager;
	TextureManager* m_textureManager;
	EntityManager* m_entityManager;
	b2World* m_world;
};