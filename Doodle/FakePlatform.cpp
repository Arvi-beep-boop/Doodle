#include "FakePlatform.h"



FakePlatform::FakePlatform(Sprite* icon, float posY)
{
	int width, height;
	getScreenSize(width, height);
	position.y = posY;
	while (position.x < 0)
	{
		position.x = std::rand() % width - 100 + 1;
	}
	sprite = icon;

	drawSprite(sprite, position.x, position.y);
}

void FakePlatform::TickFakePlatform()
{
	drawSprite(sprite, position.x, position.y);
}
bool FakePlatform::HasPlayerTouched(Player player, Sprite* newIcon)
{
	Vector2 l1 = { position.x, position.y };
	Vector2 r1 = { position.x + 100, position.y + 30 };

	Vector2 l2 = { player.position.x, player.position.y };
	Vector2 r2 = { player.position.x + 64, player.position.y + 64 };

	if (l1.x == r1.x || l1.y == r1.y || r2.x == l2.x || l2.y == r2.y)
		return false;

	// If one rectangle is on left side of other
	if (l1.x > r2.x || l2.x > r1.x)
		return false;

	// If one rectangle is above other
	if (r1.y < l2.y || r2.y < l1.y)
		return false;

	sprite = newIcon;
	return true;
}

