#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "SpriteSheet.h"
#include "StateManager.h"
#include "box2d/box2d.h"
#include "Entity.h"
#include "SFMLDebugDraw.h"

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
	void toggleDebug(EventDetails* details);

	sf::Texture* m_backTex;
	sf::Sprite m_background;

	b2World* m_world;
	TestShip* m_ship;
	Entity* m_player;

	b2ThreadPoolTaskExecutor m_taskExecutor;
	SFMLDebugDraw m_debugDraw;

	bool m_debugDrawMode;
};

