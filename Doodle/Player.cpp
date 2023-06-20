#pragma once

#include <iostream>

#include "Player.h"
#include "DeltaTime.h"


bool Player::Init(Sprite* leftSprite, Sprite* rightSprite)
{
	int width, height;
	getScreenSize(width, height);

	//====VALUES====
	
	position.x = width / 2;
	position.y = height - (0.1 * height);

	velocity.x = 0;
	velocity.y = 0;

	acceleration.x = 90000;
	acceleration.y = 600;

	canFallOut = false;
	isImmune = false;

	playerSpriteLeft = leftSprite;
	playerSpriteRight = rightSprite;

	playerActiveSprite = playerSpriteLeft;

	return true;
}
	void Player::Move(float dt)
	{
		//====GRAVITY====

		velocity.y += gravity * dt;

		//====APPLY INPUT====

		if (rightKeyMove)
		{
			velocity.x += acceleration.x * dt;
		}
		if (leftKeyMove)
		{
			velocity.x -= acceleration.x * dt;
		}

		//====CHECK FOR GROUND====

		int width, height;
		getScreenSize(width, height);

		if (position.y >= height - (0.1 * height) && !canFallOut)
		{
			position.y = height - (0.1 * height);
			velocity.y = -acceleration.y;
		}

		//====APPLY MOVEMENT====

		position.x += velocity.x * dt;
		position.y += velocity.y * dt;

		//====OPPOSITE SIDE OF SCREEN====

		if (position.x > width)
		{
			position.x = 0;
		}
		if (position.x < 0)
		{
			position.x = width;
		}
		
		velocity.x = 0;
	}
	
	bool Player::CheckGround()
	{
		int width, height;
		getScreenSize(width, height);
		if (position.y >= height - (0.1 * height))
		{
			return true;
		}
		return false;
	}

	void Player::Jump()
	{
		velocity.y = -acceleration.y;
	}

	bool Player::CheckPlatform(Platform p)
	{
		Vector2 origin = p.GetPlatformPosition();
		float right = origin.x + 100; // + width of platform
		float bottom = origin.y + 10; // + smaller height of platform

		Vector2 pPos = position;
		float pRight = pPos.x + 64; // + player width
		float pBottom = pPos.y + 64; // + player height

		if ((position.y >= origin.y && position.y <= bottom) || (pBottom >= origin.y && pBottom <= bottom))
		{
			if ((position.x >= origin.x && position.x <= right) || (pRight >= origin.x && pRight <= right))
			{
				return true;
			}
			return false;
		}
		return false;
	}
	bool Player::CheckEnemy(Enemy enemy)
	{
		if (isImmune)
			return false;
		if (position.y >= (enemy.position.y + 32) && position.y <= (enemy.position.y + 64))
		{
				if ((position.x >= enemy.position.x && position.x <= enemy.position.x + 64) || (position.x + 64 >= enemy.position.x && position.x + 64 <= enemy.position.x + 64))
				{
					return true;
				}
		}
		return false;
	}

	bool Player::isEnemyStomped(Enemy enemy)
	{
		if (position.y + 32 < (enemy.position.y + 32) && position.y + 32 >= enemy.position.y)
		{
			if ((position.x >= enemy.position.x && position.x <= enemy.position.x + 64) || (position.x + 64 >= enemy.position.x && position.x + 64 <= enemy.position.x + 64))
			{
				return true;
			}
		}
		return false;
	}

	bool Player::isHit(PlayerProjectile projectile)
	{

		Vector2 l1 = { position.x, position.y };
		Vector2 r1 = { position.x + 64, position.y + 64 };

		Vector2 l2 = { projectile.position.x, projectile.position.y };
		Vector2 r2 = { projectile.position.x + 16, projectile.position.y + 16};

		if (l1.x == r1.x || l1.y == r1.y || r2.x == l2.x || l2.y == r2.y)
			return false;

		if (l1.x > r2.x || l2.x > r1.x)
			return false;

		if (r1.y < l2.y || r2.y < l1.y)
			return false;

		return true;
	}

	void Player::Tick()
	{
		Move(DeltaTime::Get());
		if (isImmune)
		{
			immunityTime -= DeltaTime::Get();
		}
		if (immunityTime <= 0)
		{
			immunityTime = 0;
			isImmune = false;
		}
		DrawPlayer();
	}
	
	void Player::DrawPlayer()
	{
		drawSprite(playerActiveSprite, static_cast<int>(position.x), static_cast<int>(position.y));
	}

	
	void Player::onKeyPressed(FRKey k)
	{
		if (k == FRKey::RIGHT)
		{
			rightKeyMove = true;
			Player::SetActiveSprite(playerSpriteRight);
		}
		if (k == FRKey::LEFT)
		{
			leftKeyMove = true;
			Player::SetActiveSprite(playerSpriteLeft);
		}
	}

	void Player::onKeyReleased(FRKey k)
	{
		if (k == FRKey::RIGHT)
		{
			rightKeyMove = false;
		}
		if (k == FRKey::LEFT)
		{
			leftKeyMove = false;
		}
	}

	void Player::SetActiveSprite(Sprite* sprite)
	{
		playerActiveSprite = sprite;
	}