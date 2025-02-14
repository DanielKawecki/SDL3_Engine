#pragma once

#include "../mth.h"

#include <iostream>
#include <vector>

struct Entity {
	unsigned int id = 0;
};

struct Transfrom {
	float x, y;
};

struct Motion {
	mth::vec2 velocity;
	mth::vec2 acceleration;
};

namespace World {

	std::vector<Entity> _entities;
	unsigned int _lastID = 0;

	Entity CreateEntity() {
		Entity entity;
		entity.id = _lastID++;
		return entity;
	}

	const std::vector<Entity>& GetEntities() {
		return _entities;
	}

}

namespace EntityManager {

}

namespace ComponentManager {

}

namespace TransformManager {

}

namespace MovementSystem {

	void Update(float deltaTime) {

		for (const Entity& entity : World::GetEntities()) {

			//Transfrom position = entity.GetTransform();
		}
	}

}
