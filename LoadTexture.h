#pragma once
#include <iostream>

#include "SDL.h"

using namespace std;

class LoadTexture
{
private:

public:
	LoadTexture();
	~LoadTexture();

	SDL_Texture* LoadImage(string filePath, SDL_Renderer* renderTarget);
};

