#include "scene.h"
#include "projectile.h"
#include "../Player/player.h"
#include "../Core/input.h"
#include "../Renderer/renderer.h"

#include <vector>
#include <iostream>

namespace Scene {

	Player* _player = nullptr;
	std::vector<Projectile> _projectiles;
	std::vector<Wall> _walls;
	std::vector<std::vector<int>> _map;
	std::vector<const char*> _map2;

	void CreateMap() {

		_map = {
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 2, 1, 1, 1, 1, 1, 0, 0, 0},
			{0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 4, 1, 1, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		};

		for (int i = 0; i < _map.size(); ++i) {
			for (int j = 0; j < _map[0].size(); ++j) {

				if (_map[i][j] == 1) AddWall(vec2(j * 64.f, i * 64.f), WallType::FRONT);
				else if (_map[i][j] == 2) AddWall(vec2(j * 64.f, i * 64.f), WallType::CORNER_LEFT);
				else if (_map[i][j] == 3) AddWall(vec2(j * 64.f, i * 64.f), WallType::MIDDLE_TOP);
				else if (_map[i][j] == 4) AddWall(vec2(j * 64.f, i * 64.f), WallType::HALF_LEFT);
				else if (_map[i][j] == 5) AddWall(vec2(j * 64.f, i * 64.f), WallType::CORNER_RIGHT);
				else if (_map[i][j] == 6) AddWall(vec2(j * 64.f, i * 64.f), WallType::HALF_RIGHT);
				else if (_map[i][j] == 7) AddWall(vec2(j * 64.f, i * 64.f), WallType::MIDDLE_FRONT);
			}
		}
	}

	void CreatePlayer() {
		_player = new Player();
	}

	Player* GetPlayer() {
		return _player;
	}

	void AddProjectile(vec2 position, vec2 direction, float angle) {
		_projectiles.push_back(Projectile(position, direction, angle));
	}

	void AddWall(vec2 position, WallType type) {

		float gridSize = 32.f;
		float posX = floor(position.x / gridSize) * gridSize;
		float posY = floor(position.y / gridSize) * gridSize;
		vec2 pos = vec2(posX, posY);

		_walls.push_back(Wall(pos, type));
	}

	void Update(float deltaTime) {

		RemoveExpired();

		_player->Update(deltaTime);

		for (Projectile& p : _projectiles) {
			p.Update(deltaTime);
		}

		UpdateCollision();

		UploadRenderData();
	}

	void UpdateCollision() {

		for (Projectile& p : _projectiles) {
			for (const Wall& w : _walls) {

				if (IsRectInsideRect(p.GetHitbox(), w.GetHitbox())) {
					p.Explode();
				}
			}
		}
	}

	void UploadRenderData() {

		for (const Projectile& p : _projectiles) {

			RenderData data = p.CreateRenderData();
			Renderer::SubmitRenderData(data);
		}

		for (const Wall& w : _walls) {

			RenderData data = w.CreateRenderData();
			Renderer::SubmitRenderData(data);
		}
	}

	void RemoveExpired() {

		_projectiles.erase(std::remove_if(_projectiles.begin(), _projectiles.end(),
			[](const Projectile& projectile) { return projectile.GetRemove(); }), _projectiles.end());
	}

	void DisplayDebug() {

		Renderer::DrawRect(_player->GetHitbox(), false);
		Renderer::DrawRect(_player->GetWallHitbox(), false);

		for (const Projectile& p : _projectiles) {

			Renderer::DrawRect(p.GetHitbox(), false);
		}

		for (const Wall& w : _walls) {

			Renderer::DrawRect(w.GetHitbox(), false);
		}

		Renderer::DrawLine(_player->GetPosition(), Input::GetMousePos());

		/*for (int i = 0; i < 60; ++i) {
			for (int j = 0; j < 34; ++j) {

				vec2 p = vec2(16.f + i * 32.f, 16.f + j * 32.f);
				bool inside = false;

				for (const Wall& w : _walls) {

					if (IsPointInsideRect(w.rect, p)) {
						inside = true;
					}
				}

				if (!inside) Renderer::DrawPoint(p);
			}
		}*/
	}

	bool IsPointInsideRect(SDL_FRect rect, vec2 point) {

		if (
			point.x >= rect.x &&
			point.x <= (rect.x + rect.w) &&
			point.y >= rect.y &&
			point.y <= (rect.y + rect.h)
			) return true;

		return false;
	}

	bool IsRectInsideRect(SDL_FRect a, SDL_FRect b) {

		if (
			a.x + a.w >= b.x &&
			a.x <= b.x + b.w &&
			a.y + a.h >= b.y &&
			a.y <= b.y + b.h
			) return true;

		return false;
	}

	vec2 MoveController(SDL_FRect xAxis, SDL_FRect yAxis) {

		vec2 move = vec2(1.f, 1.f);

		for (const Wall& w : _walls) {

			if (IsRectInsideRect(xAxis, w.GetHitbox())) {
				move.x = 0.f;
			}

			if (IsRectInsideRect(yAxis, w.GetHitbox())) {
				move.y = 0.f;
			}
		}

		return move;
	}

}