#pragma once
#include <vector>
#include"Card.h"
#include <stack>
class Board
{
private:
	int m_size;

	std::vector<std::vector<bool>> marked;
	std::vector<std::vector<std::stack<Card>>> board;


public:
	void SetSize(int size);
	int  GetSize() const;

	void UpdateMarked(int col, int row);
	void UpdateUnMarked(int row, int col);
	bool IsEmpty(int row, int col);
	void Display();
	bool MakeMove(int row, int col, Card card);
	bool CheckWinner(std::string color);
	bool IsDraw();
	bool IsValidPosition(int row, int col);
	bool CanMakeMove(int row, int col, Card chosenCard);
	void Remove(int row, int cols);
	void Clear();

	
};
