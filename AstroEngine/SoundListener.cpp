#include "SoundListener.h"

SoundListener::SoundListener(Entity* owner) : BaseComponent(owner), m_globalVolume(50.f) {}

SoundListener::~SoundListener() 
{
	sf::Listener::setDirection(sf::Vector3f(0.f, 0.f, -1.f));
}

void SoundListener::Update(float zoom)
{
	float yPos = 800 * zoom;

	sf::Vector2f pos = GetOwner()->GetPosition();
	sf::Vector3f listenerPos = sf::Vector3f(pos.x, yPos, pos.y);
	sf::Listener::setPosition(listenerPos);
}

void SoundListener::SetDirection(const sf::Vector3f& dir)
{
	sf::Listener::setDirection(dir);
}

void SoundListener::SetGlobalVolume(float volume)
{
	sf::Listener::setGlobalVolume(volume);
}

const sf::Vector3f& SoundListener::GetDirection()
{
	return sf::Listener::getDirection();
}

float SoundListener::GetGlobalVolume()
{
	return sf::Listener::getGlobalVolume();
}
