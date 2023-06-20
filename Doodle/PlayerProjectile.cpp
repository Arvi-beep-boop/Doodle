#include <cmath>
#include "PlayerProjectile.h"
#include "DeltaTime.h"


void PlayerProjectile::pProjectileTick()
{
	int width, height;
	getScreenSize(width, height);

	position.x += velocity.x * DeltaTime::Get();
	position.y += velocity.y * DeltaTime::Get();
	drawSprite(projectileSprite, position.x, position.y);
	if (position.x > width)
	{
		position.x = 0;
	}
	if (position.x < 0)
	{
		position.x = width;
	}
}
void PlayerProjectile::SetDirection(Vector2 StartPosition, Vector2 Destination)
{
	int x = Destination.x - StartPosition.x;
	int y = Destination.y - StartPosition.y ;
	float magnitude = std::sqrt((x * x) + (y * y));
	if (magnitude == 0.0) // just to be fully safe
	{
		direction = {0, -1};
	}
	else 
	{
		direction = { x / magnitude, y / magnitude };
	}
	velocity.x = direction.x * speed;
	velocity.y = direction.y * speed;
}

PlayerProjectile::PlayerProjectile(Vector2 startPosition, Sprite* icon)
{
	projectileSprite = icon; 
	
	position = startPosition;
}
