#pragma once
#include "box2d/box2d.h"
#include "Converter.h"
#include "Window.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"

/* Collection of instances for things many objects will probably
need to reference, hence the name "shared" context. */

struct SharedContext
{
	SharedContext() : 
		m_wind(nullptr), 
		m_eventManager(nullptr),
		m_textureManager(nullptr),
		m_shaderManager(nullptr),
		m_entityManager(nullptr),
		m_soundManager(nullptr),
		m_world(nullptr),
		m_renderBuffer(nullptr){}


	Window* m_wind;
	EventManager* m_eventManager;
	TextureManager* m_textureManager;
	ShaderManager* m_shaderManager;
	EntityManager* m_entityManager;
	SoundManager* m_soundManager;
	b2World* m_world;
	sf::RenderTexture* m_renderBuffer;
};