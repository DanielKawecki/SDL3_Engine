#pragma once

#include <SDL3/SDL.h>
#include "../vec2.h"

enum class PlayerState {
	idle,
	walk,
	attack
};

enum class PlayerFacing {
	left,
	right
};

class Player {

private:
	int				_frameIndex = 0;
	float			_speed = 250.f;
	float			_accumulator = 0.f;
	float			_frameTime = 0.08f;
	int				_frameCount = 10;
	bool			_busy = false;
	float			_angle = 0.f;
	vec2			_position = vec2(100.f, 100.f);
	vec2			_mouseDirection = vec2(0.f, 0.f);
	PlayerState		_state = PlayerState::idle;
	PlayerFacing	_direction = PlayerFacing::right;
	SDL_Texture*	_texture = nullptr;
	SDL_FRect		_hitbox = { 0.f, 0.f, 0.f, 0.f };

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
	float GetAngle() const;
	const SDL_FRect& GetHitbox() const;
};