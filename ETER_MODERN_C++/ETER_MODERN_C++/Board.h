#pragma once
#include <vector>
#include"Card.h"
class Board
{
private:
	int size;

	std::vector < std::vector < Card >> board = {};
	std::vector<std::vector<bool>> marked;

public:

	void UpdateMarked(int col, int row);
	bool IsEmpty(int row, int col);
	void Display();
	bool MakeMove(int row, int col, Card card);
	bool CheckWinner(std::string color);
	bool IsDraw();
	bool CanMakeMove(int row, int col, Card chosenCard);
	void Clear();
};
