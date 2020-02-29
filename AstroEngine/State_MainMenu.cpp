#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* stateManager)
	: BaseState(stateManager) {}

State_MainMenu::~State_MainMenu() {}

void State_MainMenu::OnCreate()
{
	sf::Vector2u windowSize = m_stateMgr->GetContext()->
		m_wind->GetRenderWindow()->getSize();

	m_labelFont.loadFromFile("Resources/Fonts/arial.ttf");
	m_titleFont.loadFromFile("Resources/Fonts/spyagency.ttf");
	m_title.setFont(m_titleFont);
	m_title.setString({ "MAIN MENU" });
	m_title.setCharacterSize(40);

	sf::FloatRect textRect = m_title.getLocalBounds();
	m_title.setOrigin(textRect.left + textRect.width / 2.f,
		textRect.top + textRect.height / 2.f);
	m_title.setPosition(windowSize.x / 2.f, windowSize.y / 6.f);

	m_buttonSize = sf::Vector2f(600.f, 64.f);
	m_buttonPos = sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.5f);
	m_buttonPadding = 15; //In pixels

	std::string str[3];
	str[0] = "Play";
	str[1] = "Options";
	str[2] = "Exit";

	for (int i = 0; i < 3; i++)
	{
		sf::Vector2f buttonPosition(m_buttonPos.x, m_buttonPos.y +
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);

		m_rects[i].setOrigin(m_buttonSize.x / 2.f, m_buttonSize.y / 2.f);
		m_rects[i].setPosition(buttonPosition);

		m_labels[i].setFont(m_labelFont);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(20);

		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(rect.left + rect.width / 2.f,
			rect.top + rect.height / 2.f);

		m_labels[i].setPosition(buttonPosition);
	}

	EventManager* eventMgr = m_stateMgr->GetContext()->m_eventManager;
	eventMgr->AddCallback(StateType::MainMenu, "Menu_Click", 
		&State_MainMenu::MouseClick, this);
}

void State_MainMenu::OnDestroy()
{
	EventManager* eventMgr = m_stateMgr->GetContext()->m_eventManager;
	eventMgr->RemoveCallback(StateType::MainMenu, "Menu_Click");
}

void State_MainMenu::Activate()
{
	if (m_stateMgr->HasState(StateType::Game)
		&& m_labels[0].getString() == "Play")
	{
		m_labels[0].setString(sf::String("Resume"));
		sf::FloatRect rect = m_labels[0].getLocalBounds();
		m_labels[0].setOrigin(rect.left + rect.width / 2.f,
			rect.top + rect.height / 2.f);
	}
}

void State_MainMenu::Deactivate() { m_timePassed = 0; }

void State_MainMenu::Update(const sf::Time& time) 
{
	if (m_timePassed <= 0.9)
	{
		m_timePassed += time.asSeconds();
		for (int i = 0; i < 3; i++)
		{
			m_rects[i].setFillColor(sf::Color(255, 255, 255, m_timePassed * 255));
			m_labels[i].setFillColor(sf::Color(0, 0, 0, m_timePassed * 255));
			m_title.setFillColor(sf::Color(255, 255, 255, m_timePassed * 255));
		}
	}
}

void State_MainMenu::Draw()
{
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	window->draw(m_title);

	for (int i = 0; i < 3; i++)
	{
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
}

void State_MainMenu::MouseClick(EventDetails* details)
{
	sf::Vector2i mousePos = details->m_mouse;

	float halfX = m_buttonSize.x / 2.f;
	float halfY = m_buttonSize.y / 2.f;

	for (int i = 0; i < 3; i++)
	{
		if (mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY)
		{
			if (i == 0)
			{
				m_stateMgr->SwitchTo(StateType::Game);
			}
			else if (i == 1)
			{
				std::cout << "Options state \n";
			}
			else if (i == 2)
			{
				m_stateMgr->GetContext()->m_wind->Close();
			}
		}
	}
}