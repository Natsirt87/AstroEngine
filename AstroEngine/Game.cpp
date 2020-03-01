#include "Game.h"

Game::Game() : m_window("Astro", sf::Vector2u(1920, 1080)),
m_stateManager(&m_context), m_entityManager(&m_context, 500), m_world(b2Vec2(0,0))
{
	m_clock.restart();
	m_world.SetAllowSleeping(true);
	m_world.SetContactListener(&m_contactListener);

	m_context.m_wind = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_context.m_entityManager = &m_entityManager;
	m_context.m_textureManager = &m_textureManager;
	m_context.m_world = &m_world;
	m_context.m_rTexture = &m_rTexture;

	m_stateManager.SwitchTo(StateType::Game);
}

Game::~Game() {}

void Game::Run()
{
	float fps = 1 / m_elapsed.asSeconds();
	std::cout << std::to_string(fps) << std::endl;
	update(m_elapsed);
	render();
	lateUpdate(); 
}

void Game::update(sf::Time deltaTime)
{
	m_window.Update();
	m_stateManager.Update(deltaTime);
}

void Game::render()
{
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}

void Game::lateUpdate()
{
	m_stateManager.ProcessRequests();
	restartClock();
}

void Game::restartClock() { m_elapsed = m_clock.restart(); }

sf::Time Game::GetElapsed() { return m_clock.getElapsedTime(); }

Window* Game::GetWindow()
{
	return &m_window;
}