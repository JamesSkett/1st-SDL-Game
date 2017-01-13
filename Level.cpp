#include "Level.h"
#include <stdio.h>
#include "time.h"


Level::Level(SDL_Renderer* renderTarget, int levelNum)
{
	background = nullptr;
	m_loadlevel = nullptr;
	player1 = nullptr;

	m_renderTarget = renderTarget;

	//initialises the player
	player1 = new Player(m_renderTarget, "Assets/image.png", 20, 10, 3, 4);

	//sets up the camera rect to the size of the window
	cameraRect = { 0, 0, 640, 480 };
	//loads the background image
	if (levelNum == 2)
		background = m_loadlevel->LoadImage("Assets/lvl2Background.png", m_renderTarget);
	else
		background = m_loadlevel->LoadImage("Assets/background.png", m_renderTarget);

	//sets the x and y for the first platform
	int platformX = 10;
	int platformY = 240;

	//this is to get a completely random number every time the platforms are created
	srand(time(NULL));

	//creates 8 platforms at random heights in the game
	//and spawns them 250 pixels from the last one
	for (int i = 0; i <= 8; i++)
	{
		//push back the new platform object into the vector
		m_platform.push_back(new Platform(m_renderTarget, "Assets/Platform.png", platformX, platformY, 1, 1));
		m_coin.push_back(new Pickups(m_renderTarget, "Assets/coin.png", platformX + 50, platformY - 50, 1, 1));
		//the next platform will be 250 pixels from the last
		platformX += 250;
		printf("Y Pos: %d\n", platformY);

		//generates a random number between 100 and the previous y pos - 50
		platformY = generateRandomY(100, platformY + 50);
	}

	//sets up the coords for the position of the first enemy
	int enemyX = 190;
	int enemyY = 252;

	//creates 7 enemies at random heights in between the platforms
	for (int e = 0; e < 7; e++)
	{
		//push back the new enemy object into the vector
		m_enemy.push_back(new Enemy(m_renderTarget, "Assets/enemy.png", enemyX, enemyY, 1, 1));
		enemyX += 250;

		//generates a random number between 150 and the previous y pos - 50
		enemyY = generateRandomY(150, enemyY - 50);
	}


	hud = new HUD(m_renderTarget, 10, 10);
}


Level::~Level()
{
	if (background)
	{
		SDL_DestroyTexture(background);
		background = nullptr;
	}

	if (m_loadlevel)
	{
		delete m_loadlevel;
		m_loadlevel = nullptr;
	}

	if (player1)
	{
		delete player1;
		player1 = nullptr;
	}

	for (int i = 0; i < m_platform.size(); i++)
	{
		delete m_platform[i];
		m_platform[i] = nullptr;
	}
	m_platform.clear();

	for (int i = 0; i < m_enemy.size(); i++)
	{
		delete m_enemy[i];
		m_enemy[i] = nullptr;

	}
	m_enemy.clear();
}

//holds the main game loop and draws the art on the screen
void Level::playGame(SDL_Renderer* renderTarget)
{
	SDL_Event ev;


	//game loop
	while (isRunning)
	{
		//sets up the framerate to work the same on all devices
		previousTime = currentTime;
		currentTime = SDL_GetTicks();
		delta = (currentTime - previousTime) / 1000.0f;

		//event poll check to see if game is exited
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				isRunning = false;

		}

		keyState = SDL_GetKeyboardState(NULL);

		hud->Update(m_renderTarget);

		//updates the player
		player1->update(delta, keyState);
		hud->GetNumHealth(playerHealth);
		//updates the enemy
		for (int i = 0; i < m_enemy.size(); i++)
		{
			m_enemy[i]->update(delta);
		}

		for (int i = 0; i < m_platform.size(); i++)
		{
			m_platform[i]->Update(delta);
		}

		checkCollisions();


		//scrolls the camera with the player
		Scrolling();

		//clear the renderer
		SDL_RenderClear(m_renderTarget);


		//draw the background image
		SDL_RenderCopy(m_renderTarget, background, &cameraRect, NULL);

		hud->Draw(m_renderTarget);


		//draw the player
		player1->Draw(m_renderTarget, cameraRect);

		drawEnemies();

		drawPlatforms();

		drawCoins();

		// if the player has fallen out of the map game ends
		if (player1->positionRect.y > 640)
		{
			isRunning = false;
		}
		else if (player1->positionRect.x > 1900)
		{
			levelEnd = true;
			isRunning = false;
		}

		//updates the renderer to display on the screen
		SDL_RenderPresent(m_renderTarget);
	}
}

