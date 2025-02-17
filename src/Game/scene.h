#pragma once

#include "../vec2.h"

class Player;

namespace Scene {

	void CreatePlayer();
	Player* GetPlayer();
	void AddProjectile(vec2 position, vec2 direction, float angle);
	void Update(float deltaTime);
	void UploadRenderData();
	void RemoveExpired();
	void DisplayDebug();
}