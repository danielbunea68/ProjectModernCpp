#pragma once
#include "Game_Mode.h"
class Game//: public Game_Mode
{
public:

	Game_Mode gameMode;
	Board board;
	Player player1, player2;
	void ExecuteRound();/// selecteaza o casuta si daca nu e completata pune cartea lui 
	bool CheckWinner();
	void give_cards();
	void ResetGame();
	void SwitchTurn();
	void CurentTurn();/// ce tip este ?
	bool is_over();
	void StartGame();
	void EndGame();
	///void LoadGame();



};

