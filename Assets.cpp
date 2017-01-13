#include "Assets.h"


Assets::Assets(SDL_Renderer* renderTarget, string filePath, int x, int y, int framesX, int framesY)
{

	m_loadLevel = nullptr;
	//load the image
	m_texture = m_loadLevel->LoadImage(filePath, renderTarget);

	//get the properties of the texture
	SDL_QueryTexture(m_texture, NULL, NULL, &m_cropRect.w, &m_cropRect.h);

	//set the position of the image
	positionRect.x = x;
	positionRect.y = y;

	//set the texture width
	m_textureWidth = m_cropRect.w;

	//crop the image to the first frame if its a sprite sheet
	m_cropRect.w /= framesX;
	m_cropRect.h /= framesY;

	//set the frame width and height to the crprect width and height
	m_frameWidth = positionRect.w = m_cropRect.w;
	m_frameHeight = positionRect.h = m_cropRect.h;

	m_isActive = false;
}

//cleanup
Assets::~Assets()
{
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
	delete m_loadLevel;
	m_loadLevel = nullptr;
}

//draw the image
void Assets::Draw(SDL_Renderer* renderTarget, SDL_Rect cameraRect)
{
	SDL_Rect drawingRect = { positionRect.x - cameraRect.x, positionRect.y - cameraRect.y, positionRect.w, positionRect.h };
	SDL_RenderCopy(renderTarget, m_texture, &m_cropRect, &drawingRect);
}