#include "scene.h"
#include "player.h"
#include "game.h"
#include "render_data.h"
#include "renderer.h"

namespace scene {

	std::vector<std::unique_ptr<game_object>> _objects;

	void update(float delta_time) {

		for (const std::unique_ptr<game_object>& object : _objects) {

			object->update(delta_time);
		}
	}

	void upload_render_data() {

		for (const std::unique_ptr<game_object>& object : _objects) {
			
			renderer::submit_render_data(object->create_render_data());
			/*render_data data = render_data();

			data.src_rect = { 0.f, 0.f, 0.f, 0.f };
			data.dst_rect = { obj.positionx, obj.positiony, obj.w, obj.h };
			data.color = SDL_Color(255, 255, 255, 255);*/
			
			//renderer::submit_render_data(data);
		}
	}

	void create_object(float x, float y) {

		//object r = object(x, y, 20.f, 20.f);
		//_objects.push_back(std::make_unique<bullet>());
	}

	void create_bullet(mth::vec2 position, mth::vec2 direction) {

		_objects.push_back(std::make_unique<bullet>(position, direction));
	}

}
