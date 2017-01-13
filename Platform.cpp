#include "Platform.h"


Platform::Platform(SDL_Renderer* renderTarget, string filePath, int x, int y, int framesX, int framesY)
	: Assets(renderTarget, filePath, x, y, framesX, framesY)
{
	m_fallSpeed = 250;
}


Platform::~Platform()
{
}

void Platform::Update(float deltaTime)
{
	if (isPlatformFalling)
	{
		SDL_SetTextureColorMod(m_texture, 0, 255, 0);
		if (m_timer <= 0)
		{
			positionRect.y += m_fallSpeed * deltaTime;
		}
		m_timer -= deltaTime;
	}

	
}


void Platform::setPlatformFalling() { isPlatformFalling = true; }
bool Platform::getPlatformFalling() { return isPlatformFalling; }
