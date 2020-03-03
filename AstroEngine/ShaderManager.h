#pragma once
#include "ResourceManager.h"
#include "SFML/Graphics/Shader.hpp"

/* Manages all shader resources, is of type ResourceManager. */

class ShaderManager : public ResourceManager<ShaderManager, sf::Shader>
{
public:
	ShaderManager() : ResourceManager("Config/Shaders.cfg") {}

	sf::Shader* Load(const std::string& path) //Loads a shader from a path given by the Shaders.cfg file
	{
		sf::Shader* shader = new sf::Shader();
		if (!shader->loadFromFile(path + ".vert", path + ".frag"))
		{
			delete shader;
			shader = nullptr;
			std::cerr << "! Failed to load shader: " << path << std::endl;
		}
		return shader;
	}
};

