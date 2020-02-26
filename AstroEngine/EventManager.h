#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GoinedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, 
	MouseMoved = sf::Event::MouseMoved, Joystick
};

struct EventInfo
{
	EventInfo() { m_code = 0; }
	EventInfo(int event) { m_code = event; }
	union
	{
		int m_code;
	};
};

struct EventDetails
{
	EventDetails(const std::string& bindName)
		: m_name(bindName)
	{
		Clear();
	}
	std::string m_name;

	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode;

	void Clear()
	{
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding
{
	Binding(const std::string& name)
		: m_name(name), m_details(name), c(0) {}
	
	void BindEvent(EventType type, EventInfo info = EventInfo())
	{
		m_events.emplace_back(type, info);
	}

	Events m_events;
	std::string m_name;
	int c; //Count of events "happening", or being called

	EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using CallbackContainer = std::unordered_map<
	std::string, std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding* binding);
	bool RemoveBinding(std::string name);
	void SetFocus(const bool& focus);
	void SetCurrentState(StateType state);

	//All this needs to be defined in the header, I know it's gross
	template<class T>
	bool AddCallback(StateType state, const std::string& name,
		void(T::*func)(EventDetails*), T* instance)
	{
		auto itr = m_callbacks.emplace(state, CallbackContainer()).first;
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return itr->second.emplace(name, temp).second;
	}

	bool RemoveCallback(StateType state, const std::string& name)
	{
		auto itr = m_callbacks.find(state);
		if (itr == m_callbacks.end()) { return false; }
		auto itr2 = itr->second.find(name);
		if (itr2 == itr->second.end()) { return false; }
		itr->second.erase(name);
		return true;
	}

	sf::Vector2i GetMousePos(sf::RenderWindow* wind = nullptr)
	{
		return (wind ? sf::Mouse::getPosition(*wind)
			: sf::Mouse::getPosition());
	}

	void HandleEvent(sf::Event& event);
	void Update();

private:
	void loadBindings();

	Bindings m_bindings;
	Callbacks m_callbacks;
	StateType m_currentState;

	bool m_hasFocus;
};