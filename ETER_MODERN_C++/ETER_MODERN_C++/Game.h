#pragma once
#include "Board.h"
#include "Player.h"

class Game
{

private:
	Board board;
	Player player1, player2;
	Player* currentPlayer;

	void SwitchTurn();

public:
	Game();
	void RemoveCard(int row, int col);//aici
	void ReturnCardToPlayer(int row, int col);//aici
	void CreatePit(int row, int col);//aici
	void InitGame(std::string name1, std::string name2);
	Player* CurrentTurn() const;
	void PlayGame();
	void ResetGame();
};

