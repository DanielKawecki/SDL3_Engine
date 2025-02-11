#include "scene.h"
#include "player.h"
#include "game.h"
#include "render_data.h"
#include "renderer.h"
#include "backend.h"

namespace scene {

	std::vector<std::unique_ptr<game_object>> _objects;

	void update(float delta_time) {

		remove_expired();

		for (const std::unique_ptr<game_object>& object : _objects) {

			object->update(delta_time);
		}

		update_collision();

		upload_render_data();
	}

	void update_collision() {

		for (const std::unique_ptr<game_object>& object : _objects) {

			//if (object->_position.x > backend::get_screen_width()) object->_explode
		}
	}

	void upload_render_data() {

		for (const std::unique_ptr<game_object>& object : _objects) {
			
			renderer::submit_render_data(object->create_render_data());
		}
	}

	void create_bullet(mth::vec2 position, mth::vec2 direction, float angle) {

		_objects.push_back(std::make_unique<bullet>(position, direction, angle));
	}

	void remove_expired() {

		_objects.erase(std::remove_if(_objects.begin(), _objects.end(),
			[](const std::unique_ptr<game_object>& object) { return object->get_remove(); }), _objects.end());
	}

	void display_debug() {

		for (const std::unique_ptr<game_object>& object : _objects) {

			render_data data = render_data();

			data.dst_rect = { object->_position.x - 8.f, object->_position.y - 8.f, 16.f, 16.f };
			data.filled = false;
			data.layer = 100;

			renderer::submit_render_data(data);
		}
	}

	bool get_game_object_count() {
		return _objects.size();
	}

}
