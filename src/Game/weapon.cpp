#include "weapon.h"
#include "scene.h"

#include <iostream>

// ------------------ Weapon ------------------

Weapon::Weapon() {

	_info.name = "";
	_info.magCapacity = 0;
	_info.reloadTime = 0.f;
	_info.automatic = false;

	_magBullets = 0;
	_reloading = false;
	_accumulator = 0.f;
}

Weapon::~Weapon() {}

WeaponInfo* Weapon::GetWeaponInfo() {
	return &_info;
}

void Weapon::Reload() {

	_accumulator = 0.f;
	_reloading = true;
}

void Weapon::ResetAccumulator() {
	
	_accumulator = 0.f;
	_reloading = false;
}

// ------------------ Pistol ------------------


Pistol::Pistol() {

	_info.name = "1911";
	_info.magCapacity = 7;
	_info.reloadTime = 2.f;
	_info.automatic = false;

	_magBullets = _info.magCapacity;
	_reloading = false;
	_accumulator = 0.f;
}

Pistol::~Pistol() {

}

void Pistol::Update(float deltaTime) {

	if (_reloading) {

		_accumulator += deltaTime;
		if (_accumulator >= _info.reloadTime) {

			_reloading = false;
			_magBullets = _info.magCapacity;
		}
	}
}

void Pistol::Shoot(vec2 location, vec2 direction, float angle) {

	if (_magBullets > 0 && !_reloading) {

		_magBullets -= 1;
		Scene::AddProjectile(location, direction, angle);
	}
}

// ------------------ Machine Gun ------------------

MachineGun::MachineGun() {

	_info.name = "AK47";
	_info.magCapacity = 24;
	_info.reloadTime = 2.4f;
	_info.fireRate = 7.f; // Shots per second
	_info.automatic = true;

	_magBullets = _info.magCapacity;
	_ready = false;
	_fireInterval = 1.f / _info.fireRate;
	_reloading = false;
	_accumulator = 0.f;
}

MachineGun::~MachineGun() {}

void MachineGun::Update(float deltaTime) {

	if (!_reloading) {

		_accumulator += deltaTime;
		if (_accumulator >= _fireInterval) {

			_ready = true;
		}
	}

	else if (_reloading) {

		_accumulator += deltaTime;
		if (_accumulator >= _info.reloadTime) {

			_reloading = false;
			_magBullets = _info.magCapacity;
			_accumulator = 0.f;
		}
	}
}

void MachineGun::Shoot(vec2 location, vec2 direction, float angle) {

	if (_ready && _magBullets > 0 && !_reloading) {

		_magBullets -= 1;
		_accumulator = 0.f;
		_ready = false;

		Scene::AddProjectile(location, direction, angle);
	}
}

Shotgun::Shotgun() {

	_info.name = "SPAS";
	_info.automatic = false;
	_info.magCapacity = 6;
	_info.fireRate = 0.75f;

	_magBullets = _info.magCapacity;
	_ready = false;
	_fireInterval = 1.f / _info.fireRate;
}

Shotgun::~Shotgun() {}

void Shotgun::Update(float deltaTime) {

	if (!_reloading) {

		_accumulator += deltaTime;
		if (_accumulator >= _fireInterval) {

			_ready = true;
		}
	}

	else if (_reloading) {

		_accumulator += deltaTime;
		if (_accumulator >= _info.reloadTime) {

			_reloading = false;
			_magBullets = _info.magCapacity;
			_accumulator = 0.f;
		}
	}
}

void Shotgun::Shoot(vec2 location, vec2 direction, float angle) {

	if (_ready && _magBullets > 0 && !_reloading) {

		_magBullets -= 1;
		_accumulator = 0.f;
		_ready = false;

		float angleDiff = 0.0698131701f;

		vec2 dir;
		dir.x = direction.x * cosf(angleDiff) - direction.y * sinf(angleDiff);
		dir.y = direction.x * sinf(angleDiff) + direction.y * cosf(angleDiff);

		Scene::AddProjectile(location, dir, angle);
		Scene::AddProjectile(location, direction, angle);

		dir.x = direction.x * cosf(-angleDiff) - direction.y * sinf(-angleDiff);
		dir.y = direction.x * sinf(-angleDiff) + direction.y * cosf(-angleDiff);

		Scene::AddProjectile(location, dir, angle);
		//Scene::AddProjectile(location, direction, angle);
	}
}
