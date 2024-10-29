#pragma once
#include "Game_Mode.h"
class Game//: public Game_Mode
{

private:
	Game_Mode gameMode;
	Board board;
	Player player1, player2;
	Player* currentPlayer;

public:
	void ExecuteRound();/// selecteaza o casuta si daca nu e completata pune cartea lui 
	bool CheckWinner();
	void give_cards();
	void ResetGame();
	void SwitchTurn();
	Player* CurrentTurn() const;
	void CurentTurn();/// ce tip este ?
	bool is_over();
	void StartGame();
	void EndGame();
	///void LoadGame();



};

