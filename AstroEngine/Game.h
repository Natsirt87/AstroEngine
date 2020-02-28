#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "StateManager.h"
#include "Window.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "ContactListener.h"

class Game
{
public:
	Game();
	~Game();

	void Run(); //Manages method order and stuff like delta time

	sf::Time GetElapsed();
	Window* GetWindow();

private:
	void update(sf::Time deltaTime); //Do non visual updating stuff
	void render(); //Do rendering and drawing stuff
	void lateUpdate();

	void restartClock();

	Window m_window;
	StateManager m_stateManager;
	EntityManager m_entityManager;
	TextureManager m_textureManager;
	b2World m_world;
	ContactListener m_contactListener;

	SharedContext m_context;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};