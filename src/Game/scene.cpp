#include "scene.h"
#include "projectile.h"
#include "player.h"
#include "../Renderer/renderer.h"

#include <vector>
#include <iostream>

namespace Scene {

	Player* _player = nullptr;
	std::vector<Projectile> _projectiles;

	void CreatePlayer() {
		_player = new Player();
	}

	Player* GetPlayer() {
		return _player;
	}

	void AddProjectile(vec2 position, vec2 direction, float angle) {
		_projectiles.push_back(Projectile(position, direction, angle));
	}

	void Update(float deltaTime) {

		RemoveExpired();

		_player->Update(deltaTime);

		for (Projectile& p : _projectiles) {
			p.Update(deltaTime);
		}

		UploadRenderData();
	}

	void UploadRenderData() {

		for (const Projectile& p : _projectiles) {

			RenderData data = p.CreateRenderData();
			Renderer::SubmitRenderData(data);
		}
	}

	void RemoveExpired() {

		_projectiles.erase(std::remove_if(_projectiles.begin(), _projectiles.end(),
			[](const Projectile& projectile) { return projectile.GetRemove(); }), _projectiles.end());
	}

	void DisplayDebug() {

		RenderData data = RenderData();

		data.dstRect = _player->GetHitbox();
		data.filled = false;
		data.layer = 100;

		Renderer::SubmitRenderData(data);

		for (const Projectile& p : _projectiles) {
			
		}
	}

}