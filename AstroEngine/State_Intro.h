#pragma once
#include "BaseState.h"
#include "EventManager.h"

/* The intro application state, the very first thing the user sees
after starting the application. */

class State_Intro : public BaseState
{
public:
	State_Intro(StateManager* stateManager);
	~State_Intro();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& time);
	void Draw();

	void Continue(EventDetails* details); //Moves on to the Main Menu state whan a key is pressed (space is default)

private:
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
	sf::Font m_font;
	sf::Text m_text;

	float m_timePassed;
};