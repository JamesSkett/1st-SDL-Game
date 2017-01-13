#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <sstream>

#include <string>

using namespace std;

class HUD
{
private:
	TTF_Font* font;
	SDL_Color colour;
	SDL_Surface* textSurface;
	SDL_Texture* text;
	SDL_Rect textRect;

	int m_startScore = 0;

	stringstream m_Score;

public:
	HUD(SDL_Renderer* renderTarget, int x, int y);
	~HUD();

	void loseHealth(int updateHealth);
	void Update(SDL_Renderer* renderTarget);
	void Draw(SDL_Renderer* renderTarget);
	void GetNumHealth(int &health);

};

