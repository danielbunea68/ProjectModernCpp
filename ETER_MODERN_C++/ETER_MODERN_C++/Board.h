#pragma once
#include <vector>
#include"Card.h"
#include <stack>
class Board
{
private:
	int size;

	std::vector<std::vector<bool>> marked;
	std::vector<std::vector<std::stack<Card>>> board;


public:
	// TODO 5: sa poata exploda cu o bomba o carte si sa o scoata din stack
	void UpdateMarked(int col, int row);
	void UpdateUnMarked(int row, int col);
	bool IsEmpty(int row, int col);
	void Display();
	bool PlaceCardFacedown(int row, int col);
	bool MakeMove(int row, int col, Card card);
	bool CheckWinner(std::string color);
	bool IsDraw();
	bool CanMakeMove(int row, int col, Card chosenCard);
	void Remove(int row, int cols);
	void Clear();
};
