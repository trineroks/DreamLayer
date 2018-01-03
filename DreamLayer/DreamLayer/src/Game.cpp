#include "Game.h"

//REMEMBER THAT C++ STATIC MEMBERS MUST HAVE DEFINITIONS

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Game::Camera Game::camera;
int Game::wscreen;
int Game::hscreen;

Game::Game() {

}


Game::~Game() {
}

void Game::init(const char *title, int x, int y, int width, int height, bool fullscreen) {

	int flags = fullscreen ? (SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN) : SDL_WINDOW_SHOWN;
	
	camera.x = 0;
	camera.y = 0;
	
	wscreen = width;
	hscreen = height;

	if (!SDL_Init(SDL_INIT_EVERYTHING)) {
		printf("Subsystems initialized\n");

		window = SDL_CreateWindow(title, x, y, wscreen, hscreen, flags);
		if (window) {
			printf("Window created\n");
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
	float time_seconds = SDL_GetTicks();
	while (!StateMachine::Instance().getExitState()) {
		float new_time = SDL_GetTicks();
		float delta = new_time - time_seconds;
		time_seconds = new_time;
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