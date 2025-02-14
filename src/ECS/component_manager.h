#pragma once

#include "entity.h"
#include "entity_map.h"

#include <map>
#include <array>
#include <functional>

template<typename ComponentType>
class ComponentManager {

private:
	int											_componentsSize = 1;
	const int									_maxComponents = 1024;
	EntityMap									_entityMap;
	std::array<ComponentType, _maxComponents>	_components;
	//std::map<Entity, int>						_entityMap;
	//std::array<Entity, _maxComponents>			_entityIDs;


public:
	int Add(Entity e, ComponentType& c);
	ComponentType* Lookup(Entity e);
	void Destroy(Entity e);
	void IterateAll(std::function<void(ComponentType component)> lambda);

};
