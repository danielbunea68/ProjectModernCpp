﻿#pragma once
#include "Board.h"
#include "Player.h"

class Game
{

protected:
	Board board;
	Player player1, player2;
	Player* currentPlayer;
	std::pair<int, int> lastCardPositionPlayer1;  //aici
	std::pair<int, int> lastCardPositionPlayer2;  

	void SwitchTurn();

public:
	Game();
	void RemoveCard(int row, int col);//aici
	void ReturnCardToPlayer(int row, int col);//aici
	void CreatePit(int row, int col);//aici
	void DestroyLastOpponentCard();
	void ReturnVisibleOpponentCard();  // Funcția pentru întoarcerea cărții vizibile
	void InitGame(std::string name1, std::string name2);
	
	Player* CurrentTurn() const;
	void PlayGame();
	void ResetGame();

	void AfterInitialization();
	void AfterReset();
};

