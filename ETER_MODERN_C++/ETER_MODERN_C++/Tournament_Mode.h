
#pragma once
#include "Board.h"
#include "Player.h"
#include "IGame.h"
#include "Game.h"
#include "Wizard_Mode.h"
#include "Element_Mode.h"

#include <vector>
#include <string>
enum class BaseMode {
	Training,
	MageDuel,
	ElementalBattle
};
class Tournament_Mode 
{

private:
    IGame* game = nullptr;
    std::vector < std::vector< std::string>> tournament_board;
	char  m_mode; 
	bool isover = false;


public:

	void choseGame();

	void setmode(char mode);
	bool CheckWinner(std::string color);

	int NumberOfTokens(std::string color);

	void PlayGameChosen(std::string name1, std::string name2);

	void updateBoard(int row, int col, std::string color);
};
