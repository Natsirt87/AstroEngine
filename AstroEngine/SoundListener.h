#pragma once
#include "BaseComponent.h"
#include "SFML/Audio/Listener.hpp"

class SoundListener : public BaseComponent
{
public:
	SoundListener(Entity* owner);
	~SoundListener();

	void Update(float zoom);
	void SetDirection(const sf::Vector3f& dir);
	void SetGlobalVolume(float volume);

	const sf::Vector3f& GetDirection();
	float GetGlobalVolume();

private:
	float m_globalVolume;
};

