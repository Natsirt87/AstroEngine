#pragma once
#include "ResourceManager.h"
#include "SFML/Audio/SoundBuffer.hpp"

class AudioManager : public ResourceManager<AudioManager, sf::SoundBuffer>
{
public:
	AudioManager() : ResourceManager("Config/Audio.cfg") {}

	sf::SoundBuffer* Load(const std::string& path)
	{
		sf::SoundBuffer* sound = new sf::SoundBuffer();
		if (!sound->loadFromFile(path))
		{
			delete sound;
			sound = nullptr;
			std::cerr << "! Failed to load sound: "
				<< path << std::endl;
		}
		return sound;
	}
};

