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
			bullets[i].update();
		}
	}
	map.handleTerrainCollision(&sprite);
	testAngleUpdate();
	draw();
}

void MainMenu::testAngleUpdate() {
	float diffx = sprite.x - mousex;
	float diffy = mousey - sprite.y;
	float angle = atan(diffx / diffy) * (180 / PI);
	if (diffy < 0) {
		angle += 180;
	}
	sprite.angle = angle;
	crosshair.setPosition(mousex, mousey);
	//printf("Angle generated: %.4f. Diff x: %.4f and Diff y: %.4f\n", angle, diffx, diffy);
}

void MainMenu::draw() {
	map.render();
	sprite.render();
	crosshair.render();
	for (int i = bullets.size() - 1; i >= 0; i--) {
		if (bullets[i].x <= 0 || bullets[i].x >= 800 ||
			bullets[i].y <= 0 || bullets[i].y >= 640) {
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
		sprite.delty = 0;
		break;
	case SDLK_s:
		sprite.delty = 0;
		break;
	case SDLK_d:
		sprite.deltx = 0;
		break;
	case SDLK_a:
		sprite.deltx = 0;
		break;
	case SDLK_q:
		editing = false;
		break;
	}
}

void MainMenu::keyDown(SDL_Keycode key) {
	switch (key) {
	case SDLK_w:
		sprite.delty = -1;
		break;
	case SDLK_s:
		sprite.delty = 1;
		break;
	case SDLK_d:
		sprite.deltx = 1;
		break;
	case SDLK_a:
		sprite.deltx = -1;
		break;
	case SDLK_q:
		editing = true;
		printf("Keypress...");
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
		float startposX = sprite.x + (52 * cos(radian));
		float startposY = sprite.y + (52 * sin(radian));
		bullet.setPosition((int)startposX, (int)startposY);

		bullet.deltx = cos(radian) * 4;
		bullet.delty = sin(radian) * 4;

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
}

void MainMenu::mouseMoved(int x, int y) {
	mousex = x;
	mousey = y;
}