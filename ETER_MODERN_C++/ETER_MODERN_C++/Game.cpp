#include "Game.h"


void Game::InitGame()
{
	std::vector<int> values = { 1, 1, 2, 2, 3, 3, 4 };
	player1.setColor("red");
	player2.setColor("blue");
	for (const auto& value : values) {
		player1.AddCard(Card(value, player1.getColor()));
		player2.AddCard(Card(value, player2.getColor()));
	}
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

void Game::PlayGame()
{
	bool gameOver = false;
	while (!gameOver)
	{
		board.Display();
		currentPlayer->ShowHand();

		

		int cardIndex = -1;
		while (!currentPlayer->HasCardAtIndex(cardIndex)) {
			std::cout << currentPlayer->getName() << ", choose a card index to play: ";
			std::cin >> cardIndex;
		}
		Card chosenCard = currentPlayer->PlayCard(cardIndex);

		int row = -1, col = -1;
		while (!board.CanMakeMove(row, col, chosenCard)) {
			std::cout << "Enter row and column (0, 1, or 2) to place the card: ";
			std::cin >> row >> col;
			board.MakeMove(row, col, chosenCard);
		}
		/// to do 2 
		/// verifica daca este completa o linie si o coloana care se intersecteaza cu ajutorul matricei marked 
		/// apelezi functia de bomba 
		if (board.CheckWinner(chosenCard.getColor())) {
			board.Display();
			std::cout << currentPlayer->getName() << " wins!\n";
			gameOver = true;
		}
		else if (board.IsDraw()) {
			board.Display();
			std::cout << "It's a draw!\n";
			gameOver = true;
		}
		else {
			SwitchTurn();
		}
	}
}

void Game::ResetGame()
{
	board.Clear();
	player1.ClearCards();
	player2.ClearCards();
	InitGame();
}
