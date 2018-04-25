#include "StateMachine.h"
#include "../Game.h"

StateMachine::StateMachine() {
	exit = false;
}

StateMachine &StateMachine::Instance() {
	static StateMachine instance;
	return instance;
}

void StateMachine::changeScreen(GameScreen* screen) {
	if (!screenStack.empty())
		popScreen();
	pushScreen(screen);
}

void StateMachine::popScreen() {
	GameScreen* screen;
	if (!screenStack.empty()) {
		screen = screenStack.back();
		screen->cleanUp();
		delete screen;
	}
	screenStack.pop_back();
}

void StateMachine::pushScreen(GameScreen* screen) {
	screen->init();
	screenStack.push_back(screen);
}

void StateMachine::gameTick(float deltaTime) {
	if (!screenStack.empty()) {
		processTick(deltaTime);
		//screenStack.back()->update(deltaTime);
	}
	else
		printf("The state machine is empty!\n");
}

void StateMachine::processTick(float delta) {
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
				screen->touchDown(event.button.x + Game::camera.pos.x, event.button.y + Game::camera.pos.y);
				clicked = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				screen->touchUp(event.button.x + Game::camera.pos.x, event.button.y + Game::camera.pos.y);
				clicked = false;
			}
			break;
		case SDL_MOUSEMOTION:
			if (clicked)
				screen->touchDragged(event.button.x + Game::camera.pos.x, event.button.y + Game::camera.pos.y);
			else 
				screen->mouseMoved(event.button.x + Game::camera.pos.x, event.button.y + Game::camera.pos.y);
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0)
				screen->mouseWheel(false, true);
			else if (event.wheel.y <= 0)
				screen->mouseWheel(true, false);
			break;
		case SDL_QUIT:
			exit = true;
		}
	}
	screen->update(delta);
}
