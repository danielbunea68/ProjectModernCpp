#include "Board.h"
#include "Game.h"
#include <iostream>

Board::Board(const Board& other)
{
	if (&other == nullptr) {
		std::cerr << "Error: Attempted to copy from a null object." << std::endl;
		return;
	}
	m_size = other.m_size;
	board = other.board;
	blockedRow = other.blockedRow;

}

Board& Board::operator=(const Board& other)
{

	/*
	if (this != &other) // Self-assignment check
	{
		m_size = other.m_size;
		board = other.board;
		blockedRow = other.blockedRow;
	}
	return *this;
	*/
	if (this == &other || &other == nullptr) {
		return *this;  // Handle self-assignment or null object
	}
	m_size = other.m_size;
	board = other.board;
	blockedRow = other.blockedRow;
	return *this;
}

Board::Board(Board&& other) noexcept
{
	if (&other == nullptr) {
		std::cerr << "Error: Attempted to move from a null object." << std::endl;
		return;
	}
	m_size = other.m_size;
	board = std::move(other.board);
	blockedRow = other.blockedRow;
	other.m_size = 0;
	other.blockedRow = -1;
}

Board& Board::operator=(Board&& other) noexcept
{
	if (this != &other) // Self-assignment check
	{
		m_size = other.m_size;
		board = std::move(other.board);
		blockedRow = other.blockedRow;

		// Reset the moved-from object to a valid state
		other.m_size = 0;
		other.blockedRow = -1;
	}
	return *this;
}

void Board::SetSize(int size)
{
	m_size = size;
	board.resize(m_size, std::vector<std::stack<Card>>(m_size));
}

int Board::GetSize() const
{
	return m_size;
}

Card Board::TopCard(int row, int col) const
{
	return board[row][col].top();
}


std::vector<std::vector<std::stack<Card>>>& Board::GetBoard()
{
	return board;
}

bool Board::IsEmpty(int row, int col)
{
	return row >= 0 && row < GetSize() && col >= 0 && col < GetSize() && board[row][col].empty();
}

void Board::Display()
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			if (board[i][j].empty()) {
				std::cout << "     ";
			}
			else {
				std::cout << board[i][j].top().getColor() << ' ';

				if (board[i][j].top().getIsFaceDown()) {
					std::cout << "x";
				}
				else {
					std::cout << board[i][j].top().getValue();
				}
			}
			if (j < GetSize() - 1) std::cout << " | ";
		}
		std::cout << "\n";
		if (i < GetSize() - 1) std::cout << "----------------------\n";
	}
	std::cout << "\n";
}

int Board::CanMakeMove(int row, int col, Card chosenCard)
{
	if (CountDistinctCards() == 0)
		return 1;

	if (!IsDefinitiveBoard()) {

		if (CheckNeighbours(row, col))
		{
			if (row == -1 || row == m_size || col == -1 || col == m_size)
				return 1;

			if (board[row][col].empty())
				return 1;

			if (board[row][col].top().getValue() < chosenCard.getValue())
				return 1;
		}
	}


	if (!IsValidPosition(row, col))
		return 0;

	if (board[row][col].empty())
		return 1;

	if (board[row][col].top().getValue() > chosenCard.getValue()) {
		if (board[row][col].top().getIsFaceDown())
			return -1;
		else
			return 0;
	}

	return board[row][col].top().getValue() < chosenCard.getValue();
}

bool Board::IsValidPosition(int row, int col) {
	return row >= 0 && row < GetSize() && col >= 0 && col < GetSize();
}

bool Board::MakeMove(int row, int col, Card card)
{
	if (IsEmpty(row, col) || !IsDefinitiveBoard()) {

		ShiftBoard(row, col);
		board[row][col].push(card);

		UpdateLimits();

		return true;
	}
	else
		if (!board[row][col].empty() && board[row][col].top().getValue() < card.getValue())
		{
			ShiftBoard(row, col);
			board[row][col].push(card);

			UpdateLimits();

			return true;
		}


	return false;
}

