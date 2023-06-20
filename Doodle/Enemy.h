#pragma once

#include "Framework.h"
#include "Vector2.h"
#include "PlayerProjectile.h"

class Enemy
{
public: 
	Vector2 position;
	Vector2 velocity;

	Sprite* enemySprite;

	bool isDead;

	Enemy(Vector2 startPosition, Sprite* icon);
	void Tick();
	bool isHit(PlayerProjectile projectile, Sprite* newIcon);
	void Kill(Sprite* newIcon);
};

