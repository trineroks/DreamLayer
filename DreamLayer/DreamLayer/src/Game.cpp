#include "Game.h"

//REMEMBER THAT C++ STATIC MEMBERS MUST HAVE DEFINITIONS

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Game::Camera Game::camera;

Game::Game() {

}


Game::~Game() {
}

void Game::init(const char *title, int x, int y, int width, int height, bool fullscreen) {

	int flags = fullscreen ? (SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN) : SDL_WINDOW_SHOWN;
	
	camera.x = 0;
	camera.y = 0;
	
	if (!SDL_Init(SDL_INIT_EVERYTHING)) {
		printf("Subsystems initialized\n");

		window = SDL_CreateWindow(title, x, y, width, height, flags);
		if (window) {
			printf("Window created\n");
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			printf("Renderer created\n");
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

}

void Game::run() {
	SpriteBank::Instance().load();
	StateMachine::Instance().pushScreen(new MainMenu());
	while (!StateMachine::Instance().getExitState()) {
		delta = (SDL_GetTicks() - timeLastFrame) / 1000.0f;
		SDL_RenderClear(renderer);
		StateMachine::Instance().gameTick(delta);
		SDL_RenderPresent(renderer);
	}
	clear();
}

void Game::clear() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Window and renderer destroyed, subsystems closed\n");
}