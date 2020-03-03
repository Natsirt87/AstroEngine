#pragma once
#include "BaseState.h"
#include "EventManager.h"

/* The paused application state, any states below it get frozen. 
Traditionally some sort of menu is displayed */

class State_Paused : public BaseState
{
public:
	State_Paused(StateManager* stateManager);
	~State_Paused();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& time);
	void Draw();

	void Unpause(EventDetails* details); //Just changes the state back to the main application state, Game in this case

private:
	sf::Font m_font;
	sf::Text m_text;
	sf::RectangleShape m_rect;
};

