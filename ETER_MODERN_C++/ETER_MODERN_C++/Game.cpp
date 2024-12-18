#include "Game.h"
#include "Explosion_Card.h"

Game::Game()
{

	currentPlayer = NULL;

}

Game::Game(const Game& other)
{
	board = other.board;
	player1 = other.player1;
	player2 = other.player2;
	if (other.currentPlayer == &other.player1)
		currentPlayer = &player1;
	else if (other.currentPlayer == &other.player2)
		currentPlayer = &player2;
	else
		currentPlayer = nullptr;
}

Game& Game::operator=(const Game& other)
{
	if (this == &other)
		return *this; // Handle self-assignment

	board = other.board;
	player1 = other.player1;
	player2 = other.player2;

	// Deep copy for currentPlayer
	if (other.currentPlayer == &other.player1)
		currentPlayer = &player1;
	else if (other.currentPlayer == &other.player2)
		currentPlayer = &player2;
	else
		currentPlayer = nullptr;

	return *this;
}

Game::Game(Game&& other) noexcept
{
	board = std::move(other.board);
	player1 = std::move(other.player1);
	player2 = std::move(other.player2);
	currentPlayer = other.currentPlayer == &other.player1 ? &player1 :
		other.currentPlayer == &other.player2 ? &player2 : nullptr;
	other.currentPlayer = nullptr;

}

Game& Game::operator=(Game&& other) noexcept
{
	if (this == &other)
		return *this; // Handle self-assignment

	board = std::move(other.board);
	player1 = std::move(other.player1);
	player2 = std::move(other.player2);

	// Move currentPlayer
	currentPlayer = (other.currentPlayer == &other.player1) ? &player1 :
		(other.currentPlayer == &other.player2) ? &player2 : nullptr;

	other.currentPlayer = nullptr;

	return *this;
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
	player1.isTurn = true;
}

Player* Game::CurrentTurn()
{
	return currentPlayer;
}

Player* Game::PreviousTurn()
{
	if (currentPlayer->getName() == player1.getName())
		return &player2;
	else
		return &player1;
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
	player1.isTurn = !player1.isTurn;
	player2.isTurn = !player2.isTurn;
	currentPlayer->selectedIndex = 0;
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

		if (card.getColor() == currentPlayer->getColor()) {
			currentPlayer->AddCard(card);
			std::cout << "Card returned to " << currentPlayer->getName() << "'s hand.\n";
		}
		else {
			// Return the card to the other player's hand
			Player* otherPlayer = (currentPlayer == &player1) ? &player2 : &player1;
			otherPlayer->AddCard(card);  // Add the card to the other player's hand
			std::cout << "Card returned to " << otherPlayer->getName() << "'s hand.\n";
		}
	}
	else
	{
		std::cout << "No card to return at position (" << row << ", " << col << ").\n";
	}
}

void Game::CreatePit(int row, int col)
{


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

		int row, col;
		int result;

		do {
			std::cout << "Enter the row and column to place the card (0, 1, or 2).\n";
			if (!board.IsDefinitiveBoard()) {
				std::cout << "If the board is not definitive, you may also enter (-1, 3) to place the card in a special position.\n";
			}

			std::cin >> row >> col;
			result = board.CanMakeMove(row, col, chosenCard);

		} while (result == 0);

		if (result == 1)
		{
			board.MakeMove(row, col, chosenCard);

		}

		if (board.CheckIsBomb())//aici
		{
			Explosion_Card explosion_card(board.GetSize());
			explosion_card.activateExplosion();
			std::vector<std::pair<char, std::pair<int, int>>> coords;
			std::vector<std::pair<char, std::pair<int, int>>> left_coords;
			std::vector<std::pair<char, std::pair<int, int>>> right_coords;

			coords = explosion_card.AppliedPositions();

			for (const auto& pos : coords)
			{
				char bombType = pos.first;
				int row = pos.second.first;
				int col = pos.second.second;

				int right_r = col;
				int right_c = board.GetSize() - 1 - row;
				int left_r = board.GetSize() - 1 - col;
				int left_c = row;

				right_coords.push_back({ bombType, {right_r, right_c} });
				left_coords.push_back({ bombType, {left_r, left_c} });
			}
			std::cout << "pozitile aplicate pt dreapta: \n";
			for (const auto& pos : right_coords)
			{
				std::cout << pos.first << " " << pos.second.first << " " << pos.second.second << "\n";
			}
			std::cout << "pozitile aplicate pt stanga: \n";
			for (const auto& pos : left_coords)
			{
				std::cout << pos.first << " " << pos.second.first << " " << pos.second.second << "\n";
			}
			std::cout << "pozitile aplicate normal: \n";
			for (const auto& pos : coords)
			{
				std::cout << pos.first << " " << pos.second.first << " " << pos.second.second << "\n";
			}

			std::cout << " alege unde vrei sa pui : ";
			char c;
			std::cin >> c;

			switch (c)
			{
			case 'r':
				for (const auto& pos : right_coords)
				{
					switch (pos.first)
					{
					case 'r':
						std::cout << "Removing card at (" << pos.second.first << ", " << pos.second.second << ").\n";
						RemoveCard(pos.second.first, pos.second.first);
						break;
					case 'u':
						std::cout << "Returning card to player at (" << pos.second.first << ", " << pos.second.second << ").\n";
						ReturnCardToPlayer(pos.second.first, pos.second.second);
						break;
					case 'p':
						std::cout << "Creating pit at (" << pos.second.first << ", " << pos.second.second << ").\n";
						CreatePit(pos.second.first, pos.second.second);
						break;

						break;
					}
				}
				break;

			case 's':

				for (const auto& pos : left_coords)
				{
					switch (pos.first)
					{
					case 'r':
						std::cout << "Removing card at (" << pos.second.first << ", " << pos.second.second << ").\n";
						RemoveCard(pos.second.first, pos.second.first);
						break;
					case 'u':
						std::cout << "Returning card to player at (" << pos.second.first << ", " << pos.second.second << ").\n";
						ReturnCardToPlayer(pos.second.first, pos.second.second);
						break;
					case 'p':
						std::cout << "Creating pit at (" << pos.second.first << ", " << pos.second.second << ").\n";
						CreatePit(pos.second.first, pos.second.second);
						break;

						break;
					}
				}
				break;

			case 'n':
				for (const auto& pos : coords)
				{
					switch (pos.first)
					{
					case 'r':
						std::cout << "Removing card at (" << pos.second.first << ", " << pos.second.second << ").\n";
						RemoveCard(pos.second.first, pos.second.first);
						break;
					case 'u':
						std::cout << "Returning card to player at (" << pos.second.first << ", " << pos.second.second << ").\n";
						ReturnCardToPlayer(pos.second.first, pos.second.second);
						break;
					case 'p':
						std::cout << "Creating pit at (" << pos.second.first << ", " << pos.second.second << ").\n";
						CreatePit(pos.second.first, pos.second.second);
						break;

						break;
					}
				}
				break;

			default:
				break;
			}



		}

		if (board.CheckWinner(chosenCard.getColor())) {
			std::pair<int, int> cords(row, col);
			currentPlayer->setWinnCords(cords);
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

Board Game::getboard()
{
	return board;
}