bool Board::CheckWinner(std::string color)
{

	for (int i = 0; i < GetSize(); i++) {
		if (board[i][0].empty() || board[0][i].empty() || board[i][1].empty() || board[1][i].empty() || board[i][2].empty() || board[2][i].empty())
			return false;

		if ((board[i][0].top().getColor() == color && board[i][1].top().getColor() == color && board[i][2].top().getColor() == color) ||
			(board[0][i].top().getColor() == color && board[1][i].top().getColor() == color && board[2][i].top().getColor() == color)) {
			return true;
		}
	}
	// Verifică diagonalele
	if ((board[0][0].top().getColor() == color && board[1][1].top().getColor() == color && board[2][2].top().getColor() == color) ||
		(board[0][2].top().getColor() == color && board[1][1].top().getColor() == color && board[2][0].top().getColor() == color)) {
		return true;
	}
	return false;

}

bool Board::CheckIsBomb()
{
	int nr = 0;
	for (int i = 0; i < GetSize(); i++)
	{
		bool verif = true;

		for (int j = 0; j < GetSize(); j++)
		{
			if (board[i][j].empty())
				verif = false;
		}
		if (verif)
		{

			nr++;
		}
	}

	for (int j = 0; j < GetSize(); j++)
	{
		bool verif = true;

		for (int i = 0; i < GetSize(); i++)
		{
			if (board[i][j].empty())
				verif = false;
		}
		if (verif)
		{
			nr++;
		}
	}

	if (nr == 2)
		return true;
	else
		return false;
}

bool Board::IsDraw()
{
	for (int i = 0; i < GetSize(); i++) {
		for (int j = 0; j < GetSize(); j++) {
			if (board[i][j].empty()) return false;
		}
	}
	return true;

}

bool Board::CheckNeighbours(int row, int col)
{
	std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, -1}, {1 ,-1}, {1, 1}, {-1, 1} };

	for (auto dir : directions) {
		int nx = row + dir.first;
		int ny = col + dir.second;
		if (nx >= 0 && nx < m_size && ny >= 0 && ny < m_size && !board[nx][ny].empty()) {
			return true;
		}
	}
	return false;

}

void Board::Clear()
{
	board.clear();
}

int Board::GetStackSize(int row, int col)
{
	if (IsValidPosition(row, col))
	{
		return board[row][col].size();
	}
	else
	{
		std::cerr << "Invalid position (" << row << ", " << col << ") on the board.\n";
		return 0;
	}
}


void Board::AddCard(int row, int col, Card card)
{
	board[row][col].push(card);
}

void Board::SwapStacks(int row1, int col1, int row2, int col2)
{
	if (!IsValidPosition(row1, col1) || !IsValidPosition(row2, col2)) {
		std::cout << "Invalid positions for swapping stacks.\n";
		return;
	}
	std::stack<Card> tempStack = board[row1][col1];
	board[row1][col1] = board[row2][col2];
	board[row2][col2] = tempStack;

	std::cout << "Stacks at (" << row1 << ", " << col1 << ") and ("
		<< row2 << ", " << col2 << ") have been swapped.\n";
}

void Board::MoveStack(int srcRow, int srcCol, int destRow, int destCol)
{
	if (!IsValidPosition(srcRow, srcCol) || !IsValidPosition(destRow, destCol))
	{
		std::cerr << "Invalid positions. Source or destination out of bounds.\n";
		return;
	}

	if (IsEmpty(srcRow, srcCol))
	{
		std::cerr << "Source position (" << srcRow << ", " << srcCol << ") is empty. Nothing to move.\n";
		return;
	}

	if (!IsEmpty(destRow, destCol))
	{
		std::cerr << "Destination position (" << destRow << ", " << destCol << ") is not empty.\n";
		return;
	}

	board[destRow][destCol] = std::move(board[srcRow][srcCol]);

	while (!board[srcRow][srcCol].empty())
	{
		board[srcRow][srcCol].pop();
	}

	std::cout << "Moved stack from (" << srcRow << ", " << srcCol << ") to (" << destRow << ", " << destCol << ").\n";
}


