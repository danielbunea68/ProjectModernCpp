#include "Game.h"

void Game::give_cards()
{

}

void Game::InitGame()
{

}

void Game::SwitchTurn()
{
    if (currentPlayer->getName() == player1.getName()) 
    {
        currentPlayer = &player2; 
    }
    else 
    {
        currentPlayer = &player1; 
    }
}

Player* Game::CurrentTurn() const
{
    return currentPlayer;
}

void Game::StartGame()
{
    bool gameOver = false;
    while (!gameOver)
    {
        board.display();
        std::cout<<currentPlayer->getName()<<currentPlayer->
    }
}
