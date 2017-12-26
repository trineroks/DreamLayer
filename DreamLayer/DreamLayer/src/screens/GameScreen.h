#pragma once
#include "SDL.h"
#include <iostream>

class GameScreen {
public:
	virtual void cleanUp() = 0;
	virtual void init() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void update(float deltaTime) = 0;

	virtual void keyUp(SDL_Keycode key) {};
	virtual void keyDown(SDL_Keycode key) {};
	virtual void touchDown(int x, int y) {};
	virtual void touchUp(int x, int y) {};
	virtual void touchDragged(int x, int y) {};
	virtual void mouseMoved(int x, int y) {};

protected:
	float currentTime = 0;
};