#pragma once

#include "../vec2.h"
#include <SDL3/SDL.h>

class Player;

namespace Scene {

	void CreatePlayer();
	Player* GetPlayer();
	void AddProjectile(vec2 position, vec2 direction, float angle);
	void AddWall(vec2 position);

	void Update(float deltaTime);
	void UpdateCollision();
	void UploadRenderData();
	void RemoveExpired();
	void DisplayDebug();

	// Where does this go?
	bool IsPointInsideRect(SDL_FRect rect, vec2 point);
	bool IsRectInsideRect(SDL_FRect a, SDL_FRect b);

	// This works but it's disgusting so get rid of it
	vec2 MoveController(SDL_FRect xAxis, SDL_FRect yAxis);
}