#pragma once
#include "GameScreen.h"
#include "../Sprite.h"
#include "../SpriteBank.h"
#include "../Rect.h"
#include "../Constants.h"

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
	Sprite* sprite;
	Sprite* nonControlled;
	Rect* test;
};

