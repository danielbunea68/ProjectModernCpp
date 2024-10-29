#pragma once
#include "Game_Mode.h"
class Game//: public Game_Mode
{

private:
	Game_Mode gameMode;
	Board board;
	Player player1, player2;

	void ExecuteRound();
	/// selecteaza o casuta si daca nu e completata pune cartea lui 
	/// verifica daca a facut 2 liniii si pune aplica explozia , 
	/// apeleza fcuntia de rotate table 
	/// apleaza functia chech the winner ;
	/// apleaza functia switch turn ;
	bool CheckWinner();/// verfica tabla de joc daca este completatat pe diagonala sau linii de acelasi player
	void  friend give_cards(); /// override - 
	void ResetGame();
	void SwitchTurn();
	bool CurentTurn();
	///bool is_over();
	void StartGame();/// initializeza o tabla goala si apeleaza functia de give cards 

	Player* currentPlayer;

public:
	void ExecuteRound();/// selecteaza o casuta si daca nu e completata pune cartea lui 
	bool CheckWinner();
	void give_cards();
	void ResetGame();
	void SwitchTurn();
	Player* CurrentTurn() const;

	
	bool is_over();
	void StartGame();

	void EndGame();
	///void LoadGame();



};

