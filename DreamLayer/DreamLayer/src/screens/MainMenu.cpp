#include "MainMenu.h"



MainMenu::MainMenu() {
	sprite = new Sprite(SpriteBank::Instance().Player);
	sprite->setCollisionBox(new Rect(0, 0, 80, 80));

	nonControlled = new Sprite(SpriteBank::Instance().Player);
	nonControlled->setCollisionBox(new Rect(0, 0, 80, 80));
	nonControlled->setPosition(300, 300);
}


MainMenu::~MainMenu() {
}

void MainMenu::cleanUp() {
	delete sprite;
	delete nonControlled;
}

void MainMenu::pause() {

}

void MainMenu::resume() {

}

void MainMenu::update(float deltaTime) {
	sprite->update();
	nonControlled->update();
}

void MainMenu::keyUp(SDL_Keycode key) {
	switch (key) {
	case SDLK_UP:
		sprite->delty = 0;
		break;
	case SDLK_DOWN:
		sprite->delty = 0;
		break;
	case SDLK_RIGHT:
		sprite->deltx = 0;
		break;
	case SDLK_LEFT:
		sprite->deltx = 0;
		break;
	}
}

void MainMenu::keyDown(SDL_Keycode key) {
	switch (key) {
	case SDLK_UP:
		sprite->delty = -1;
		break;
	case SDLK_DOWN:
		sprite->delty = 1;
		break;
	case SDLK_RIGHT:
		sprite->deltx = 1;
		break;
	case SDLK_LEFT:
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
	//printf("Mouse Dragged to %d, %d\n", x, y);
}

void MainMenu::mouseMoved(int x, int y) {
	//printf("Mouse Moved to %d, %d\n", x, y);
}