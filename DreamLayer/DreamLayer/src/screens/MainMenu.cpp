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

	sprite = Character(SpriteBank::Instance().Spy, SpriteBank::Instance().SpyHolstered);
	sprite.setCollisionBox(Rect(0,0,32, 32));
	sprite.drawDebug = true;
	sprite.setCustomOrientationType(25, 16, 9, 0);
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
		for (int i = bullets.size() - 1; i >= 0; i--) {
			bounceBullet(&bullets[i]);
			bullets[i].update();
		}
	}
	Point p = map.getPositionInLightMap(sprite.pos.x, sprite.pos.y);
	printf("Lightmap coordinate: %d, %d\n", p.x, p.y);
	map.isCollidingPredict(&sprite);
	testAngleUpdate();
	map.update(deltaTime);
	draw();
	map.renderWallAndFogLayer(deltaTime);
}

void MainMenu::bounceBullet(Sprite* bullet) {
	if (map.isColliding(bullet)) {
		char collType = map.isCollidingWithType(bullet);
		bullet->revertPos();
		if (collType == CollisionType::VERTICAL) {
			bullet->angle *= -1;
			bullet->delta.x *= -1;
		}
		else if (collType == CollisionType::HORIZONTAL) {
			bullet->angle *= -1;
			bullet->angle -= 180;
			bullet->delta.y *= -1;
		}
		else if (collType == CollisionType::CORNER) {
			bullet->angle += 180;
			bullet->delta.x *= -1;
			bullet->delta.y *= -1;
		}
	}
}

void MainMenu::testAngleUpdate() {
	float diffx = sprite.pos.x - mousex;
	float diffy = mousey - sprite.pos.y;
	float angle = atan(diffx / diffy) * (180 / PI);
	if (diffy < 0) {
		angle += 180;
	}
	sprite.angle = angle;
	crosshair.setPosition(mousex, mousey);
}

void MainMenu::draw() {
	sprite.scale(Game::getScaleW(), Game::getScaleH());
	sprite.render();
	crosshair.render();
	for (int i = bullets.size() - 1; i >= 0; i--) {
		if (bullets[i].pos.x <= 0 || bullets[i].pos.x >= 800 ||
			bullets[i].pos.y <= 0 || bullets[i].pos.y >= 640) {
			bullets.erase(bullets.begin() + i);
			printf("Bullet cleared\n");
		}
		else {
			bullets[i].scale(Game::getScaleW(), Game::getScaleH());
			bullets[i].render();
		}
	}
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
	else if (!sprite.getHolstered()) {
		Sprite bullet = Sprite(SpriteBank::Instance().Bullet);
		bullet.angle = sprite.angle;
		bullet.setCollisionBox(Rect(0, 0, 3, 3));
		bullet.drawDebug = true;
		bullet.setCustomOrientationType(2, 7, 0, 5);

		float radian = (sprite.angle + 90.0f) * (PI / 180.0f);
		float startposX = sprite.pos.x + (52 * cos(radian) * Game::getScaleW());
		float startposY = sprite.pos.y + (52 * sin(radian) * Game::getScaleH());
		bullet.setPosition((int)startposX, (int)startposY);

		bullet.delta.x = cos(radian) * 7 * Game::getScaleW();
		bullet.delta.y = sin(radian) * 7 * Game::getScaleH();
		bullet.scale(Game::getScaleW(), Game::getScaleH());

		bullets.push_back(std::move(bullet));
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