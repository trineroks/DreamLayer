#include "MainMenu.h"
#include "../Constants.h"
#include <math.h>
#include <stdio.h>
#include "../Game.h"
#include "../Terrain.h"
#include "../Tile.h"
#include <stdlib.h>

MainMenu::MainMenu() {
	
}


MainMenu::~MainMenu() {
}

void MainMenu::cleanUp() {
}

void MainMenu::init() {
	Game::setScaleW(1.0f);
	Game::setScaleH(1.0f);
	map.generate();
	//map.drawDebug = true;
	Point p = map.getPixelPositionInMap(5, 5);

	sprite = Character(SpriteBank::Instance().PlayerN, SpriteBank::Instance().PlayerS);
	sprite.setCollisionBox(Rect(0,0,32, 16));
	sprite.drawDebug = true;
	sprite.setOrientationType(sprite.BOTTOMCENTER);
	sprite.setPosition(p.x, p.y);
	sprite.scale(Game::getScaleW(), Game::getScaleH());
	
	map.addPlayer(sprite);

	crosshair = Sprite(SpriteBank::Instance().Crosshair);
	crosshair.setOrientationType(crosshair.CENTER);

	//SDL_ShowCursor(SDL_DISABLE);
	
}

void MainMenu::pause() {

}

void MainMenu::resume() {

}

void MainMenu::update(float deltaTime) {
	currentTime += deltaTime;
	if (currentTime >= FRAMEDELAY) {
		Game::camera.update();
		sprite.update(&map);
		crosshair.update();
		currentTime = 0;
	}
	map.willCollideHandle(&sprite);
	testAngleUpdate();
	map.update(deltaTime);
	draw();
	map.renderWallLayer(deltaTime);
	if (fog)
		map.renderFogLayer();
}

void MainMenu::testAngleUpdate() {
	crosshair.setPosition(mousex, mousey);
}

void MainMenu::draw() {
	sprite.scale(Game::getScaleW(), Game::getScaleH());
}

void MainMenu::keyUp(SDL_Keycode key) {
	switch (key) {
	case SDLK_w:
		sprite.delta.y = 0;
		break;
	case SDLK_s:
		sprite.delta.y = 0;
		break;
	case SDLK_d:
		sprite.delta.x = 0;
		break;
	case SDLK_a:
		sprite.delta.x = 0;
		break;
	case SDLK_UP:
		Game::camera.delta.y = 0;
		break;
	case SDLK_DOWN:
		Game::camera.delta.y = 0;
		break;
	case SDLK_LEFT:
		Game::camera.delta.x = 0;
		break;
	case SDLK_RIGHT:
		Game::camera.delta.x = 0;
		break;
	case SDLK_q:
		editing = 0;
		break;
	case SDLK_f:
		fog = !fog;
		break;
	case SDLK_r:
		map.clearMap();
		printf("Map cleared!\n");
		break;
	case SDLK_t:
		SpriteBank::Instance().reload();
		break;
	default:
		editing = 0;
		break;
	}
}

void MainMenu::keyDown(SDL_Keycode key) {
	switch (key) {
	case SDLK_w:
		sprite.delta.y = -1;
		break;
	case SDLK_s:
		sprite.delta.y = 1;
		break;
	case SDLK_d:
		sprite.delta.x = 1;
		break;
	case SDLK_a:
		sprite.delta.x = -1;
		break;
	case SDLK_UP:
		Game::camera.delta.y = -1 * 5;
		break;
	case SDLK_DOWN:
		Game::camera.delta.y = 1 * 5;
		break;
	case SDLK_RIGHT:
		Game::camera.delta.x = 1 * 5;
		break;
	case SDLK_LEFT:
		Game::camera.delta.x = -1 * 5;
		break;
	case SDLK_q:
		editing = 1;
		break;
	case SDLK_e:
		editing = 2;
		break;
	}
}

void MainMenu::touchDown(int x, int y) {
	int r = rand() % 3;
	if (editing != 0) {
		switch (editing) {
		case 1:
			switch (r) {
			case 0:
				map.editTerrainAt(x, y, Tile::wall1);
				break;
			case 1:
				map.editTerrainAt(x, y, Tile::wall2);
				break;
			case 2:
				map.editTerrainAt(x, y, Tile::wallwater);
				break;
			}
			break;
		case 2:
			map.editTerrainAt(x, y, Tile::floor1);
			break;
		default:
			break;
		}
	}
}

void MainMenu::touchUp(int x, int y) {
	//printf("Mouse Up\n");
}

void MainMenu::touchDragged(int x, int y) {
	mousex = x;
	mousey = y;
	int r = rand() % 3;

	if (editing != 0) {
		switch (editing) {
		case 1:
			switch (r) {
			case 0:
				map.editTerrainAt(x, y, Tile::wall1);
				break;
			case 1:
				map.editTerrainAt(x, y, Tile::wall2);
				break;
			case 2:
				map.editTerrainAt(x, y, Tile::wallwater);
				break;
			}
			break;
		case 2:
			map.editTerrainAt(x, y, Tile::floor1);
			break;
		default:
			break;
		}
	}
}

void MainMenu::mouseMoved(int x, int y) {
	mousex = x;
	mousey = y;
}

void MainMenu::mouseWheel(bool scrollDown, bool scrollUp) {
	if (scrollDown) {
		Game::modifyScale(-0.1f);
	}
	else if (scrollUp) {
		Game::modifyScale(0.1f);
	}
}