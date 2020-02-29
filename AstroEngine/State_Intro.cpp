#include "State_Intro.h"
#include "StateManager.h"

State_Intro::State_Intro(StateManager* stateManager)
	: BaseState(stateManager) {}

State_Intro::~State_Intro() {}

void State_Intro::OnCreate()
{
	m_timePassed = 0.0f;

	sf::Vector2u windowSize = m_stateMgr->GetContext()->
		m_wind->GetRenderWindow()->getSize();

	m_introTexture.loadFromFile("Resources/Images/astro.png");
	m_introTexture.setSmooth(true);
	m_introSprite.setTexture(m_introTexture);
	m_introSprite.setScale(0.75, 0.75);
	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.f,
		m_introTexture.getSize().y / 2.f);
	m_introSprite.setPosition(windowSize.x / 2.f, windowSize.y / 1.8f);

	m_font.loadFromFile("Resources/Fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setString({ "Press SPACE to continue" });
	m_text.setCharacterSize(15);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.f,
		textRect.top + textRect.height / 2.f);
	m_text.setPosition(windowSize.x / 2.f, windowSize.y / 1.5f);

	EventManager* eventMgr = m_stateMgr->GetContext()->m_eventManager;
	eventMgr->AddCallback(StateType::Intro, "Intro_Continue",
		&State_Intro::Continue, this);
}

void State_Intro::OnDestroy()
{
	EventManager* eventMgr = m_stateMgr->GetContext()->m_eventManager;
	eventMgr->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void State_Intro::Activate() {}
void State_Intro::Deactivate() {}

void State_Intro::Update(const sf::Time& time)
{
	
	if (m_timePassed < 7.f) { 
		m_timePassed += time.asSeconds();

		if (m_timePassed < 5.f)
		{
			m_introSprite.setColor(sf::Color(255, 255, 255, m_timePassed * 51.f));
		}
		if (m_timePassed > 4.f)
		{
			m_text.setFillColor(sf::Color(255, 255, 255, (m_timePassed - 4) * 85));
		}
	}
	
	
}

void State_Intro::Draw()
{
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	window->draw(m_introSprite);
	if (m_timePassed >= 4.f)
	{
		window->draw(m_text);
	}
}

void State_Intro::Continue(EventDetails* details)
{
	if (m_timePassed >= 4.f)
	{
		m_stateMgr->SwitchTo(StateType::MainMenu);
		m_stateMgr->Remove(StateType::Intro);
	}
}