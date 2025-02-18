#pragma once

#include <SDL3/SDL.h>
#include "../vec2.h"
#include "component.h"

enum class PlayerState {
	IDLE,
	WALK,
	ATTACK
};

enum class PlayerFacing {
	LEFT,
	RIGHT
};

class Player {

private:
	Transform		_transform;
	Motion			_motion;
	Collision		_collision;
	Sprite			_sprite;
	Animation		_animation;

	SDL_FRect		_wallHitbox;
	vec2			_mouseDirection = vec2(0.f, 0.f);
	PlayerState		_state = PlayerState::IDLE;
	PlayerFacing	_direction = PlayerFacing::RIGHT;
	bool			_busy = false;

public:
	Player();
	~Player();

	void Update(float delta_time);
	void UpdateMovement(float delta_time);
	void UpdateFrame(float delta_time);
	void UpdateMouse();
	void UploadRenderData() const;

	float GetX() const;
	float GetY() const;
	vec2 GetPosition() const;
	float GetAngle() const;
	SDL_FRect GetHitbox() const;
	SDL_FRect GetWallHitbox() const;
};