#pragma once

#include <vector>
#include "Framework.h"
#include "Vector2.h"
#include "Player.h"


class FakePlatform
{
public: 
	Sprite* sprite;
	Vector2 position{ -1, 0 };

	FakePlatform(Sprite* icon, float posY);
	void TickFakePlatform();
	bool HasPlayerTouched(Player player, Sprite* newIcon);

};

