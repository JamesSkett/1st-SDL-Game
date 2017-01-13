#pragma once
#include "SDL.h"
#include <iostream>

#include "LoadTexture.h"

using namespace std;

//Parent class
class Assets
{
	//protected so the child classes can ccess the variables
protected:
	SDL_Rect m_cropRect;
	SDL_Texture* m_texture = nullptr;
	float m_frameCounter;
	int m_frameWidth, m_frameHeight;
	int m_textureWidth;
	bool m_isActive;

	//used to load the image files
	LoadTexture* m_loadLevel = new LoadTexture;

public:
	Assets(SDL_Renderer* renderTarget, string filePath, int x, int y, int framesX, int framesY);
	~Assets();

	void Draw(SDL_Renderer* renderTarget, SDL_Rect cameraRect);

	SDL_Rect positionRect;
};

