#pragma once
#include "Anim_Base.h"
#include "Directions.h"

/* A directional animation, assumes the row beneath it
is the same animation being played in the opposite direction. */

class Anim_Directional : public Anim_Base
{
protected:
	void frameStep();
	void cropSprite();
	void readIn(std::stringstream& stream);
};

