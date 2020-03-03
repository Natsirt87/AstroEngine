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

/* Manages all the states, responsible for their creation, removal,
activation, deactivation, update, draw, etc. */
class StateManager
{
public:
	StateManager(SharedContext* shared);
	~StateManager();

	void Update(const sf::Time& time); //Updates all relevant states
	void UpdateGlobalShader(const sf::Texture* tex); //Updates all state global shaders
	void Draw(); //Draw all relevant states


	void ProcessRequests(); //Removes states that are up for removal

	SharedContext* GetContext(); //Gets the shared context
	bool HasState(const StateType& type); //Checks whether a state exists

	void SwitchTo(const StateType& type); //Switches to a state
	void Remove(const StateType& type); //Removes a state

	sf::Shader* GetGlobalShader();
	const PostEffectSettings& GetPostEffects();

	float GetCurrentZoom();

private:
	void createState(const StateType& type); //State creation helper method
	void removeState(const StateType& type); //State removal helper method

	template<class T>
	void registerState(const StateType& type) //Registers a state class with a state type for the state factory
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