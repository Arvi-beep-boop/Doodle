#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cmath>

#include "Framework.h"
#include "Player.h"
#include "DeltaTime.h"
#include "Platform.h"
#include "FakePlatform.h"
#include "PlayerProjectile.h"
#include "Enemy.h"
#include "Turret.h"

/*
================ STEERING ==============

@ press UP Arrow key to enable immunity ability. 
@ immunity ability lasts 20 seconds and has cooldown before each use
@ in the start of the game you will be able to use immunity AFTER 30 seconds
@ left and right arrow key to move
@ player jumps if detects platform/ground beneath 

============ RESTARTING GAME ============

 to restart game press DOWN arrow key after dying.

============ SCORE ==========
 
 Score is shown both in upper left and right corner.
 Left upper corner shows platforms passed
 Right upper corner shows distance passed

*/

int gameWidth = 0;
int gameHeight = 0;

class MyFramework : public Framework {
public:
	int platformsPassed = 0;
	float score = 0;
	bool gameOver = false;
	float scrollWorld = 0;
	float immunityDuration = 20.0f;
	float immunityCooldownDuration = 10.0f;
	float immunityCooldown = immunityDuration + immunityCooldownDuration; //immunity duration + cooldown before next immunity use

	Vector2 cursorPosition;
	Player player;
	Turret turret;
	
	Sprite* background; 
	Sprite* playerProjectileIcon;
	Sprite* platformSprite;
	Sprite* fakePlatformSprite;
	Sprite* fakePlatformSpriteBroken;
	Sprite* enemySprite;
	Sprite* deadEnemy;
	Sprite* gameOverSprite;
	Sprite* PlayerLeft;
	Sprite* PlayerRight;
	Sprite* turretSprite;
	Sprite* turretProjectileSprite;
	Sprite* Immunity;
	Sprite* numericSprites[10];

	std::vector<Platform> platforms;
	std::vector<FakePlatform> fakePlatforms;
	std::vector<PlayerProjectile> playerProjectiles;
	std::vector<Enemy> enemies;
	std::vector<PlayerProjectile> turretProjectiles;
		
	float timer = std::rand() % 5 + 1;

	void PreInit(int& width, int& height, bool& fullscreen) override
	{
		width = gameWidth;
		height = gameHeight;
		fullscreen = false;
	}

	bool Init() override 
	{
		DeltaTime::Init(getTickCount());

//========== CREATE SPRITES =========

		background = /*std::unique_ptr<Sprite>*/(createSprite("..\\data\\jungle-bck@2x.png"));
		playerProjectileIcon = createSprite("..\\data\\bubble@2x.png");
		platformSprite = createSprite("..\\data\\green_platform.png");
		fakePlatformSprite = createSprite("..\\data\\fake_platform.png");
		fakePlatformSpriteBroken = createSprite("..\\data\\fake_platform_1.png");
		enemySprite = createSprite("..\\data\\ice-puca@2x.png");
		gameOverSprite = createSprite("..\\data\\race-over.png");
		deadEnemy = createSprite("..\\data\\ghost-puca@2x.png");
		PlayerLeft = createSprite("..\\data\\jungle-left.png");
		PlayerRight = createSprite("..\\data\\jungle-right.png");
		turretSprite = createSprite("..\\data\\bluesquare-64.png");
		turretProjectileSprite = createSprite("..\\data\\square-64.png");
		Immunity = createSprite("..\\data\\Immunity.png");

		//===== NUMERIC SPRITES =====
		
		numericSprites[0] = createSprite("..\\data\\n0.png");
		numericSprites[1] = createSprite("..\\data\\n1.png");
		numericSprites[2] = createSprite("..\\data\\n2.png");
		numericSprites[3] = createSprite("..\\data\\n3.png");
		numericSprites[4] = createSprite("..\\data\\n4.png");
		numericSprites[5] = createSprite("..\\data\\n5.png");
		numericSprites[6] = createSprite("..\\data\\n6.png");
		numericSprites[7] = createSprite("..\\data\\n7.png");
		numericSprites[8] = createSprite("..\\data\\n8.png");
		numericSprites[9] = createSprite("..\\data\\n9.png");

		for (Sprite* s : numericSprites)
		{
			setSpriteSize(s, 32, 32);
		}
		
		setSpriteSize(background, gameWidth, gameHeight);
		setSpriteSize(platformSprite, 100, 30);
		setSpriteSize(fakePlatformSprite, 100, 30);
		setSpriteSize(fakePlatformSpriteBroken, 100, 30);
		setSpriteSize(enemySprite, 64, 64);
		setSpriteSize(deadEnemy, 64, 64);
		setSpriteSize(gameOverSprite, 312, 80);
		setSpriteSize(PlayerLeft, 64, 64);
		setSpriteSize(PlayerRight, 64, 64);
		setSpriteSize(turretProjectileSprite, 16, 16);
		setSpriteSize(Immunity, 64, 64);

		//====INITIALIZE OBJECTS====

		InitializePlatforms();
		player.Init(PlayerLeft, PlayerRight);
		turret.Init({ (float)gameWidth / 2, 0 }, turretSprite);

		return true;
	}

