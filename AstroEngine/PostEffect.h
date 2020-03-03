#pragma once
#include <SFML/System/NonCopyable.hpp>

namespace sf
{
	class RenderTarget;
	class RenderTexture;
	class Shader;
}

//An effect made up of multiple shaders, when just one won't do the trick

class PostEffect : sf::NonCopyable
{
public:
	virtual ~PostEffect();
	virtual void apply(const sf::RenderTexture& input, sf::RenderTarget& output) = 0;

protected:
	static void applyShader(const sf::Shader& shader, sf::RenderTarget& output);
};

