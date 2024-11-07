#include "Game.h"
#include "Explosion_Card.h"

Game::Game()
{

	currentPlayer = NULL;

}

void Game::InitGame(std::string name1, std::string name2)
{
	player1.setName(name1);
	player2.setName(name2);
	board.SetSize(3);
	std::vector<int> values = { 1, 1, 2, 2, 3, 3, 4 };
	player1.setColor("red");
	player2.setColor("blue");
	for (const auto& value : values) {
		player1.AddCard(Card(value, player1.getColor()));
		player2.AddCard(Card(value, player2.getColor()));
	}
	currentPlayer = &player1;
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

void Game::RemoveCard(int row, int col) //aici
{
	board.Remove(row, col);  // Use the board's Remove function
}

void Game::ReturnCardToPlayer(int row, int col)//aici
{
	if (!board.IsEmpty(row, col))  // Check if there's a card to return
	{
		// Get the card from the board
		Card card = board.TopCard(row, col);
		board.Remove(row, col);  // Remove the card from the board

		// Return the card to the other player's hand
		Player* otherPlayer = (currentPlayer == &player1) ? &player2 : &player1;
		otherPlayer->AddCard(card);  // Add the card to the other player's hand
		std::cout << "Card returned to " << otherPlayer->getName() << "'s hand.\n";
	}
	else
	{
		std::cout << "No card to return at position (" << row << ", " << col << ").\n";
	}
}

void Game::CreatePit(int row, int col) 
{
	board.UpdateMarked(row, col);  // Mark the position as a pit

	// Now, remove all cards from that position using the getter function to access the internal board
	auto& boardGrid = board.GetBoard();  // Get a reference to the board
	while (!boardGrid[row][col].empty()) 
	{
		boardGrid[row][col].pop();  // Remove all cards from the stack at that position
	}

	std::cout << "Pit created at position (" << row << ", " << col << "). All cards removed.\n";
}

void Game::PlayGame()
{
	bool gameOver = false;
	while (!gameOver)
	{
		board.Display();
		currentPlayer->ShowHand();

		// TODO: Daca player-ul curent are o bomba
		// Intreabal daca vrea sa o foloseasca si daca da, afiseaza un meniu in care sa ii spui ca poate roti bomba
		// si apoi sa confirme si sa fie aplicate efectele

		int cardIndex = -1;
		while (!currentPlayer->HasCardAtIndex(cardIndex)) 
		{
			std::cout << currentPlayer->getName() << ", choose a card index to play: ";
			std::cin >> cardIndex;
		}
		Card chosenCard = currentPlayer->PlayCard(cardIndex);

		if (currentPlayer->CanPlaceCardFaceDown()) {
			char answer = 'n';
			std::cout << "Do you want to play this card face down? y/[n]\n";
			std::cin >> answer;
			if (answer == 'y') 
			{
				currentPlayer->PlayedCardFaceDown();
				chosenCard.setFaceDown(true);
			}
		}

		int row = -1, col = -1;
		int result = board.CanMakeMove(row, col, chosenCard);
		while (result == 0) {
			std::cout << "Enter row and column (0, 1, or 2) to place the card: ";
			std::cin >> row >> col;
			result = board.CanMakeMove(row, col, chosenCard);
		}
		if (result == 1) 
		{
			board.MakeMove(row, col, chosenCard);
		}

		if (board.CheckIsBomb())//aici
		{
			Explosion_Card explosion_card(board.GetSize());
			explosion_card.activateExplosion();
			std::vector<std::pair<char, std::pair<int, int>>> coords;
			//right left coords

			for (const auto& pos : coords)
			{
				char bombType = pos.first;
				int row = pos.second.first;
				int col = pos.second.second;
				
				//aplic
			}
			
			//swich

			bool effectApplied = false;
			
			for (const auto& pos : coords) 
			{
				char bombType = pos.first;  // Effect type: 'r', 'u', or 'p'
				int row = pos.second.first;  // Row of the bomb effect
				int col = pos.second.second; // Column of the bomb effect

				switch (bombType)
				{
				case 'r':
					std::cout << "Removing card at (" << row << ", " << col << ").\n";
					RemoveCard(row, col);
					break;
				case 'u':
					std::cout << "Returning card to player at (" << row << ", " << col << ").\n";
					ReturnCardToPlayer(row, col);
					break;
				case 'p':
					std::cout << "Creating pit at (" << row << ", " << col << ").\n";
					CreatePit(row, col);
					break;
				default:
					std::cout << "Unknown effect type at (" << row << ", " << col << ").\n";
					break;
				}

			}

			/// captezi coordonatele ;
			/// if (  dreapta )
			/// board[x][y] - coordonate 90 grade  rotatie la dreapta , rotatie stanga 
			/// aici faci o functie 1 
		}

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
	InitGame(player1.getName(), player2.getName());
}
