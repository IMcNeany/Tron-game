#pragma once
#include <string>

enum class GameState
{
	MainMenu = 0,
	Game = 1,
	GameOver = 2,
	connecting = 3
};

//set main menu
GameState gameState = GameState::MainMenu;