#pragma once


#include "Enemy.h"
#include "DeltaTime.h"



Enemy::Enemy(Vector2 startPosition, Sprite* icon)
{
	position = startPosition;
	enemySprite = icon;
	isDead = false;
}

void Enemy::Tick()
{
	//position.y += 0.2 * DeltaTime::Get();
	drawSprite(enemySprite, position.x, position.y);
}

bool Enemy::isHit(PlayerProjectile projectile, Sprite* newIcon)
{
	Vector2 l1 = { position.x, position.y };
	Vector2 r1 = { position.x + 64, position.y + 64 };

	Vector2 l2 = { projectile.position.x, projectile.position.y };
	Vector2 r2 = { projectile.position.x + 16, projectile.position.y + 16 };

	if (l1.x == r1.x || l1.y == r1.y || r2.x == l2.x || l2.y == r2.y)
		return false;

	// If one rectangle is on left side of other
	if (l1.x > r2.x || l2.x > r1.x)
		return false;

	// If one rectangle is above other
	if (r1.y < l2.y || r2.y < l1.y)
		return false;

	isDead = true;
	enemySprite = newIcon;
	return true;
}
void Enemy::Kill(Sprite* newIcon)
{
	isDead = true;
	enemySprite = newIcon;
}

