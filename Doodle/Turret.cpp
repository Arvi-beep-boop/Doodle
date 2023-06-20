#include "Turret.h"

void Turret::Init(Vector2 startPosition, Sprite* icon)
{
	shootCooldown = 5.0f;
	timer = shootCooldown;
	sprite = icon;
	position = startPosition;
}
void Turret::Tick()
{
	timer -= DeltaTime::Get();
	drawSprite(sprite, position.x, position.y);
}
bool Turret::CanShoot()
{
	if (timer <= 0)
	{
		return true;
	}
	return false;
}
void Turret::ResetCooldown()
{
	timer = shootCooldown;
}