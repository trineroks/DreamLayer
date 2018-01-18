#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SpriteBank.h"
#include "Vector2D.h"
#include "Constants.h"

#include "stateMachine/StateMachine.h"

#include <stdio.h>

class Camera {
public:
	Vector2D pos = Vector2D(0, 0);
	Vector2D delta = Vector2D(0, 0);
	short w, h;
	void setDimensions(short _w, short _h) {
		w = _w;
		h = _h;
	}
	void update() {
		pos += delta;
	}

	bool isWithinView(int _x, int _y) {
		return !(_x > pos.x + w || _x < pos.x || _y > pos.y + h || _y < pos.y);
	}

	void resetPosition() {
		pos.x = 0;
		pos.y = 0;
	}

	void reset() {
		pos.x = 0;
		pos.y = 0;
		delta.x = 0;
		delta.y = 0;
	}
};

class Game {
public:
	Game();
	~Game();

	void init(const char *title, int x, int y, int width, int height, bool fullscreen);

	void run();
	void clear();

	bool running() { return isRunning; };

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static Camera camera;

	static int getScreenWidth() {
		return wscreen;
	}

	static int getScreenHeight() {
		return hscreen;
	}

	static float getScaleW() {
		return wscale;
	}

	static float getScaleH() {
		return hscale;
	}

	static void setScaleW(float s) {
		wscale = s;
	}

	static void setScaleH(float s) {
		hscale = s;
	}

	static void modifyScale(float s) {
		wscale += s;
		hscale += s;
	}

private:
	int counter = 0;
	bool isRunning;
	SDL_Window *window;

	static int wscreen;
	static int hscreen;
	static float wscale;
	static float hscale;
};
