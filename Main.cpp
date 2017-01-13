#include "SDL.h"
#include "SDL_image.h"

#include "GameSystem.h"

using namespace std;

int main(int argc, char* argv[])
{

	GameSystem* gameSystem = new GameSystem();

	//starts the main game loop
	gameSystem->playGame();


	//quit SDL before closing program
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}
