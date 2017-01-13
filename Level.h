#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Player.h"
#include "Platform.h"
#include "LoadTexture.h"
#include "Enemy.h"
#include "HUD.h"
#include "Pickups.h"
#include <vector>

class Level
{
private:
	SDL_Renderer* m_renderTarget;
	SDL_Texture* background;
	SDL_Event ev;

	Player* player1;
	int playerHealth;

	LoadTexture* m_loadlevel = new LoadTexture;
	//stores the information for the platforms
	vector <Platform*> m_platform;
	//stores the information for the enemys
	vector <Enemy*> m_enemy;
	//stores the information for the coin pickup
	vector <Pickups*> m_coin;
	HUD* hud;

	SDL_Rect cameraRect;
	int levelWidth, levelHeight;

	//for setting up framerate
	int currentTime = 0;
	int previousTime = 0;
	float delta = 0.0f;
	bool isRunning = true;
	bool levelEnd;


	const Uint8* keyState;

	void drawEnemies();
	void drawPlatforms();
	void checkCollisions();
	void drawCoins();
public:
	Level(SDL_Renderer* renderTarget, int levelNum);
	~Level();

	void playGame(SDL_Renderer* renderTarget);

	void Scrolling();
	int generateRandomY(int min, int max);

	bool getLevelEnd();
};

