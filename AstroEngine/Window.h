#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "EventManager.h"
class SharedContext;

/* The application window, has functionality for displaying, closing, 
and various other window related activities. */

class Window
{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size, SharedContext* context);
	~Window();

	void BeginDraw(); //Clear the window
	void EndDraw(); //Display changes

	void Update(); //Update window things

	void ToggleFullscreen(EventDetails* details);
	void Close(EventDetails* details = nullptr);

	bool IsFocused();
	bool IsDone();
	bool IsFullscreen();

	EventManager* GetEventManager();
	sf::RenderWindow* GetRenderWindow();
	sf::Vector2u GetWindowSize();
	sf::FloatRect GetViewSpace();

private:
	void setup(const std::string& title, const sf::Vector2u& size);
	void create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	EventManager m_eventManager;
	SharedContext* m_context;

	bool m_isFocused;
	bool m_isDone;
	bool m_isFullscreen;
};