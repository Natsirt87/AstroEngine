#include "Game.h"

Game::Game() : m_window("Astro", sf::Vector2u(1920, 1080), &m_context),
m_stateManager(&m_context), m_entityManager(&m_context, 500), m_world(b2Vec2(0,0)),
m_globalShader(nullptr), m_bloomEffect(&m_shaderManager), m_bloomEnabled(true),
m_antialiasing(false)
{
	if (!sf::Shader::isAvailable())
	{
		std::cerr << "! Graphics architecture outdated or nonexistent" << std::endl;
		m_window.Close();
	}

	m_clock.restart();
	m_world.SetAllowSleeping(true);
	m_world.SetContactListener(&m_contactListener);

	m_renderBuffer.create(m_window.GetWindowSize().x, m_window.GetWindowSize().y);
	m_renderBuffer.setSmooth(m_antialiasing);
	m_postBuffer.create(m_window.GetWindowSize().x, m_window.GetWindowSize().y);
	m_postBuffer.setSmooth(m_antialiasing);

	m_context.m_wind = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_context.m_entityManager = &m_entityManager;
	m_context.m_textureManager = &m_textureManager;
	m_context.m_shaderManager = &m_shaderManager;
	m_context.m_world = &m_world;
	m_context.m_renderBuffer = &m_renderBuffer;

	m_stateManager.SwitchTo(StateType::Game);
}

Game::~Game() {}

void Game::Run()
{
	update(m_elapsed);
	render();
	lateUpdate(); 
	float fps = 1 / m_elapsed.asSeconds();
	//std::cout << "FPS: " << std::to_string((int)fps) << std::endl;
}

void Game::update(sf::Time deltaTime)
{
	m_window.Update();
	m_stateManager.Update(deltaTime);
}

void Game::render()
{
	m_window.BeginDraw();
	m_renderBuffer.clear(sf::Color::Black);
	m_postBuffer.clear(sf::Color::Black);
	m_stateManager.Draw();
	m_renderBuffer.display();

	sf::Sprite scene(m_renderBuffer.getTexture());
	m_stateManager.UpdateGlobalShader(scene.getTexture());
	m_globalShader = m_stateManager.GetGlobalShader();
	m_postEffects = m_stateManager.GetPostEffects();

	if (m_postEffects.m_bloom) 
	{
		m_postBuffer.draw(scene, m_globalShader);
		m_postBuffer.display();
		m_bloomEffect.apply(m_postBuffer, *m_window.GetRenderWindow());
	}
	else
	{
		m_window.GetRenderWindow()->draw(scene, m_globalShader);
	}
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