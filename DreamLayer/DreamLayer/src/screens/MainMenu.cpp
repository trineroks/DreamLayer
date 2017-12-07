#include "MainMenu.h"



MainMenu::MainMenu() {
	sprite = new Sprite("assets/GhostAvi.png");
}


MainMenu::~MainMenu() {
}

void MainMenu::cleanUp() {

}

void MainMenu::pause() {

}

void MainMenu::resume() {

}

void MainMenu::update(float deltaTime) {
	sprite->update();
	printf("Sprite position: %d, %d\n", sprite->x, sprite->y);
}

void MainMenu::keyUp(SDL_Keycode key) {
	
}

void MainMenu::keyDown(SDL_Keycode key) {
	switch (key) {
	case SDLK_UP:
		sprite->y -= 1;
		break;
	case SDLK_DOWN:
		sprite->y += 1;
		break;
	case SDLK_RIGHT:
		sprite->x += 1;
		break;
	case SDLK_LEFT:
		sprite->x -= 1;
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