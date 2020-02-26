#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_MainMenu : public BaseState
{
public:
	State_MainMenu(StateManager* stateManager);
	~State_MainMenu();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& time);
	void Draw();

	void MouseClick(EventDetails* details);

private:
	sf::Font m_titleFont;
	sf::Font m_labelFont;
	sf::Text m_title;

	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;

	sf::RectangleShape m_rects[3];
	sf::Text m_labels[3];

	float m_timePassed;
};