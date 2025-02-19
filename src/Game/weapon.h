#pragma once

class vec2;

enum class WeaponType {
	NONE,
	PISTOL,
	MACHINE_GUN,
	SHOTGUN
};

class Weapon {

protected:
	WeaponType _type;

	int		_magCapacity;
	int		_magBullets;
	bool	_automatic;

	bool	_reloading;
	float	_accumulator;
	float	_reloadTime;

public:
	Weapon();
	virtual ~Weapon();

	bool IsAutomatic() const;
	virtual void Update(float deltaTime) = 0;
	virtual void Shoot(vec2 location, vec2 direction, float angle) = 0;
	virtual void Reload();
	void ResetAccumulator();
	WeaponType GetType() const;
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
	float	_fireRate;
	float	_fireInterval;

public:
	MachineGun();
	~MachineGun();

	void Update(float deltaTime) override;
	void Shoot(vec2 location, vec2 direction, float angle) override;
};
