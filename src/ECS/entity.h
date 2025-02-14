#pragma once

#include "world.h"

struct Entity {
	int id = 0;
};

struct EntityHandle {
	Entity entity;
	World* world;

	void Destroy() {
		world->Remove(entity);
	}
};