bool Board::AreAdjacent(int row1, int col1, int row2, int col2)
{
	if (!IsValidPosition(row1, col1) || !IsValidPosition(row2, col2))
	{
		std::cerr << "Invalid positions. Either one or both positions are out of bounds.\n";
		return false;
	}
	return (std::abs(row1 - row2) + std::abs(col1 - col2)) == 1;
}

void Board::Remove(int row, int col)
{
	if (IsValidPosition(row, col) && !IsEmpty(row, col))
	{
		// Pop the top card from the stack at the specified position
		board[row][col].pop();
		std::cout << "Card removed from position (" << row << ", " << col << ").\n";

		// After removing the card, unmark the position (assuming the pit is no longer relevant after the card is removed)

	}
	else
	{
		std::cout << "Invalid position or no card to remove at (" << row << ", " << col << ").\n";
	}
}

void Board::UpdateCard(int row, int col, const Card& card)
{
	if (!IsValidPosition(row, col))
	{
		std::cerr << "Invalid position (" << row << ", " << col << ").\n";
		return;
	}

	if (board[row][col].empty())
	{
		std::cerr << "No cards at position (" << row << ", " << col << ") to update.\n";
		return;
	}

	board[row][col].pop();
	board[row][col].push(card);

	std::cout << "Updated the top card at position (" << row << ", " << col << ").\n";
}

bool Board::HasCoveredCard(int row, int col, const std::string& color)
{
	if (IsValidPosition(row, col) && !IsEmpty(row, col))
	{
		std::stack<Card>& cardStack = board[row][col];
		if (cardStack.size() > 1)
		{

			Card topCard = cardStack.top();

			cardStack.pop();
			Card secondCard = cardStack.top();

			cardStack.push(topCard);

			if (secondCard.getColor() == color && secondCard.getIsFaceDown())
			{
				return true;
			}
		}
	}
	return false;
}

bool Board::IsFaceDown(int row, int col) const
{
	if (board[row][col].empty()) {
		std::cout << "Nu există nicio carte la poziția (" << row << ", " << col << ").\n";
		return false;
	}

	const Card& topCard = board[row][col].top();

	return topCard.getIsFaceDown();
}

int Board::CountDistinctCards()
{
	int count = 0;
	for (auto row : board) {
		for (auto col : row) {
			count += !col.empty();
		}
	}
	return count;
}

void Board::ShiftBoard(int &row, int &col)
{
	if (!IsDefinitiveBoard()) {

		if (row < 0) {
			row++;
			ShiftDown();
		}
		else if (row > 2) {
			row--;
			ShiftUp();
		}

		if (col < 0) {
			col++;
			ShiftRight();
		}
		else if (col > 2) {
			col--;
			ShiftLeft();
		}
	}
}

inline void Board::ShiftLeft() {
	for (auto& row : board) {
		auto first = std::move(row[0]);
		for (size_t i = 0; i < row.size() - 1; ++i) {
			row[i] = std::move(row[i + 1]);
		}
		row[row.size() - 1] = std::move(first);
	}
}

inline void Board::ShiftRight() {
	for (auto& row : board) {
		auto last = std::move(row[row.size() - 1]);
		for (int i = row.size() - 1; i > 0; --i) {
			row[i] = std::move(row[i - 1]);
		}
		row[0] = std::move(last);
	}
}

inline void Board::ShiftUp() {
	int numCols = board[0].size();
	for (int col = 0; col < numCols; ++col) {
		auto first = std::move(board[0][col]);
		for (int row = 0; row < board.size() - 1; ++row) {
			board[row][col] = std::move(board[row + 1][col]);
		}
		board[board.size() - 1][col] = std::move(first);
	}
}

inline void Board::ShiftDown() {
	int numCols = board[0].size();
	for (int col = 0; col < numCols; ++col) {
		auto last = std::move(board[board.size() - 1][col]);
		for (int row = board.size() - 1; row > 0; --row) {
			board[row][col] = std::move(board[row - 1][col]);
		}
		board[0][col] = std::move(last);
	}
}

inline bool Board::IsDefinitiveBoard() {
	return bottomRow - topRow >= m_size - 1 || rightCol - leftCol >= m_size - 1;
}

