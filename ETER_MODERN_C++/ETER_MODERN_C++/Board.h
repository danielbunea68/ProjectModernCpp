#pragma once
#include <vector>
#include <stack>

#include "Card.h"

class Board
{
private:
	int m_size;

	std::vector<std::vector<bool>> marked;
	std::vector<std::vector<std::stack<Card>>> board;


public:
	void SetSize(int size);
	int  GetSize() const;
	std::vector<std::vector<std::stack<Card>>>& GetBoard();
	Card TopCard(int row, int col) const;//aici am lucrat
	void UpdateMarked(int col, int row);
	void UpdateUnMarked(int row, int col);
	bool IsEmpty(int row, int col);
	void Display();
	bool MakeMove(int row, int col, Card card);
	bool CheckWinner(std::string color);
	bool CheckIsBomb();
	bool IsDraw();
	bool IsValidPosition(int row, int col);
	bool CanMakeMove(int row, int col, Card chosenCard);
	int GetStackSize(int row, int col);
	void AddCard(int row , int col ,Card card );
	void SwapStacks(int row1, int col1, int row2, int col2);
	void MoveStack(int srcRow, int srcCol, int destRow, int destCol);
	bool AreAdjacent(int row1, int col1, int row2, int col2);
	void Remove(int row, int cols);//aici am lucrat
	void UpdateCard(int row, int col, const Card& card);
	bool HasCoveredCard(int row, int col, const std::string& color);
	void Clear();

	
};