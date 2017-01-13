#include "Pickups.h"


Pickups::Pickups(SDL_Renderer* renderTarget, string filePath, int x, int y, int framesX, int framesY)
	: Assets(renderTarget, filePath, x, y, framesX, framesY)
{

}


Pickups::~Pickups()
{
}
