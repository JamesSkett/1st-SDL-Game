#pragma once
#include "SDL.h"
#include "Assets.h"
#include "Platform.h"
#include "Enemy.h"
#include "HUD.h"
#include "Pickups.h"
#include <iostream>
#include <vector>

using namespace std;

//child class of Assets
class Player : public Assets
{
private:
	bool m_canJump;
	bool isJumping;
	bool m_isCollidingPlatform;
	int m_originX, m_originY;
	float m_jumpVelovity = 2;

	float m_jumpSpeed = 1000;
	float m_timer = 0.0f;
	bool m_useGravity;
	const float m_gravity = 6.0f;

	float moveSpeed;

	SDL_Scancode keys[3];

	


public:
	Player(SDL_Renderer* renderTarget, string filePath, int x, int y, int framesX, int framesY);
	~Player();

	void update(float delta, const Uint8* keyState);
	bool platformCollisionCheck(Platform &platform);
	bool enemyCollisionCheck(Enemy &enemy);
	bool coinCollision(Pickups &coin, HUD &hud);
	void jump(float deltaTime);

	int GetOriginX();
	int GetOriginY();
};

