#pragma once

class vec2;

class Weapon {

public:
	virtual ~Weapon();

	virtual bool IsAutomatic() const = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Shoot(vec2 location, vec2 direction, float angle) = 0;
	virtual void Reload() = 0;
	virtual void ResetAccumulator() = 0;
};

class Pistol : public Weapon {

private:
	int		_magCapacity;
	int		_magBullets;
	bool	_automatic;
	
	bool	_reloading;
	float	_accumulator;
	float	_reloadTime;

public:
	Pistol();
	~Pistol();

	bool IsAutomatic() const override;
	void Update(float deltaTime) override;
	void Shoot(vec2 location, vec2 direction, float angle) override;
	void Reload() override;
	void ResetAccumulator() override;
};

class MachineGun : public Weapon {

private:
	int		_magCapacity;
	int		_magBullets;
	bool	_automatic;
	bool	_ready;
	float	_fireRate;
	float	_fireInterval;

	bool	_reloading;
	float	_accumulator;
	float	_reloadTime;

public:
	MachineGun();
	~MachineGun();

	bool IsAutomatic() const override;
	void Update(float deltaTime) override;
	void Shoot(vec2 location, vec2 direction, float angle) override;
	void Reload() override;
	void ResetAccumulator() override;
};
