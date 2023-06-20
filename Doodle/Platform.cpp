#include "Platform.h"
#include "DeltaTime.h"


	Platform::Platform(Sprite* icon, float posY)
	{
		int width, height;
		getScreenSize(width, height);
		position.y = posY;
		while (position.x < 0)
		{
			position.x = std::rand() % width - 100 + 1;
		}
		platformSprite = icon;
		
		drawSprite(platformSprite, position.x, position.y);

	}
	void Platform::TickPlatform()
	{
		drawSprite(platformSprite, position.x, position.y);
	}
	Vector2 Platform::GetPlatformPosition()
	{
		return position;
	}
	