#include "scene.h"
#include "player.h"
#include "game.h"
#include "../Renderer/render_data.h"
#include "../Renderer/renderer.h"
#include "../Core/backend.h"
#include "../Core/physics.h"

#include <iostream>

// Rewrite projectile class and separate it from other objects

namespace scene {

	std::vector<std::unique_ptr<game_object>> _objects;

	void update(float delta_time) {

		remove_expired();

		for (const std::unique_ptr<game_object>& object : _objects) {

			object->update(delta_time);
		}

		update_collision();
		update_trace();

		upload_render_data();
	}

	void update_collision() {

		for (int i = 0; i < _objects.size(); ++i) {

			//std::cout << i << "\n";

			if (_objects[i]->is_projectile() && _objects[i]->_active == true) {
				
				for (int j = 0; j < _objects.size(); ++j) {

					if (_objects[j]->is_wall()) {

						if (physics::check_collision(_objects[i]->_hitbox, _objects[j]->_hitbox)) {

							_objects[i]->collision();
							_objects[i]->_active = false;
						}
					}

					else if (_objects[j]->is_enemy()) {

						if (physics::check_collision(_objects[i]->_hitbox, _objects[j]->_hitbox)) {

							_objects[i]->_active = false;
							_objects[i]->collision();
							_objects[j]->damage();
						}
					}
				}
			}

		}
	}

	void update_trace() {

		for (int i = 0; i < _objects.size(); ++i) {

			if (_objects[i]->is_enemy()) {
				float player_x = game::get_player_by_id(0)->get_x();
				float player_y = game::get_player_by_id(0)->get_y();

				//_objects[i]
			}
		}
	}

	void upload_render_data() {

		for (const std::unique_ptr<game_object>& object : _objects) {
			
			renderer::submit_render_data(object->create_render_data());
		}
	}

	void create_bullet(mth::vec2 position, mth::vec2 direction, float angle) {

		_objects.push_back(std::make_unique<projectile>(position, direction, angle));
	}

	void create_wall(mth::vec2 position) {

		_objects.push_back(std::make_unique<wall>(position));
	}

	void create_enemy(mth::vec2 position) {

		_objects.push_back(std::make_unique<enemy>(position));
	}

	void remove_expired() {

		_objects.erase(std::remove_if(_objects.begin(), _objects.end(),
			[](const std::unique_ptr<game_object>& object) { return object->get_remove(); }), _objects.end());
	}

	void display_debug() {

		for (const std::unique_ptr<game_object>& object : _objects) {

			render_data data = render_data();

			data.dst_rect = object->_hitbox;
			data.filled = false;
			data.layer = 100;

			renderer::submit_render_data(data);
		}
	}

	size_t get_game_object_count() {
		return _objects.size();
	}

}
