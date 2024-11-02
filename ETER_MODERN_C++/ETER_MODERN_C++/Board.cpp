#include "Board.h"
#include <iostream>

int Board::getSize() const
{
	return size;
}

void Board::setBoard(int row, int col, const std::stack<Card>& newStack)
{
	if (row >= 0 && row < size && col >= 0 && col < size) {
		board[row][col] = newStack;
	}
}

void Board::UpdateMarked(int row, int col)
{
	marked[row][col] = true;
}

void Board::UpdateUnMarked(int row, int col)
{
	marked[row][col] = false;
}

bool Board::IsEmpty(int row, int col)
{
	return row >= 0 && row < size && col >= 0 && col < size && !marked[row][col];
}

void Board::Display()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << board[i][j].top().getColor() << ' ' << board[i][j].top().getValue();
			if (j < size - 1) std::cout << " | ";
		}
		std::cout << "\n";
		if (i < size - 1) std::cout << "---------\n";
	}
	std::cout << "\n";
}

bool Board::CanMakeMove(int row, int col, Card chosenCard)
{
	return !marked[row][col] || board[row][col].top().getValue() < chosenCard.getValue();
}

bool Board::PlaceCardFacedown(int row, int col)
{
	if (row < 0 || row >= size || col < 0 || col >= size) {
		throw std::out_of_range("Pozitia este in afara limitelor tablei!");
	}
	if (IsEmpty(row, col)) {
		Card facedownCard;
		facedownCard.setValue(-1);
		board[row][col].push(facedownCard);
		return true;
	}
	std::cout << "Pozitia este deja ocupata!" << std::endl;
	return false;
}

void Board::rotateRight()
{
	std::vector<std::vector<std::stack<Card>>> newBoard(size, std::vector<std::stack<Card>>(size));

	for (int r = 0; r < size; ++r) {
		for (int c = 0; c < size; ++c) {
			newBoard[c][size - 1 - r] = board[r][c];
		}
	}
	board = newBoard;
}

void Board::rotateLeft()
{
	std::vector<std::vector<std::stack<Card>>> newBoard(size, std::vector<std::stack<Card>>(size));

	for (int r = 0; r < size; ++r) {
		for (int c = 0; c < size; ++c) {
			newBoard[size - 1 - c][r] = board[r][c];
		}
	}
	board = newBoard;
}

bool Board::MakeMove(int row, int col, Card card)
{
	if (IsEmpty(row, col)) {
		board[row][col].push(card);
		UpdateMarked(row, col);
		return true;
	}
	else
		if (board[row][col].top().getValue() < card.getValue())
		{
			board[row][col].push(card);
			return true;
		}	
	return false;
}

bool Board::CheckWinner(std::string color)
{

	for (int i = 0; i < size; i++) {
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

bool Board::IsDraw()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (marked[i][j] == false) return false;
		}
	}
	return true;

}

void Board::Clear()
{
	board.clear();
}

void Board::Remove(int row , int col)
{
	board[row][col].pop();
	if (board[row][col].empty())
	{
		UpdateUnMarked(row, col);
	}
	
}
