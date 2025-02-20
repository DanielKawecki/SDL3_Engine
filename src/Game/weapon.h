#pragma once

#include <string>
class vec2;

//enum class WeaponType {
//	NONE,
//	PISTOL,
//	MACHINE_GUN,
//	SHOTGUN
//};

struct WeaponInfo {
	std::string		name;
	int				magCapacity;
	bool			automatic;
	float			reloadTime;
	float			fireRate;
	//WeaponType	type;
};

class Weapon {

protected:
	WeaponInfo _info;
	int		_magBullets;
	bool	_reloading;
	float	_accumulator;

public:
	Weapon();
	virtual ~Weapon();

	WeaponInfo* GetWeaponInfo();
	virtual void Update(float deltaTime) = 0;
	virtual void Shoot(vec2 location, vec2 direction, float angle) = 0;
	virtual void Reload();
	void ResetAccumulator();
};

class Pistol : public Weapon {

public:
	Pistol();
	~Pistol();

	void Update(float deltaTime) override;
	void Shoot(vec2 location, vec2 direction, float angle) override;
};

class MachineGun : public Weapon {

private:
	bool	_ready;
	float	_fireInterval;

public:
	MachineGun();
	~MachineGun();

	void Update(float deltaTime) override;
	void Shoot(vec2 location, vec2 direction, float angle) override;
};

class Shotgun : public Weapon {

private:
	bool	_ready;
	float	_fireInterval;

public:
	Shotgun();
	~Shotgun();

	void Update(float deltaTime) override;
	void Shoot(vec2 location, vec2 direction, float angle) override;
};
