#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "SpriteSheet.h"
#include "StateManager.h"
#include "box2d/box2d.h"
#include "Entity.h"
#include "SFMLDebugDraw.h"

/* The primary application state, this will be responsible for logic that
can't be abstracted to other objects, as well as whatever else you want it 
to do. */

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

	void MainMenu(EventDetails* details); //Switch to the Main Menu state
	void Pause(EventDetails* details); //Switch to the Paused state

protected:
	void setupGlobalShader() override;
	void updateGlobalShader(const sf::Texture* tex) override;

private:
	void zoom(EventDetails* details); //Bound to middle mouse, zooms in and out the view
	void toggleDebug(EventDetails* details); //Toggles the drawing of Box2D collision shapes for debug purposes

	sf::Texture* m_backTex;
	sf::Sprite m_background;

	sf::Clock m_clock;

	b2World* m_world;
	TestShip* m_ship;
	Entity* m_player;

	b2ThreadPoolTaskExecutor m_taskExecutor;
	SFMLDebugDraw m_debugDraw;

	bool m_debugDrawMode;
};