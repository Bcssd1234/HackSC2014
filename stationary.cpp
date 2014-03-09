#include "stationary.h"
#include "definitions.h"

void Stationary::advance(int phase)
{
	if (phase == 1)
	{
		moveBy(0, SCROLL_MOVE_DIST);
	}
}

bool Stationary::expired()
{
	return this->y() > VIEW_HEIGHT + EXTRA_SCENE_SPACE;
}
