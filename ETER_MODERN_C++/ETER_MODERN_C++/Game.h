#pragma once
#include "Game_Mode.h"
class Game
{

private:
	Game_Mode gameMode;
	Board board;
	Player player1, player2;
	Player* currentPlayer;

	void SwitchTurn();

public:
	Game();
	void InitGame(std::string name1, std::string name2);
	Player* CurrentTurn() const;
	void PlayGame();
	void ResetGame();
};