	void Close() override
	{

	}

	bool Tick() override
	{

		DeltaTime::Update(getTickCount());
		drawSprite(background, 0, 0);

		timer -= DeltaTime::Get();
		immunityCooldown -= DeltaTime::Get();

		if (!gameOver)
		{
			if (score == 0)
				drawSprite(numericSprites[0], gameWidth - 64, 0);
			if (platformsPassed == 0)
				drawSprite(numericSprites[0], 96, 0);

			CalculateScore(score, { (float)gameWidth - 64, 0 });
			CalculateScore(platformsPassed, { 96, 0 });

			if (turret.CanShoot())
			{
				PlayerProjectile turretProjectile(turret.position, turretProjectileSprite);
				turretProjectile.SetDirection(turret.position, player.position);
				turretProjectiles.push_back(turretProjectile);
				turret.ResetCooldown();
			}

			if (player.position.y < gameHeight / 3)
			{
				float difference = (gameHeight / 3) - player.position.y;
				MoveWorld(difference);
			}

//========== TICK GAME OBJECTS ==========

			turret.Tick();
			player.Tick();
			if (player.isImmune)
			{
				drawSprite(Immunity, player.position.x, player.position.y);
			}

			for (PlayerProjectile& turretPrjct : turretProjectiles)
			{
				turretPrjct.pProjectileTick();
				if (player.isHit(turretPrjct) && !player.isImmune)
					gameOver = true;
			}

			for (Platform& p : platforms)
			{
				p.TickPlatform();
				if (player.CheckPlatform(p))
				{

					if (player.velocity.y > 0)
						player.Jump();

					break;
				}
			}
			for (FakePlatform& f : fakePlatforms)
			{
				f.TickFakePlatform();
				if (player.velocity.y > 0);
					f.HasPlayerTouched(player, fakePlatformSpriteBroken);
			}

			for (PlayerProjectile& prjct : playerProjectiles)
			{
				prjct.pProjectileTick();
				for (Enemy& e : enemies)
				{
					e.isHit(prjct, deadEnemy);
				}
			}

			for (Enemy& e : enemies)
			{
				e.Tick();
				if (player.CheckEnemy(e) && !e.isDead)
				{
					gameOver = true;
				}
				if (player.isEnemyStomped(e) && player.velocity.y > 0)
				{
					e.Kill(deadEnemy);
				}
			}
//========== REMOVE OBJECTS IF OFF SCREEN ==========
			if (enemies.size() > 0)
			{
				if (enemies[0].position.y > gameHeight)
				{
					enemies.erase(enemies.begin());
				}
			}

			if (platforms.size() > 0)
			{
				if (platforms[0].GetPlatformPosition().y > gameHeight)
				{
					platformsPassed++;
					platforms.erase(platforms.begin());
				}
			}

			if (fakePlatforms.size() > 0)
			{
				if (fakePlatforms[0].position.y > gameHeight)
				{
					fakePlatforms.erase(fakePlatforms.begin());
				}
			}

			if (playerProjectiles.size() > 0)
			{
				if (playerProjectiles[0].position.y > gameHeight || playerProjectiles[0].position.y < 0)
				{
					playerProjectiles.erase(playerProjectiles.begin());
				}
			}

			if (turretProjectiles.size() > 0)
			{
				if (turretProjectiles[0].position.y > gameHeight || turretProjectiles[0].position.y < 0)
				{
					turretProjectiles.erase(turretProjectiles.begin());
				}
			}

//========== ENABLE DEATH BY FALL ==========
			if (platformsPassed > 0)
			{
				
				if (player.CheckGround())
				{
					gameOver = true;
				}
			}
		}

		if (gameOver)
		{
			drawSprite(gameOverSprite, gameWidth / 3, gameHeight / 3);
		}
		return false;
	}

	void onMouseMove(int x, int y, int xrelative, int yrelative) override
	{
		cursorPosition.x = x;
		cursorPosition.y = y;
	}

