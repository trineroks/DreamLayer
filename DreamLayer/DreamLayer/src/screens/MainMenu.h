#pragma once
#include "GameScreen.h"
#include "../Sprite.h"

class MainMenu : public GameScreen {
public:
	MainMenu();
	~MainMenu();

	void cleanUp() override;
	void pause() override;
	void resume() override;

	void keyUp(SDL_Keycode key) override;
	void keyDown(SDL_Keycode key) override;
	void touchDown(int x, int y) override;
	void touchUp(int x, int y) override;
	void touchDragged(int x, int y) override;
	void mouseMoved(int x, int y) override;

	void update(float deltaTime) override;

private:
	Sprite* sprite;
};

