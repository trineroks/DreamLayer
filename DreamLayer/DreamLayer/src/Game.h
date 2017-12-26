#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SpriteBank.h"

#include "stateMachine/StateMachine.h"

#include <stdio.h>

class Game {
public:
		struct Camera {
		int x;
		int y;
	};

	Game();
	~Game();

	void init(const char *title, int x, int y, int width, int height, bool fullscreen);

	void run();
	void clear();

	bool running() { return isRunning; };

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static Camera camera;

private:
	int counter = 0;
	bool isRunning;
	SDL_Window *window;
};
