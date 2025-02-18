#pragma once

#include "../Renderer/render_data.h"
#include "component.h"
#include <SDL3/SDL.h>

class Wall {

private:
	Transform	_transform;
	Collision	_collision;
	Sprite		_sprite;

public:
	Wall(vec2 position);
	~Wall();
	RenderData CreateRenderData() const;
	SDL_FRect GetHitbox() const;
	bool IsActive() const;
};
