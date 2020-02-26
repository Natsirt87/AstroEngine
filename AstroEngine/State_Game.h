#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "SpriteSheet.h"
#include "StateManager.h"
#include "box2d/box2d.h"
#include "BaseEntity.h"

class PhysicsBox;
class TestShip;
class State_Game : public BaseState
{
public:
	State_Game(StateManager* stateManager);
	~State_Game();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& time);
	void Draw();

	void MainMenu(EventDetails* details);
	void Pause(EventDetails* details);

private:
	void zoom(EventDetails* details);

	sf::Texture* m_backTex;
	sf::Sprite m_background;

	b2World* m_world;
	TestShip* m_ship;
	BaseEntity* m_player;
};

