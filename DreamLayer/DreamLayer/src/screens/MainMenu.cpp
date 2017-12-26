#include "MainMenu.h"
#include "../Constants.h"
#include <math.h>
#include <stdio.h>

MainMenu::MainMenu() {
	
}


MainMenu::~MainMenu() {
}

void MainMenu::cleanUp() {
	delete sprite;
	delete nonControlled;
}

void MainMenu::init() {
	sprite = new Sprite(SpriteBank::Instance().Spy);
	sprite->setCollisionBox(Rect(0,0,32, 32));
	sprite->drawDebug = true;
	sprite->posType = sprite->CUSTOM;
	sprite->xoffset = 25;
	sprite->yoffset = 16;
	sprite->collxOffset = 9;
	sprite->setPosition(300, 300);
}

void MainMenu::pause() {

}

void MainMenu::resume() {

}

void MainMenu::update(float deltaTime) {
	currentTime += deltaTime;
	if (currentTime >= FRAMEDELAY) {
		sprite->update();
		currentTime = 0;
	}
	draw();
}

void MainMenu::draw() {
	sprite->render();
}

void MainMenu::keyUp(SDL_Keycode key) {
	switch (key) {
	case SDLK_w:
		sprite->delty = 0;
		break;
	case SDLK_s:
		sprite->delty = 0;
		break;
	case SDLK_d:
		sprite->deltx = 0;
		break;
	case SDLK_a:
		sprite->deltx = 0;
		break;
	}
}

void MainMenu::keyDown(SDL_Keycode key) {
	switch (key) {
	case SDLK_w:
		sprite->delty = -1;
		break;
	case SDLK_s:
		sprite->delty = 1;
		break;
	case SDLK_d:
		sprite->deltx = 1;
		break;
	case SDLK_a:
		sprite->deltx = -1;
		break;
	}
}

void MainMenu::touchDown(int x, int y) {
	//printf("Mouse Down\n");
}

void MainMenu::touchUp(int x, int y) {
	//printf("Mouse Up\n");
}

void MainMenu::touchDragged(int x, int y) {
	float diffx = sprite->x - x;
	float diffy = y - sprite->y;
	float angle = atan(diffx / diffy) * (180 / PI);
	if (diffy < 0) {
		angle += 180;
	}
	sprite->angle = angle;
	printf("Angle generated: %.4f. Diff x: %.4f and Diff y: %.4f\n", angle, diffx, diffy);
}

void MainMenu::mouseMoved(int x, int y) {
	float diffx = sprite->x - x;
	float diffy = y - sprite->y;
	float angle = atan(diffx / diffy) * (180 / PI);
	if (diffy < 0) {
		angle += 180;
	}
	sprite->angle = angle;
	printf("Angle generated: %.4f. Diff x: %.4f and Diff y: %.4f\n", angle, diffx, diffy);
}