#pragma once
#include "Anim_Base.h"

/* A standard animation, nothing fancy going on. */

class Anim_Standard : public Anim_Base
{
protected:
	void frameStep();
	void cropSprite();
	void readIn(std::stringstream& stream);
};

