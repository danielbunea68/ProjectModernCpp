#include "Board.h"
#include <iostream>

void Board::updateMarked(int col, int row)
{
    marked[row][col] = true;
}

bool Board::verifyEmpty(int row, int col)
{
    return  marked[row][col];
}

void Board::display()
{
   std:: cout << "\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
           std:: cout << board[i][j].getColor();
            if (j < size - 1) std::cout << " | ";
        }
       std:: cout << "\n";
        if (i < size - 1) std:: cout << "---------\n";
    }
    std::cout << "\n";
}

bool Board::makeMove(int col, int row, Card card )
{
  
        if (row >= 0 && row < size && col >= 0 && col < size && verifyEmpty(row,col  ) ==false){
            board[row][col]= card;
            return true;
        }
        return false;
    
    return false;
}

bool Board::CheckWinner(Card card)
{

    for (int i = 0; i < size; i++) {
        if ((board[i][0].getColor() == card.getColor() && board[i][1].getColor() == card.getColor() && board[i][2].getColor() == card.getColor()) ||
            (board[0][i].getColor() == card.getColor() && board[1][i].getColor() == card.getColor() && board[2][i].getColor() == card.getColor())) {
            return true;
        }
    }
    // Verifică diagonalele
    if ((board[0][0].getColor() == card.getColor() && board[1][1].getColor() == card.getColor() && board[2][2].getColor() == card.getColor()) ||
        (board[0][2].getColor() == card.getColor() && board[1][1].getColor() == card.getColor() && board[2][0].getColor() == card.getColor())) {
        return true;
    }
    return false;
   
}

bool Board::isDraw()
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (marked[i][j] == false  ) return false;
        }
    }
    return true;
 
}

void Board::resetBoard()
{
    board.clear();
}
