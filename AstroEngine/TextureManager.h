#pragma once
#include "ResourceManager.h"
#include "SFML/Graphics/Texture.hpp"

/* Manages all texture resources, is of type ResourceManager. */

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
	TextureManager(): ResourceManager("Config/Textures.cfg") {}                   

	sf::Texture* Load(const std::string& path) //Loads a texture from a path given by the Textures.cfg file
	{
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile(path))
		{
			delete texture;
			texture = nullptr;
			std::cerr << "! Failed to load texture: " << path << std::endl;
		}
		return texture;
	}
};

