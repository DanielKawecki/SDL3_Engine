#include "component_manager.h"

template<typename ComponentType>
int ComponentManager<ComponentType>::Add(Entity e, ComponentType& c) {
	
	_components[_componentsSize] = c;
	return _componentsSize++;
}

template<typename ComponentType>
ComponentType* ComponentManager<ComponentType>::Lookup(Entity e) {

	//unsigned int index = _entityMap[e];
	return &_components[_entityMap.GetID(e)];
}

template<typename ComponentType>
void ComponentManager<ComponentType>::Destroy(Entity e) {

	int id = _entityMap.GetID(e);// [e] ;
	int lastID = --_componentsSize;
	_components[id] = _components[lastID];
	_entityMap.Remove(e);
	//_entityMap.erase(e);

	Entity movedEntity = _entityMap.GetEntity(lastID); //_entityIDs[lastID];
	_entityMap.Update(movedEntity, id);// [movedEntity] = id;
}

template<typename ComponentType>
void ComponentManager<ComponentType>::IterateAll(std::function<void(ComponentType component)> lambda) {

	for (int i = 1; i < _componentsSize; ++i) {
		lambda(_components[i]);
	}
}
