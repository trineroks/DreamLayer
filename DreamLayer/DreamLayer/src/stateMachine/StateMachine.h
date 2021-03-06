#pragma once
#include "../screens/GameScreen.h"
#include "../screens/MainMenu.h"
#include "../Game.h"
#include <vector>
#include <memory>

class StateMachine {
public:
	static StateMachine &Instance();

	void changeScreen(GameScreen* screen);
	void pushScreen(GameScreen* screen);
	void popScreen();
	void gameTick(float deltaTime);

	void quit() { exit = true; }
	bool getExitState() { return exit; }

private:
	void processTick(float delta);

	StateMachine();
	StateMachine(StateMachine const&);

	std::vector<GameScreen*> screenStack;
	bool clicked = false;
	bool exit;
};