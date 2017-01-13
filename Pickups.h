#pragma once
#include "SDL.h"
#include "Assets.h"


class Pickups : public Assets
{
private:

public:
	Pickups(SDL_Renderer* renderTarget, string filePath, int x, int y, int framesX, int framesY);
	~Pickups();

};

