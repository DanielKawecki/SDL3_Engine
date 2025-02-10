#pragma once

#include "game_object.h"

#include <vector>
#include <memory>

//struct object {
//	float x, y, w, h;
//
//	object() = default;
//
//	object(float x, float y, float w, float h)
//		: x(x), y(y), w(w), h(h) {}
//};

namespace scene {

	void update(float delta_time);
	void upload_render_data();

	void create_object(float x, float y);
	void create_bullet(mth::vec2 position, mth::vec2 direction);

}