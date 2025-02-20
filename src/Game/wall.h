#pragma once

#include "../Renderer/render_data.h"
#include "component.h"
#include <SDL3/SDL.h>

enum class WallType {
	FRONT,
	CORNER_LEFT,
	CORNER_RIGHT,
	HALF_LEFT,
	HALF_RIGHT,
	MIDDLE_TOP,
	MIDDLE_FRONT
};

class Wall {

private:
	Transform	_transform;
	Collision	_collision;
	Sprite		_sprite;
	WallType	_type;

	void Setup();

public:
	Wall(vec2 position, WallType type);
	~Wall();
	RenderData CreateRenderData() const;
	SDL_FRect GetHitbox() const;
	bool IsActive() const;
};