	void onMouseButtonClick(FRMouseButton button, bool isReleased) override
	{

		if (button == FRMouseButton::LEFT && isReleased == false)
		{
			PlayerProjectile prjct(player.position, playerProjectileIcon);
			prjct.SetDirection(player.position, cursorPosition);
			playerProjectiles.push_back(prjct);
		}
	}

	void onKeyPressed(FRKey k) override
	{
		player.onKeyPressed(k);
		if (k == FRKey::UP)
		{
			if (!player.isImmune && immunityCooldown <= 0)
			{
				player.immunityTime = immunityDuration;
				immunityCooldown = immunityDuration + immunityCooldownDuration;
				player.isImmune = true;
			}
		}
		if (k == FRKey::DOWN && gameOver == true)
		{
			RestartGame();
		}
	}

	void onKeyReleased(FRKey k) override {
		player.onKeyReleased(k);
	}

	const char* GetTitle() override
	{
		return "Doodle";
	}

	void MoveWorld(float difference)
	{
// ========== MOVE DOWN ==========
		for (Enemy& e : enemies)
		{
			e.position.y += difference;
		}

		for (Platform& r : platforms)
		{
			r.position.y += difference ; 
		}

		for (FakePlatform& f : fakePlatforms)
		{
			f.position.y += difference;
		}
		for (PlayerProjectile& p : playerProjectiles)
		{
			p.position.y += difference;
		}
		for (PlayerProjectile& t : turretProjectiles)
		{
			t.position.y += difference;
		}

		scrollWorld += difference;

// ========== NEW PLATFORM ==========
		if (scrollWorld >= 100)
		{
			Platform newPlatform(platformSprite, 0);
			platforms.push_back(newPlatform);


			// ===== ENEMY? =====
			int spawn = std::rand() % 5 + 1;
			if (spawn % 2 == 0)
			{
				Vector2 enemySpawn = { newPlatform.GetPlatformPosition().x + 20, newPlatform.GetPlatformPosition().y - 50 };
				Enemy e(enemySpawn, enemySprite);
				enemies.push_back(e);
			}
			// ===== FAKE PLATFORM? =====
			if (spawn % 3 == 0)
			{
				FakePlatform newFake(fakePlatformSprite, 50);
				fakePlatforms.push_back(newFake);
			}
			scrollWorld = 0;
		}
		
		player.position.y += difference;
		score += difference;
	}

	void RestartGame()
	{
// ========== CLEAR ALL ARRAYS ==========
		if (platforms.size() > 0)
		{
			platforms.clear();
		}
		if (enemies.size() > 0)
		{
			enemies.clear();
		}
		if (playerProjectiles.size() > 0)
		{
			playerProjectiles.clear();
		}
		if (turretProjectiles.size() > 0)
		{
			turretProjectiles.clear();
		}
		if (fakePlatforms.size() > 0)
		{
			fakePlatforms.clear();
		}

// ========== INITIALIZE ==========
		player.Init(PlayerLeft, PlayerRight);
		score = 0;
		platformsPassed = 0;
		immunityCooldown = immunityDuration + 10.0f;
		InitializePlatforms();
		gameOver = false;
	}

	void InitializePlatforms()
	{
		for (int i =9; i > 0; i--)
		{
			float posY = i * 100;
			Platform p(platformSprite, posY);
			platforms.push_back(p);
		}
	}

	void CalculateScore(float score, Vector2 startPositionForText)
	{
		int s = int(score);
		Vector2 drawingPosition = startPositionForText;
		int n;
		while (s != 0)
		{
			n = s % 10;
			drawSprite(numericSprites[n], drawingPosition.x, drawingPosition.y);
			s /= 10;
			drawingPosition.x -= 32;
		}
	}
};

int main(int argc, char* argv[])
{
	//game -window 800x600
	bool fullscreen = false;

	if (argc == 3 && std::string(argv[1]) == "-window") 
	{
		std::string arg = argv[2];
		std::stringstream ss(arg);

		if (ss >> gameWidth && ss.peek() == 'x' && ss.ignore() && ss >> gameHeight) {
			std::cout << "Width: " << gameWidth << std::endl;
			std::cout << "Height: " << gameHeight << std::endl;
		}
		else 
		{
			std::cerr << "Invalid argument: " << arg << std::endl;
			return 1;
		}
	}
	else 
	{
		std::cerr << "Usage: " << argv[0] << " -window WIDTHxHEIGHT" << std::endl;
		std::cerr << "Default values 640x900 has been loaded" << std::endl;
		
		gameWidth = 640; //640
		gameHeight = 900;
	}


	MyFramework application;
	if (gameWidth > 0 && gameHeight > 0)
	{
		application.PreInit(gameWidth, gameHeight, fullscreen);
	}
	return run(&application);
	
}