#include "Board.h"
#include <iostream>

void Board::SetSize(int size)
{
	m_size = size;
	marked.resize(m_size, std::vector<bool>(m_size));
	board.resize(m_size, std::vector<std::stack<Card>>(m_size));
}

int Board::GetSize() const
{
	return m_size;
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
	return row >= 0 && row < GetSize() && col >= 0 && col < GetSize() && !marked[row][col];
}

void Board::Display()
{
	for (int i = 0; i < GetSize(); i++) {
		for (int j = 0; j < GetSize(); j++) {
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

bool Board::CanMakeMove(int row, int col, Card chosenCard)
{
	if (!IsValidPosition(row, col))
		return 0;

	if (board[row][col].empty())
		return 1;

	if (board[row][col].top().getValue() < chosenCard.getValue())
		return 1;

	if (board[row][col].top().getValue() >= chosenCard.getValue() && board[row][col].top().getIsFaceDown())
		return -1;
}

bool Board::IsValidPosition(int row, int col) {
	return row >= 0 && row < GetSize() && col >= 0 && col < GetSize();
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
			if (marked[i][j] == false) return false;
		}
	}
	return true;

}

void Board::Clear()
{
	board.clear();
}

void Board::Remove(int row, int col)
{
	board[row][col].pop();
	if (board[row][col].empty())
	{
		UpdateUnMarked(row, col);
	}

}
