#include "scene.h"
#include "player.h"
#include "game.h"
#include "render_data.h"
#include "renderer.h"

namespace scene {

	std::vector<object> _objects;

	void update(float delta_time) {

	}

	void upload_render_data() {

		for (const object& obj : _objects) {
			
			render_data data = render_data();
			data.x = obj.x;
			data.y = obj.y;
			data.w = obj.w;
			data.h = obj.h;
			data.color = color_type(255, 255, 255, 255);
			
			renderer::submit_render_data(data);
		}
	}

	void create_object(float x, float y) {

		object r = object(x, y, 20.f, 20.f);
		_objects.push_back(r);
	}

	const std::vector<object>& get_objects() {
		return _objects;
	}

}