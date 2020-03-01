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

/* Entry point for the application after Main, this class
is what dictates the most basic application loop */

class Game
{
public:
	Game();
	~Game();

	void Run(); //What actually gets called every frame

	sf::Time GetElapsed(); //Get delta time in sf::Time
	Window* GetWindow(); //Gets a reference to the window

private:
	void update(sf::Time deltaTime); //Does non visual updating stuff
	void render(); //Does rendering and drawing stuff
	void lateUpdate(); //Does event processing stuff

	void restartClock(); //Resets the delta time counter

	Window m_window;
	StateManager m_stateManager;
	EntityManager m_entityManager;
	TextureManager m_textureManager;
	b2World m_world;
	ContactListener m_contactListener;
	sf::RenderTexture m_rTexture;

	SharedContext m_context;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};