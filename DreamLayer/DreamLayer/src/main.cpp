#include <stdio.h>
#include "Game.h"

int main(int argc, char*args[]) {
	Game* game = new Game();
	//game->init("Tragedy Strikes Again!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
	game->init("Tragedy Strikes Again!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, false);
	game->run();
	return 0;
}