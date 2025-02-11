#pragma once

#include "render_data.h"
#include "mth.h"
#include <SDL3/SDL.h>

class game_object {
public:

	mth::vec2		_position;
	SDL_FRect		_rect;
	float			_angle;
	bool			_remove;

	virtual void update(float delta_time);
	virtual render_data create_render_data() const;
	virtual ~game_object() = default;
	bool get_remove() const;
};

//class wall : public game_object {
//public:
//	void update(float delta_time) override;
//	void upload_render_data() const override;
//};

class bullet : public game_object {
private:
	
	mth::vec2 _displacement;
	float _speed = 800.f;
	float _life_time = 0.5f;
	float _accumulator = 0.f;
	bool _explode = false;
	animation_info _animation;
	SDL_Texture* _texture = nullptr;
	SDL_FRect _dst_rect = { 10.f, 10.f };

public:

	bullet(mth::vec2 position, mth::vec2 direction, float angle);
	void update(float delta_time) override;
	render_data create_render_data() const override;
};