#pragma once

#include "Vector2.h"
#include "Framework.h"
#include "DeltaTime.h"
#include "PlayerProjectile.h"
class Turret
{
public:
	Vector2 position;
	Sprite* sprite;
	

	float shootCooldown;
	float timer;

	void Init(Vector2 startPosition, Sprite* icon);
	void Tick();
	bool CanShoot();
	void ResetCooldown();
};

