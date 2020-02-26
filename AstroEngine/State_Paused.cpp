#include "State_Paused.h"
#include "StateManager.h"

State_Paused::State_Paused(StateManager* stateManager) 
	: BaseState(stateManager) {}

State_Paused::~State_Paused() {}

void State_Paused::OnCreate()
{
	SetTransparent(true); //Do the transparency thing, it'll draw on top of stuff
	m_font.loadFromFile("Resources/Fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("PAUSED"));
	m_text.setCharacterSize(20);
	m_text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = m_stateMgr->GetContext()->
		m_wind->GetRenderWindow()->getSize();

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.f,
		textRect.top + textRect.height / 2.f);
	m_text.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);

	m_rect.setSize(sf::Vector2f(windowSize));
	m_rect.setPosition(0, 0);
	m_rect.setFillColor(sf::Color(0, 0, 0, 150));

	EventManager* eventMgr = m_stateMgr->GetContext()->m_eventManager;
	eventMgr->AddCallback(StateType::Paused, "Game_Pause", &State_Paused::Unpause, this);
}

void State_Paused::OnDestroy()
{
	EventManager* eventMgr = m_stateMgr->GetContext()->m_eventManager;
	eventMgr->RemoveCallback(StateType::Paused, "Game_Pause");
}

void State_Paused::Activate() {}
void State_Paused::Deactivate() {}

void State_Paused::Update(const sf::Time& time) {}

void State_Paused::Draw()
{
	sf::RenderWindow* wind = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	wind->draw(m_rect);
	wind->draw(m_text);
}

void State_Paused::Unpause(EventDetails* details)
{
	m_stateMgr->SwitchTo(StateType::Game);
}
