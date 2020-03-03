#include "SpriteSheet.h"
#include "Anim_Base.h"
#include "SFML/Graphics.hpp"

SpriteSheet::SpriteSheet(TextureManager* textMgr, Entity* owner) 
	: BaseComponent(owner), m_textureManager(textMgr), 
	m_animationCurrent(nullptr),
	m_spriteScale(1.f, 1.f), m_direction(Direction::Right) {}

SpriteSheet::~SpriteSheet() { ReleaseSheet(); }

void SpriteSheet::CropSprite(const sf::IntRect& rect) { m_sprite.setTextureRect(rect); }
sf::Vector2i SpriteSheet::GetSpriteSize() const { return m_spriteSize; }
sf::Vector2f SpriteSheet::GetSpritePosition() const { return m_sprite.getPosition(); }

float SpriteSheet::GetSpriteRotation() const { return m_sprite.getRotation(); }

void SpriteSheet::SetSpriteSize(const sf::Vector2i& size)
{
	m_spriteSize = size;
	m_sprite.setOrigin(m_spriteSize.x / 2, m_spriteSize.y / 2);
}

void SpriteSheet::SetSpritePosition(const sf::Vector2f& pos) { m_sprite.setPosition(pos); }

void SpriteSheet::SetSpriteRotation(const float angle) { m_sprite.setRotation(angle); }

void SpriteSheet::SetDirection(const Direction& dir)
{
	if (dir == m_direction) { return; }
	m_direction = dir;
	m_animationCurrent->cropSprite();
}

Direction SpriteSheet::GetDirection() const { return Direction(); }

bool SpriteSheet::LoadSheet(const std::string& file)
{
	std::ifstream sheet;
	sheet.open(file);

	if (sheet.is_open())
	{
		ReleaseSheet();
		std::string line;
		while (std::getline(sheet, line))
		{
			if (line[0] == '|') { continue; }
			std::stringstream keystream(line);
			std::string type;
			keystream >> type;

			if (type == "Texture")
			{
				if (m_texture != "")
				{
					std::cerr << "! Duplicate texture entries in: " << file << std::endl;
					continue;
				}
				std::string texture;
				keystream >> texture;

				if (!m_textureManager->RequireResource(texture))
				{
					std::cerr << "! Could not set up the texture: " << texture << std::endl;
					continue;
				}
				m_texture = texture;
				m_sprite.setTexture(*m_textureManager->GetResource(m_texture));
			}
			else if (type == "Size")
			{
				keystream >> m_spriteSize.x >> m_spriteSize.y;
				SetSpriteSize(m_spriteSize);
			}
			else if (type == "Scale")
			{
				keystream >> m_spriteScale.x >> m_spriteScale.y;
				m_sprite.setScale(m_spriteScale);
			}
			else if (type == "AnimationType")
			{
				keystream >> m_animType;
			}
			else if (type == "Animation")
			{
				std::string name;
				keystream >> name;

				if (m_animations.find(name) != m_animations.end())
				{
					std::cerr << "! Duplicate animation(" << name << ") in: " << file << std::endl;
					continue;
				}
				Anim_Base* anim = nullptr;
				if (m_animType == "Directional")
				{
					anim = new Anim_Directional();
				}
				else if (m_animType == "Standard")
				{
					anim = new Anim_Standard();
				}
				else
				{
					std::cerr << "! Unknown animation type: " << m_animType << std::endl;
					continue;
				}

				keystream >> *anim;
				anim->SetSpriteSheet(this);
				anim->SetName(name);
				anim->Reset();
				m_animations.emplace(name, anim);

				if (m_animationCurrent) { continue; }
				m_animationCurrent = anim;
				m_animationCurrent->Play();
			}
		}
		sheet.close();
		return true;
	}
	std::cerr << "! Failed loading spritesheet: " << file << std::endl;
	return false;
}

void SpriteSheet::ReleaseSheet()
{
	m_textureManager->ReleaseResource(m_texture);
	m_animationCurrent = nullptr;
	while (m_animations.begin() != m_animations.end())
	{
		delete m_animations.begin()->second;
		m_animations.erase(m_animations.begin());
	}
}

Anim_Base* SpriteSheet::GetCurrentAnim() { return m_animationCurrent; }

bool SpriteSheet::SetAnimation(const std::string& name, const bool& play, const bool& loop)
{
	auto itr = m_animations.find(name);

	if (itr == m_animations.end()) { return false; }
	if (itr->second == m_animationCurrent) { return false; }
	if (m_animationCurrent) { m_animationCurrent->Stop(); }

	m_animationCurrent = itr->second;
	m_animationCurrent->SetLooping(loop);
	m_animationCurrent->SetNextAnim("");
	if (play) { m_animationCurrent->Play(); }
	m_animationCurrent->cropSprite();
	return true;
}

bool SpriteSheet::SetAnimation(const std::string& name, const bool& play, const bool& nextLoop, const std::string& nextAnim)
{
	auto itr = m_animations.find(name);

	if (itr == m_animations.end()) { return false; }
	if (itr->second == m_animationCurrent) { return false; }
	if (m_animationCurrent) { m_animationCurrent->Stop(); }

	m_animationCurrent = itr->second;
	m_animationCurrent->SetLooping(false);
	m_animationCurrent->SetNextLooping(nextLoop);
	m_animationCurrent->SetNextAnim(nextAnim);
	if (play) { m_animationCurrent->Play(); }
	m_animationCurrent->cropSprite();
	return true;
}

void SpriteSheet::Update(const float& dt)
{
	m_animationCurrent->Update(dt);
}

void SpriteSheet::Draw(sf::RenderTexture* rnd)
{
	rnd->draw(m_sprite);
}
