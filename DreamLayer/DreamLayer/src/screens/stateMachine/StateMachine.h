#pragma once
#include "../GameScreen.h"
#include "../../Game.h"
#include "../MainMenu.h"
#include <vector>

class StateMachine {
public:
	static StateMachine &getInstance();

	void changeScreen(GameScreen* screen);
	void pushScreen(GameScreen* screen);
	void popScreen();
	void gameTick(float deltaTime);

	void quit() { exit = true; }
	bool getExitState() { return exit; }

private:
	void processInput();

	StateMachine();
	StateMachine(StateMachine const&);

	std::vector<GameScreen*> screenStack;
	bool clicked = false;
	bool exit;
};