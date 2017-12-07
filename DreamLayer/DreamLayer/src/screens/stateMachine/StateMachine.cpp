#include "StateMachine.h"

StateMachine::StateMachine() {
	exit = false;
}

StateMachine &StateMachine::getInstance() {
	static StateMachine instance;
	return instance;
}

void StateMachine::changeScreen(GameScreen* screen) {
	if (!screenStack.empty())
		popScreen();
	screenStack.push_back(screen);
}

void StateMachine::popScreen() {
	GameScreen *screen;
	if (!screenStack.empty()) {
		screen = screenStack.back();
		screen->cleanUp();
		delete screen;
	}
	screenStack.pop_back();
}

void StateMachine::pushScreen(GameScreen* screen) {
	screenStack.push_back(screen);
}

void StateMachine::gameTick(float deltaTime) {
	if (!screenStack.empty()) {
		processInput();
		screenStack.back()->update(deltaTime);
	}
	else
		printf("The state machine is empty!\n");
}

void StateMachine::processInput() {
	GameScreen* screen = screenStack.back();
	SDL_Event &event = Game::event;
	while (SDL_PollEvent(&event)) {
		switch (Game::event.type) {
		case SDL_KEYDOWN:
			screen->keyDown(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			screen->keyUp(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				screen->touchDown(event.button.x, event.button.y);
				clicked = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				screen->touchUp(event.button.x, event.button.y);
				clicked = false;
			}
			break;
		case SDL_MOUSEMOTION:
			if (clicked)
				screen->touchDragged(event.motion.x, event.motion.y);
			else 
				screen->mouseMoved(event.motion.x, event.motion.y);
			break;
		case SDL_QUIT:
			exit = true;
		}
	}
}
