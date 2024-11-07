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
	void RemoveCard(int row , int col);//aici
	void ReturnCardToPlayer(int row, int col);//aici
	void CreatePit(int row, int col);//aici
	void InitGame(std::string name1, std::string name2);
	std::vector<std::pair<char, std::pair<int, int>>> RotateExplosionCoords(const std::vector<std::pair<char, std::pair<int, int>>>& coords, char rotationChoice);
	void RotateBoardRight();
	void RotateBoardLeft();
	Player* CurrentTurn() const;
	void PlayGame();
	void ResetGame();
};

