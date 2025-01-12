#pragma once
#include <vector>
#include <stack>
#include <set>

#include "Card.h"
#include "Explosion_Card.h"
#include "ranges"

class Board
{
private:
	int m_size;


	std::vector<std::vector<std::stack<Card>>> board;
	std::set<std::pair<int, int>> blockedCells;
	int blockedRow = -1;

	int topRow{ 2 };
	int bottomRow{ 0 };
	int leftCol{ 2 };
	int rightCol{ 0 };



public:
	Board() = default;
	~Board() = default;
	Board(const Board& other);
	Board& operator=(const Board& other);
	Board(Board&& other) noexcept;
	Board& operator=(Board&& other) noexcept;

	void SetSize(int size);
	int  GetSize() const;

	std::vector<std::vector<std::stack<Card>>>& GetBoard() ;///->aici pun const
	Card TopCard(int row, int col) const;
	bool IsEmpty(int row, int col)const;
	void Display()const;
	bool MakeMove(int row, int col, Card card);
	bool CheckWinner(std::string color);
	bool CheckIsBomb();
	bool IsDraw();
	bool CheckNeighbours(int row, int col);
	bool IsValidPosition(int row, int col)const;
	bool IsCoveredByOpponent(int row, int col, const std::string& currentPlayerColor);
	int CanMakeMove(int row, int col, Card chosenCard);
	int GetStackSize(int row, int col);
	void AddCard(int row, int col, Card card);
	void SwapStacks(int row1, int col1, int row2, int col2);
	void MoveStack(int srcRow, int srcCol, int destRow, int destCol);
	bool AreAdjacent(int row1, int col1, int row2, int col2);
	void Remove(int row, int cols);//aici am lucrat
	void UpdateCard(int row, int col, const Card& card);
	bool HasCoveredCard(int row, int col, const std::string& color);
	bool IsFaceDown(int row, int col) const;
	int CountDistinctCards()const;
	bool IsBlockedCell(int row, int col) const;
	void BlockCell(int row, int col);

	void ShiftBoard(int& row, int& col);
	void ShiftLeft();
	void ShiftRight();
	void ShiftUp();
	void ShiftDown();

	bool IsDefinitiveBoard();

	void UpdateLimits();

	void Clear();
};