#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Level.h"
#include <vector>

struct SDL_Window;
struct SDL_Renderer;

class GameSystem
{
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderTarget;

	Level* m_level1;

	int levelNum;

public:
	GameSystem();
	~GameSystem();

	void playGame(void);




};

