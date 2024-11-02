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
	void InitGame();
	Player* CurrentTurn() const;
	void rotateRight();
	void rotateLeft();
	void PlayGame();
	void ResetGame();
};