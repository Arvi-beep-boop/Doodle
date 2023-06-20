#pragma once
#include "Framework.h"
#include "Vector2.h"
#include "Platform.h"
#include "Enemy.h"

class Player
{
	
public:
	const float gravity = 700;
	float immunityTime;

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	
	Sprite* playerSpriteLeft;
	Sprite* playerSpriteRight;
	Sprite* playerActiveSprite;

	bool rightKeyMove;
	bool leftKeyMove;
	bool canFallOut;
	bool isImmune;

	void Move(float dt);
	void Jump();
	void Tick();
	void SetActiveSprite(Sprite* sprite);

	bool CheckPlatform(Platform p);
	bool CheckEnemy(Enemy enemy);
	bool isEnemyStomped(Enemy enemy);
	bool isHit(PlayerProjectile);
	
	bool CheckGround();

	bool Init(Sprite* leftSprite, Sprite* rightSprite);
	
	void DrawPlayer();

	void onKeyPressed(FRKey k);

	void onKeyReleased(FRKey k);

};