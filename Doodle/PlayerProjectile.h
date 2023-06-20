#pragma once

#include "Framework.h"
#include "Vector2.h"

class PlayerProjectile
{
public:
	float speed = 500;

	Sprite* projectileSprite;

	Vector2 position;
	Vector2 direction;
	Vector2 velocity;

	PlayerProjectile(Vector2 startPosition, Sprite* icon);
	void SetDirection(Vector2 StartPosition, Vector2 Destination);
	void pProjectileTick();

};

