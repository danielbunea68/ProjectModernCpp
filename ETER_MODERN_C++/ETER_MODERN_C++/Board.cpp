#include "Board.h"
#include "Game.h"
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

Card Board::TopCard(int row, int col) const 
{
	return board[row][col].top(); // Assuming board[row][col] is a stack of Cards
}

void Board::UpdateMarked(int row, int col)
{
	marked[row][col] = true;
}

std::vector<std::vector<std::stack<Card>>>& Board::GetBoard()
{
	return board;
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
		if (!board[row][col].empty() && board[row][col].top().getValue() < card.getValue())
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

	UpdateUnMarked(srcRow, srcCol);
	UpdateMarked(destRow, destCol);

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
		UpdateUnMarked(row, col);  // Unmark the position where the card was removed
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



