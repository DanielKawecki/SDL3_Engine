#pragma once

#include <vector>

struct object {
	float x, y, w, h;

	object() = default;

	object(float x, float y, float w, float h)
		: x(x), y(y), w(w), h(h) {}
};

namespace scene {

	void update(float delta_time);
	void upload_render_data();

	void create_object(float x, float y);
	const std::vector<object>& get_objects();

}