#include "StateManager.h"

StateManager::StateManager(SharedContext* shared)
	: m_shared(shared)
{
	registerState<State_Intro>(StateType::Intro);
	registerState<State_MainMenu>(StateType::MainMenu);
	registerState<State_Game>(StateType::Game);
	registerState<State_Paused>(StateType::Paused);
}

StateManager::~StateManager()
{
	for (auto& itr : m_states)
	{
		itr.second->OnDestroy();
		delete itr.second;
	}
}

void StateManager::Update(const sf::Time& time)
{
	if (m_states.empty()) { return; }

	if (m_states.back().second->IsTranscendent() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin())
		{
			if (itr != m_states.end())
			{
				if (!itr->second->IsTranscendent()) { break; }
			}
			itr--;
		}
		for (; itr != m_states.end(); itr++)
		{
			itr->second->Update(time);
		}
	}
	else
	{
		m_states.back().second->Update(time);
	}
}

void StateManager::UpdateGlobalShader(const sf::Texture* tex)
{
	m_states.back().second->updateGlobalShader(tex);
}

void StateManager::Draw()
{
	if (m_states.empty()) { return; }

	if (m_states.back().second->IsTransparent() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin())
		{
			if (itr != m_states.end())
			{
				if (!itr->second->IsTransparent())
				{
					break;
				}
			}
			itr--;
		}
		for (; itr != m_states.end(); itr++)
		{
			m_shared->m_renderBuffer->
				setView(itr->second->GetView());
			itr->second->Draw();
		}
	}
	else
	{
		m_shared->m_renderBuffer->setView(m_states.back().second->GetView());
		m_states.back().second->Draw();
	}
}

void StateManager::ProcessRequests()
{
	while (m_toRemove.begin() != m_toRemove.end())
	{
		removeState(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

SharedContext* StateManager::GetContext() { return m_shared; }

bool StateManager::HasState(const StateType& type)
{
	for (auto itr = m_states.begin(); itr != m_states.end(); itr++)
	{
		if (itr->first == type)
		{
			auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), type);
			if (removed == m_toRemove.end()) { return true; }
			return false;
		}
	}
	return false;
}

void StateManager::SwitchTo(const StateType& type)
{
	m_shared->m_eventManager->SetCurrentState(type);
	m_shared->m_soundManager->ChangeState(type);
	for (auto itr = m_states.begin(); itr != m_states.end(); itr++)
	{
		if (itr->first == type)
		{
			m_states.back().second->Deactivate();
			StateType tmp_type = itr->first;
			BaseState* tmp_state = itr->second;
			m_states.erase(itr);
			m_states.emplace_back(tmp_type, tmp_state);
			tmp_state->Activate();
			m_shared->m_renderBuffer->
				setView(tmp_state->GetView());
			return;
		}
	}

	//State with the type wasn't found
	if (!m_states.empty()) { m_states.back().second->Deactivate(); }
	createState(type);
	m_states.back().second->Activate();
	m_shared->m_wind->GetRenderWindow()->
		setView(m_states.back().second->GetView());
}

void StateManager::Remove(const StateType& type)
{
	m_toRemove.push_back(type);
}

sf::Shader* StateManager::GetGlobalShader()
{
	return m_states.back().second->m_globalShader;
}

const PostEffectSettings& StateManager::GetPostEffects()
{
	return m_states.back().second->m_postEffects;
}

float StateManager::GetCurrentZoom()
{
	return m_states.back().second->m_zoom;
}

void StateManager::createState(const StateType& type)
{
	auto newState = m_stateFactory.find(type);
	if (newState == m_stateFactory.end()) { return; }
	BaseState* state = newState->second();
	state->m_view = m_shared->m_wind->GetRenderWindow()->getDefaultView();
	m_states.emplace_back(type, state);
	state->OnCreate();
	state->setupGlobalShader();
}

void StateManager::removeState(const StateType& type)
{
	for (auto itr = m_states.begin(); itr != m_states.end(); itr++)
	{
		if (itr->first == type)
		{
			itr->second->OnDestroy();
			delete itr->second;
			m_states.erase(itr);
			m_shared->m_soundManager->RemoveState(type);
			return;
		}
	}
}