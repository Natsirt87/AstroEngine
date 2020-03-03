#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

struct PostEffectSettings
{
	PostEffectSettings() : m_bloom(false) {}

	bool m_bloom;
};

class StateManager;

/* The parent of all application states, contains the basic
functionality common to all states. */
class BaseState
{
	friend class StateManager;
public:
	BaseState(StateManager* stateManager)
		: m_stateMgr(stateManager), m_transparent(false), 
		m_transcendent(false) {}
	virtual ~BaseState() {}

	virtual void OnCreate() = 0; //Called when state is created
	virtual void OnDestroy() = 0; //Called when state is destroyed

	virtual void Activate() = 0; //Called when state is activated (the top state)
	virtual void Deactivate() = 0; //Called when state is deactivated (not the top state)

	virtual void Update(const sf::Time& time) = 0; //Called every frame, meant for non-visual updating
	
	virtual void Draw() = 0; //Called every frame, meant for drawing

	void SetTransparent(const bool& transparent) //Sets whether the state is transparent
	{
		m_transparent = transparent;
	}

	void SetTranscendent(const bool& transcendence) //Sets whether the state is transcendent
	{
		m_transcendent = transcendence;
	}

	bool IsTransparent()const { return m_transparent; }
	bool IsTranscendent()const { return m_transcendent; }
	
	StateManager* GetStateManager() { return m_stateMgr; }
	sf::View& GetView() { return m_view; }

protected:
	virtual void setupGlobalShader() {}
	virtual void updateGlobalShader(const sf::Texture* tex) {}

	StateManager* m_stateMgr;
	sf::View m_view;

	sf::Shader* m_globalShader;
	PostEffectSettings m_postEffects;

	bool m_transparent;
	bool m_transcendent;
	float m_zoom = 1;
};