#include "Window.h"
#include "SharedContext.h"

Window::Window() { setup("Window", sf::Vector2u(640, 480)); }

Window::Window(const std::string& title, const sf::Vector2u& size, SharedContext* context)
	: m_context(context)
{
	setup(title, size);
}

Window::~Window() { m_window.close(); }

void Window::setup(const std::string& title, const sf::Vector2u& size)
{
	m_windowTitle = title;
	m_windowSize = size;
	m_isFullscreen = false;
	m_isDone = false;
	m_isFocused = true;

	m_eventManager.AddCallback(StateType(0), "Fullscreen_Toggle", &Window::ToggleFullscreen, this);
	m_eventManager.AddCallback(StateType(0), "Window_Close", &Window::Close, this);

	create();
}

void Window::BeginDraw() { m_window.clear(sf::Color::Black); }
void Window::EndDraw() { m_window.display(); }

void Window::Update() //Poll window events, window closed or fullscreen key pressed
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus)
		{
			m_isFocused = false;
			m_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			m_isFocused = true;
			m_eventManager.SetFocus(true);
		}
		m_eventManager.HandleEvent(event);
	}
	m_eventManager.Update();
}



void Window::ToggleFullscreen(EventDetails* details)
{
	m_isFullscreen = !m_isFullscreen;
	m_window.close();
	create();
}

void Window::Close(EventDetails* details) { m_isDone = true; }

bool Window::IsFocused()
{
	return false;
}

bool Window::IsDone() { return m_isDone; }
bool Window::IsFullscreen() { return m_isFullscreen; }

EventManager* Window::GetEventManager() { return &m_eventManager; }
sf::RenderWindow* Window::GetRenderWindow() { return &m_window; }
sf::Vector2u Window::GetWindowSize() { return m_windowSize; }

sf::FloatRect Window::GetViewSpace()
{
	sf::RenderTexture* render = m_context->m_renderBuffer;
	sf::Vector2f viewCenter = render->getView().getCenter();
	sf::Vector2f viewSize = render->getView().getSize();
	sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
	sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
	return viewSpace;
}

void Window::create() //Make the actual SFML window
{
	sf::Uint32 style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, "Astro Game", style);
	m_window.setFramerateLimit(144);
}