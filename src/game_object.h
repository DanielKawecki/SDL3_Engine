#pragma once

#include "render_data.h"
#include "mth.h"
#include <SDL3/SDL.h>

class game_object {
public:
	mth::vec2		_position;
	SDL_FRect		_rect;
	float			_angle;

	virtual void update(float delta_time);
	virtual render_data create_render_data() const;
	virtual ~game_object() = default;
};

//class wall : public game_object {
//public:
//	void update(float delta_time) override;
//	void upload_render_data() const override;
//};

class bullet : public game_object {
public:

	mth::vec2 _displacement;
	float _speed = 400.f;

	bullet(mth::vec2 position, mth::vec2 direction);
	void update(float delta_time) override;
	render_data create_render_data() const override;
};