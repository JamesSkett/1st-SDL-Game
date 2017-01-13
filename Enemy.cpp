#include "Enemy.h"

//initialise the enemy variables
Enemy::Enemy(SDL_Renderer* renderTarget, string filePath, int x, int y, int framesX, int framesY)
	: Assets(renderTarget, filePath, x, y, framesX, framesY)
{
	m_moveSpeed = 100;
	m_startPosY = positionRect.y;
	m_endPosY = positionRect.y - 100;
	m_isAtEndPos = false;
}


Enemy::~Enemy()
{
}

//this updates the enemy position depending on if it is a the start or end position
void Enemy::update(float delta)
{

	//if the enemy y pos is less than or equal to the endPosY set bool to true
	if (positionRect.y <= m_endPosY)
		m_isAtEndPos = true;
	//if the enemy y pos is greater than or equal to start pos y set bool to false
	else if (positionRect.y >= m_startPosY)
		m_isAtEndPos = false;

	//if the enemy is not at the end pos then move up
	if (!m_isAtEndPos)
	{
		positionRect.y -= m_moveSpeed * delta;
	}
	else //if the enemy is at the end pos then move down
	{
		positionRect.y += m_moveSpeed * delta;
	}
}

