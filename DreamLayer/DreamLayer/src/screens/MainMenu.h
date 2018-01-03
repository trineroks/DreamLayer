#pragma once
#include "GameScreen.h"
#include "../Sprite.h"
#include "../SpriteBank.h"
#include "../Rect.h"
#include "../Constants.h"
#include "../Map.h"
#include <vector>

class Sprite;
class Rect;
class MainMenu : public GameScreen {
public:
	MainMenu();
	~MainMenu();

	void cleanUp() override;
	void pause() override;
	void resume() override;
	void init() override;

	void keyUp(SDL_Keycode key) override;
	void keyDown(SDL_Keycode key) override;
	void touchDown(int x, int y) override;
	void touchUp(int x, int y) override;
	void touchDragged(int x, int y) override;
	void mouseMoved(int x, int y) override;

	void update(float deltaTime) override;
	void draw();
private:
	std::vector<Sprite> bullets;

	Sprite sprite;
	Sprite nonControlled;
	Sprite crosshair;
	Map map;

	Rect* test;

	void testAngleUpdate();

	bool editing = false;

	int mousex = 0;
	int mousey = 0;
};

