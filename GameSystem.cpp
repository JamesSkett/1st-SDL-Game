#include "GameSystem.h"
#include <stdio.h>
#include "time.h"

using namespace std;

//initialises the gamesystem properties and objects
GameSystem::GameSystem()
{
	m_window = nullptr;
	m_renderTarget = nullptr;
	levelNum = 1;


	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	//creates the game window
	m_window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	//error checking
	if (!m_window)
	{
		printf("Window Initialisation failed: %s\n", SDL_GetError);
		printf("Press any key to continue\n");
		getchar();
		return;
	}

	//creates the renderer for the game
	m_renderTarget = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//error checking
	if (!m_renderTarget)
	{
		printf("Renderer initialisation failed: %s\n", SDL_GetError);
		printf("Press any key to continue\n");
		getchar();
		return;
	}



}

//clean up
GameSystem::~GameSystem()
{
	if (m_renderTarget)
	{
		SDL_DestroyRenderer(m_renderTarget);
		m_renderTarget = nullptr;
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}

	if (m_level1)
	{
		delete m_level1;
		m_level1 = nullptr;
	}

}

//holds the main game loop and draws the art on the screen
void GameSystem::playGame()
{
	bool isDone = false;
	while (!isDone)
	{
		m_level1 = new Level(m_renderTarget, levelNum);

		m_level1->playGame(m_renderTarget);

 		if (m_level1->getLevelEnd() == true)
		{
			levelNum++;
		}
		else
			isDone = true;

		if (levelNum == 3)
			isDone = true;

		delete m_level1;
		m_level1 = nullptr;
	}
	
}

