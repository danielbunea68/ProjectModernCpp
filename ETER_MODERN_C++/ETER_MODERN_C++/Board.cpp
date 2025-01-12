#include "Board.h"
#include "Game.h"
#include <iostream>
#include <ranges>


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

bool Board::IsEmpty(int row, int col) const
{
	return IsValidPosition(row,col) && board[row][col].empty(); ///modificat
}

void Board::Display() const
{
	/*
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
			if (j < GetSize() ) std::cout << " | ";
		}
		std::cout << "\n";
		/// 8 
		if (i < GetSize()) {
			if (GetSize() > 3) std::cout << "-------------------------------\n";
			else 
			std::cout << "-----------------------\n";
			
		}
	}
	std::cout << "\n";*/
	auto indices = std::views::iota(0, m_size); // Range of indices for rows and columns

	// Lambda to format each cell
	auto formatCell = [&](int i, int j) -> std::string {
		if (board[i][j].empty()) {
			return "     ";
		}
		else {
			std::string result = board[i][j].top().getColor() + " ";
			if (board[i][j].top().getIsFaceDown()) {
				result += "x";
			}
			else {
				result += std::to_string(board[i][j].top().getValue());
			}
			return result;
		}
		};


	std::ranges::for_each(indices, [&](int i) {
		// Print row
		std::ranges::for_each(indices, [&](int j) {
			std::cout << formatCell(i, j);
			if (j < m_size - 1) std::cout << " | ";
			});
		std::cout << "\n";

		// Print separator
		if (i < m_size - 1) {
			std::cout << (m_size > 3 ? "-------------------------------\n" : "-----------------------\n");
		}
		});

	std::cout << "\n";

	
	

}

int Board::CanMakeMove(int row, int col, Card chosenCard)
{
	if (IsBlockedCell(row, col)) 
	{
		std::cout << "Cannot make a move. Cell (" << row << ", " << col << ") is blocked.\n";
		return 0;
	}

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

bool Board::IsValidPosition(int row, int col) const {
	return row >= 0 && row < GetSize() && col >= 0 && col < GetSize();
}

bool Board::IsCoveredByOpponent(int row, int col, const std::string& currentPlayerColor)
{
	if (!IsValidPosition(row, col) || board[row][col].size() < 2)
	{
		return false;
	}

	const Card& topCard = board[row][col].top();

	if (topCard.getColor() != currentPlayerColor)
	{
		return true;
	}

	return false;
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
	int boardSize = board.size(); // Assuming a square board

	// Helper lambda to check if a stack has the given color on top
	auto hasTopCardWithColor = [&](int row, int col) -> bool {
		return !board[row][col].empty() && board[row][col].top().getColor() == color;
		};

	// Check rows for a win
	//for (int i = 0; i < boardSize; ++i) {
	//	bool rowWin = true;
	//	for (int j = 0; j < boardSize; ++j) {
	//		if (!hasTopCardWithColor(i, j)) {
	//			rowWin = false;
	//			break;
	//		}
	//	}
	//	if (rowWin) return true;
	//}
	auto rows = std::views::iota(0, boardSize); // Range of row indices

	bool rowWin= std::ranges::any_of(rows, [&](int i) {
		auto columns = std::views::iota(0, boardSize); // Range of column indices
		return std::ranges::all_of(columns, [&](int j) {
			return hasTopCardWithColor(i, j);
			});
		});
	if (rowWin) return true;

	// Check columns for a win
	/*for (int j = 0; j < boardSize; ++j) {
		bool colWin = true;
		for (int i = 0; i < boardSize; ++i) {
			if (!hasTopCardWithColor(i, j)) {
				colWin = false;
				break;
			}
		}
		if (colWin) return true;
	}*/

	auto columns = std::views::iota(0, boardSize); // Range of column indices
	bool colWin = std::ranges::any_of(columns, [&](int j) {
		auto rows = std::views::iota(0, boardSize); // Range of row indices
		return std::ranges::all_of(rows, [&](int i) {
			return hasTopCardWithColor(i, j);
			});
		});
	if (colWin) return true;



	//// Check main diagonal (top-left to bottom-right)
	//bool mainDiagonalWin = true;
	//for (int i = 0; i < boardSize; ++i) {
	//	if (!hasTopCardWithColor(i, i)) {
	//		mainDiagonalWin = false;
	//		break;
	//	}
	//}
	//if (mainDiagonalWin) return true;

	auto indices = std::views::iota(0, boardSize); 
	bool mainDiagonalWin =  std::ranges::all_of(indices, [&](int i) {
		return hasTopCardWithColor(i, i);
		});
	if (mainDiagonalWin) return true;

	// Check anti-diagonal (top-right to bottom-left)
	/*bool antiDiagonalWin = true;
	for (int i = 0; i < boardSize; ++i) {
		if (!hasTopCardWithColor(i, boardSize - 1 - i)) {
			antiDiagonalWin = false;
			break;
		}
	}
	if (antiDiagonalWin) return true;*/
	
	
	bool antiDiagonalWin= std::ranges::all_of(indices, [&](int i) {
		return hasTopCardWithColor(i, boardSize - 1 - i);
		});
	if (antiDiagonalWin) return true;

	// No winning formation found
	return false;
}

bool Board::CheckIsBomb()
{
	int nr = 0;
	/*for (int i = 0; i < GetSize(); i++)
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
	}*/
	auto indices1 = std::views::iota(0, static_cast<int>(board.size())); // Range of row indices

	// Count rows where all cells are non-empty
	std::ranges::for_each(indices1, [&](int i) {
		auto row = board[i];
		if (std::ranges::all_of(row, [](const std::stack<Card>& stack) {
			return !stack.empty();
			})) {
			nr++; // Incrementăm dacă rândul este complet
		}
		});


	/*for (int j = 0; j < GetSize(); j++)
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
}*/
	auto indices2 = std::views::iota(0, static_cast<int>(board.size()));
	std::ranges::for_each(indices2, [&](int j) {
		auto col = board[j];
		if (std::ranges::all_of(col, [](const std::stack<Card>& stack) {
			return !stack.empty();
			})) {
			nr++; 
		}
		});

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

int Board::CountDistinctCards()const 
{
	int count = 0;
	for (auto row : board) {
		for (auto col : row) {
			count += !col.empty();
		}
	}
	return count;
}

bool Board::IsBlockedCell(int row, int col) const
{
	return blockedCells.find({ row, col }) != blockedCells.end();
}

void Board::BlockCell(int row, int col)
{
	if (row >= 0 && row < m_size && col >= 0 && col < m_size) 
	{
		blockedCells.insert({ row, col });
	}
}

void Board::ShiftBoard(int &row, int &col)
{
	if (!IsDefinitiveBoard()) {

		if (row < 0) {
			row++;
			ShiftDown();
		}
		else if (row > m_size - 1) {
			row--;
			ShiftUp();
		}

		if (col < 0) {
			col++;
			ShiftRight();
		}
		else if (col > m_size - 1) {
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

void Board::UpdateLimits()
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			if (!board[i][j].empty()) {
				bottomRow = std::max(bottomRow, i);
				topRow = std::min(topRow, i);
				leftCol = std::min(leftCol, j);
				rightCol = std::max(rightCol, j);
			}

		}
	}
}

