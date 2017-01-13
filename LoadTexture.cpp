#include "LoadTexture.h"
#include "SDL_image.h"

LoadTexture::LoadTexture()
{

}


LoadTexture::~LoadTexture()
{
	
}

//optimising the texture
SDL_Texture* LoadTexture::LoadImage(string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
	//load the image file
	SDL_Surface* surface = IMG_Load(filePath.c_str());

	//error check
	if (surface == NULL)
		printf("Error: %s\n", IMG_GetError());
	else
	{
		//create the texture
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	}

	SDL_FreeSurface(surface);

	return texture;
}
