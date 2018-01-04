#include "MainMenu.h"
#include "../Constants.h"
#include <math.h>
#include <stdio.h>
#include "../Game.h"
#include "../Terrain.h"
#include "../Tile.h"

MainMenu::MainMenu() {
	
}


MainMenu::~MainMenu() {
}

void MainMenu::cleanUp() {
}

void MainMenu::init() {
	sprite = Sprite(SpriteBank::Instance().Spy);
	sprite.setCollisionBox(Rect(0,0,32, 32));
	sprite.drawDebug = true;
	sprite.posType = sprite.CUSTOM;
	sprite.xoffset = 25;
	sprite.yoffset = 16;
	sprite.collxOffset = 9;
	sprite.setPosition(300, 300);

	crosshair = Sprite(SpriteBank::Instance().Crosshair);
	crosshair.posType = crosshair.CENTER;

	SDL_ShowCursor(SDL_DISABLE);

	map.generate();
	map.drawDebug = true;
}

void MainMenu::pause() {

}

void MainMenu::resume() {

}

void MainMenu::update(float deltaTime) {
	currentTime += deltaTime;
	if (currentTime >= FRAMEDELAY) {
		sprite.update();
		crosshair.update();
		currentTime = 0;
		for (int i = bullets.size() - 1; i >= 0; i--) {
			bounceBullet(&bullets[i]);
			bullets[i].update();
		}
	}
	map.isCollidingPredict(&sprite);
	testAngleUpdate();
	draw();
}

void MainMenu::bounceBullet(Sprite* bullet) {
	if (map.isColliding(bullet)) {
		bullet->revertPos();
		char collType = map.isCollidingWithType(bullet);
		if (collType == CollisionType::VERTICAL) {
			bullet->delta.x *= -1;
		}
		else if (collType == CollisionType::HORIZONTAL) {
			bullet->delta.y *= -1;
		}
		else if (collType == CollisionType::CORNER) {
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
	//printf("Angle generated: %.4f.\n", angle, diffx, diffy);
}

void MainMenu::draw() {
	map.render();
	sprite.render();
	crosshair.render();
	for (int i = bullets.size() - 1; i >= 0; i--) {
		if (bullets[i].pos.x <= 0 || bullets[i].pos.x >= 800 ||
			bullets[i].pos.y <= 0 || bullets[i].pos.y >= 640) {
			bullets.erase(bullets.begin() + i);
			printf("Bullet cleared\n");
		}
		else
			bullets[i].render();
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
	case SDLK_q:
		editing = false;
		break;
	case SDLK_e:
		map.clearMap();
		printf("Map cleared!\n");
		break;
	}
}

void MainMenu::keyDown(SDL_Keycode key) {
	switch (key) {
	case SDLK_w:
		sprite.delta.y = -1;
		//printf("Keypress...");
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
	case SDLK_q:
		editing = true;
		break;
	}
}

void MainMenu::touchDown(int x, int y) {
	if (!editing) {
		Sprite bullet = Sprite(SpriteBank::Instance().Bullet);
		bullet.angle = sprite.angle;
		bullet.setCollisionBox(Rect(0, 0, 3, 3));
		bullet.drawDebug = true;
		bullet.posType = bullet.CUSTOM;
		bullet.xoffset = 2;
		bullet.yoffset = 7;
		bullet.collyOffset = 5;

		float radian = (sprite.angle + 90.0f) * (PI / 180.0f);
		float startposX = sprite.pos.x + (52 * cos(radian));
		float startposY = sprite.pos.y + (52 * sin(radian));
		bullet.setPosition((int)startposX, (int)startposY);

		bullet.delta.x = cos(radian) * 4;
		bullet.delta.y = sin(radian) * 4;

		bullets.push_back(std::move(bullet));
	}
	else {
		map.editTerrainAt(x, y, Tile::wall);
	}
}

void MainMenu::touchUp(int x, int y) {
	//printf("Mouse Up\n");
}

void MainMenu::touchDragged(int x, int y) {
	mousex = x;
	mousey = y;
	if (editing) {
		map.editTerrainAt(x, y, Tile::wall);
	}
}

void MainMenu::mouseMoved(int x, int y) {
	mousex = x;
	mousey = y;
}