void Level::Scrolling()
{
	//get the propeties of the background image
	SDL_QueryTexture(background, NULL, NULL, &levelWidth, &levelHeight);

	//set the camera rect to the origin of the player - 320 and 240 (screen width / 2, screen height / 2)
	cameraRect.x = player1->GetOriginX() - 320;
	cameraRect.y = player1->GetOriginY() - 240;

	//if the x is less than 0 set camera rect x to 0;
	if (cameraRect.x < 0)
		cameraRect.x = 0;
	//if the y is less than 0 set camera rect y to 0;
	if (cameraRect.y < 0)
		cameraRect.y = 0;

	//if the player has reached the end of the level stop scrolling
	if (cameraRect.x + cameraRect.w >= levelWidth)
		cameraRect.x = levelWidth - 640;

	if (cameraRect.y + cameraRect.h >= levelHeight)
		cameraRect.y = levelHeight - 480;
}

void Level::drawEnemies()
{
	//draw the enemies
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->Draw(m_renderTarget, cameraRect);
	}
}

void Level::drawPlatforms()
{
	//draw the platforms
	for (int i = 0; i < m_platform.size(); i++)
	{
		m_platform[i]->Draw(m_renderTarget, cameraRect);
	}
}

void Level::drawCoins()
{
	for (int i = 0; i < m_coin.size(); i++)
	{
		m_coin[i]->Draw(m_renderTarget, cameraRect);
	}
}

void Level::checkCollisions()
{
	bool isCollidingWithPlatform = false;
	//checks if the player is colliding with any of the platforms
	for (int i = 0; i < m_platform.size(); i++)
	{
		//if the player is colliding dont check the collision of the other platforms
		//if the player is not colliding keep checking collision
		if (!isCollidingWithPlatform)
		{
			isCollidingWithPlatform = player1->platformCollisionCheck(*m_platform[i]);
		}
	}

	bool isCollidingWithEnemy = false;

	//checks if the player is colliding with any of the enemies
	for (int i = 0; i < m_enemy.size(); i++)
	{
		//if the player is colliding dont check the collision of the other enemies
		//if the player is not colliding keep checking collision
		if (!isCollidingWithEnemy)
		{
			isCollidingWithEnemy = player1->enemyCollisionCheck(*m_enemy[i]);
			if (isCollidingWithEnemy)
				isRunning = false;
		}
	}

	bool isCollidingWithCoin = false;
	for (int i = 0; i < m_coin.size(); i++)
	{
		//if the player is colliding dont check the collision of the other enemies
		//if the player is not colliding keep checking collision
		if (!isCollidingWithCoin)
		{
			isCollidingWithCoin = player1->coinCollision(*m_coin[i], *hud);
			if (isCollidingWithCoin)
			{
				m_coin[i] = m_coin.back();
				m_coin.pop_back();
				i--;
			}

		}
	}
}

int Level::generateRandomY(int min, int max)
{
	//generates a random number between the max and min
	int n = max - min + 1;
	int remainder = RAND_MAX % n;
	int x;
	do
	{
		x = rand();
	} while (x >= RAND_MAX - remainder);
	return min + x % n;
}

bool Level::getLevelEnd()
{
	return levelEnd;
}
