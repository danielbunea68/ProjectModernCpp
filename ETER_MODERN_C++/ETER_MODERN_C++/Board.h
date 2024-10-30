#pragma once
#include <vector>
#include"Card.h"
class Board
{
private:
	int size;

	// TODO 4: fa o matrice de stack de Card astfel incat un jucator sa poata puna o carte deasupra 
	// altei carti fara sa o suprascrie
	std::vector < std::vector < Card >> board = {};
	std::vector<std::vector<bool>> marked;



public:
	// TODO 5: sa poata exploda cu o bomba o carte si sa o scoata din stack
	void UpdateMarked(int col, int row);
	bool IsEmpty(int row, int col);
	void Display();
	bool MakeMove(int row, int col, Card card);
	bool CheckWinner(std::string color);
	bool IsDraw();
	bool CanMakeMove(int row, int col, Card chosenCard);
	void Clear();
};
