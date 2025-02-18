#pragma once

//#include "../vec2.h"
#include "component.h"
#include "../Renderer/render_data.h"

#include <SDL3/SDL.h>

class Projectile {

private:
	Transform	_transform;
	Motion		_motion;
	Collision	_collision;
	Sprite		_sprite;
	Animation	_animation;

	float		_lifeTime;
	bool		_exploded;
	bool		_prevExploded;
	bool		_remove;

public:
	Projectile(vec2 position, vec2 direction, float angle);
	void Update(float deltaTime);
	void UpdateAnimation(float deltaTime);
	RenderData CreateRenderData() const;
	void Explode();
	bool GetRemove() const;
	SDL_FRect GetHitbox() const;
};