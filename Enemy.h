#pragma once
#include "SDL.h"
#include "Assets.h"

//child class of Assets
class Enemy : public Assets
{
private:
	int m_moveSpeed;
	int m_startPosY;
	int m_endPosY;
	bool m_isAtEndPos;
	bool m_isActive;

public:
	Enemy(SDL_Renderer* renderTarget, string filePath, int x, int y, int framesX, int framesY);
	~Enemy();

	void update(float delta);
};

