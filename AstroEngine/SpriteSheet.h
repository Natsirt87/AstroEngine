#pragma once
#include <unordered_map>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "TextureManager.h"
#include "Anim_Directional.h"
#include "Anim_Standard.h"
#include "Utilities.h"
#include "Anim_Base.h"
#include "BaseComponent.h"

/* The component responsible for animation, contains all sorts of animation
functionality. Uses a spritesheet (if you couldn't tell from the name). */

using Animations = std::unordered_map<std::string, Anim_Base*>;

class SpriteSheet : public BaseComponent
{
public:
	SpriteSheet(TextureManager* textMgr, Entity* owner);
	~SpriteSheet();

	void CropSprite(const sf::IntRect& rect);
	sf::Vector2i GetSpriteSize()const;
	sf::Vector2f GetSpritePosition()const;
	float GetSpriteRotation()const;
	void SetSpriteSize(const sf::Vector2i& size);
	void SetSpritePosition(const sf::Vector2f& pos);
	void SetSpriteRotation(const float angle);

	void SetDirection(const Direction& dir);
	Direction GetDirection()const;

	bool LoadSheet(const std::string& file);
	void ReleaseSheet();

	Anim_Base* GetCurrentAnim();
	bool SetAnimation(const std::string& name,
		const bool& play = false,
		const bool& loop = false);
	bool SetAnimation(const std::string& name,
		const bool& play,
		const bool& nextLoop,
		const std::string& nextAnim);

	void Update(const float& dt);
	void Draw(sf::RenderWindow* wnd);

private:
	std::string m_texture;
	sf::Sprite m_sprite;
	sf::Vector2i m_spriteSize;
	sf::Vector2f m_spriteScale;
	Direction m_direction;

	std::string m_animType;
	Animations m_animations;
	Anim_Base* m_animationCurrent;

	TextureManager* m_textureManager;
};

