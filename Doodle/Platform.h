#pragma once

#include <vector>
#include "Framework.h"
#include "Vector2.h"

class Platform
{

public:
	Vector2 position{ -1, 0 };
	Sprite* platformSprite;

	Platform(Sprite* icon, float posY);
	void TickPlatform();
	Vector2 GetPlatformPosition();
};

