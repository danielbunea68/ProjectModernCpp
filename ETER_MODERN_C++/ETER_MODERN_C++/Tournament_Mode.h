
#pragma once
#include "Board.h"
#include "Player.h"
#include "IGame.h"
class Tournament_Mode :public IGame
{

private:
	Board board;
	Player player1, player2;
	Player* currentPlayer;
	Board boardt;
	void SwitchTurn();

public:
	

	void RemoveCard(int row, int col) override;

	void ReturnCardToPlayer(int row, int col)override;

	void CreatePit(int row, int col)override;

	void InitGame(std::string name1, std::string name2)override;

	Player* CurrentTurn() const;

	void PlayGame()override;
	void ResetGame()override;
};