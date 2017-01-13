#pragma once
#include "SDL.h"

#include "Assets.h"

//child class of Assets
class Platform : public Assets
{
private:
	int m_fallSpeed;
	float m_timer = 1.5f;
	bool isPlatformFalling;

public:
	Platform(SDL_Renderer* renderTarget, string filePath, int x, int y, int framesX, int framesY);
	~Platform();

	void Update(float deltaTime);
	void setPlatformFalling();
	bool getPlatformFalling();
};

