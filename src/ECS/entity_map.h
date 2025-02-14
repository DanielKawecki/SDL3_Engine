
#include <array>
#include <map>

struct Entity {
	int id;
};

struct EntityMap {

	std::map<Entity, int> _idByEntity;
	std::array<Entity, 1024> _entityByID;

	Entity GetEntity(int id) { return _entityByID.at(id); }
	int GetID(Entity entity) { return _idByEntity.at(entity); }

	void Add(Entity entity, int id) {
		_idByEntity.insert({ entity, id });
		_entityByID.at(id) = entity;
	}

	void Update(Entity entity, int id) {
		_idByEntity.at(entity) = id;
		_entityByID.at(id) = entity;
	}

	void Remove(Entity entity) {
		_idByEntity.erase(entity);
	}
};