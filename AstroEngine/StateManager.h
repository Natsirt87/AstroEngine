#pragma once
#include <vector>
#include <unordered_map>
#include "State_Intro.h"
#include "State_Game.h"
#include "State_MainMenu.h"
#include "State_Paused.h"
#include "BaseState.h"
#include "SharedContext.h"
#include "EventManager.h"

enum class StateType{ Intro = 1, MainMenu, Game, Paused, GameOver, Credits };

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class SharedContext;
class StateManager
{
public:
	StateManager(SharedContext* shared);
	~StateManager();

	void Update(const sf::Time& time);
	void Draw();

	void ProcessRequests();

	SharedContext* GetContext();
	bool HasState(const StateType& type);

	void SwitchTo(const StateType& type);
	void Remove(const StateType& type);

private:
	void createState(const StateType& type);
	void removeState(const StateType& type);

	template<class T>
	void registerState(const StateType& type)
	{
		m_stateFactory[type] = [this]() -> BaseState*
		{
			return new T(this);
		};
	}

	SharedContext* m_shared;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};