#include "Board.h"
#include <iostream>

void Board::UpdateMarked(int row, int col)
{
	marked[row][col] = true;
}

bool Board::IsEmpty(int row, int col)
{
	return row >= 0 && row < size && col >= 0 && col < size && !marked[row][col];
}

void Board::Display()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << board[i][j].getColor() << ' ' << board[i][j].getValue();
			if (j < size - 1) std::cout << " | ";
		}
		std::cout << "\n";
		if (i < size - 1) std::cout << "---------\n";
	}
	std::cout << "\n";
}

bool Board::CanMakeMove(int row, int col, Card chosenCard)
{
	return !marked[row][col] || board[row][col].getValue() < chosenCard.getValue();
}

bool Board::MakeMove(int row, int col, Card card)
{
	if (IsEmpty(row, col)) {
		board[row][col] = card;
		UpdateMarked(row, col);
		return true;
	}

	return false;
}

bool Board::CheckWinner(std::string color)
{

	for (int i = 0; i < size; i++) {
		if ((board[i][0].getColor() == color && board[i][1].getColor() == color && board[i][2].getColor() == color) ||
			(board[0][i].getColor() == color && board[1][i].getColor() == color && board[2][i].getColor() == color)) {
			return true;
		}
	}
	// Verifică diagonalele
	if ((board[0][0].getColor() == color && board[1][1].getColor() == color && board[2][2].getColor() == color) ||
		(board[0][2].getColor() == color && board[1][1].getColor() == color && board[2][0].getColor() == color)) {
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
