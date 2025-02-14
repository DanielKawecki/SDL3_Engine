#pragma once

#include "render_data.h"
#include "mth.h"
#include <SDL3/SDL.h>

class game_object {
public:

	mth::vec2		_position;
	SDL_FRect		_hitbox;
	SDL_FRect		_src_rect;
	SDL_FRect		_dst_rect;
	SDL_Texture*	_texture;
	SDL_FlipMode	_flip;
	animation_info	_animation;
	float			_accumulator;
	float			_angle;
	bool			_remove;
	bool			_active;

	game_object();
	virtual void update(float delta_time);
	virtual void collision();
	virtual void damage();
	virtual ~game_object() = default;
	void update_animation(float delta_time);
	render_data create_render_data() const;
	bool get_remove() const;

	virtual bool is_wall() const;
	virtual bool is_projectile() const;
	virtual bool is_enemy() const;
};

class wall : public game_object {
public:

	wall(mth::vec2 position);
	void update(float delta_time) override;
	bool is_wall() const override;
};

class projectile : public game_object {
private:
	
	mth::vec2		_displacement;
	float			_speed = 800.f;
	float			_life_time = 0.8f;
	float			_accumulator = 0.f;
	bool			_prev_explode = false;
	bool			_explode = false;
	//animation_info	_animation;

public:

	projectile(mth::vec2 position, mth::vec2 direction, float angle);
	void update(float delta_time) override;
	void collision() override;
	bool is_projectile() const override; 
};

class enemy : public game_object {
private:

	int				_health = 100;
	float			_accumulator = 0.f;
	//animation_info	_animation;

public:
	enemy(mth::vec2 position);
	void update(float delta_time) override;
	void collision() override;
	void damage() override;
	bool is_enemy() const override;
};