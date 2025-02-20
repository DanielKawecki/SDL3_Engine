#pragma once

#include <SDL3/SDL.h>
#include <string>
#include "../Game/game.h"

namespace UIBackEnd {

	void BlitText(std::string text, float posX, float posY);
	void BlitTexture(std::string name, float posX, float posY, float sizeX, float sizeY);

}