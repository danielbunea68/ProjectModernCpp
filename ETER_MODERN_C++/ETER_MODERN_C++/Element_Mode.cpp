#pragma once
#include "Element_Mode.h"
#include "Explosion_Card.h"

#include "Board.h"

void Element_Mode::SwitchTurn()
{
	if (currentPlayer->getName() == player1.getName())
	{
		currentPlayer = &player2;
	}
	else
	{
		currentPlayer = &player1;
	}

	if (blockedRowForNextTurn != -1) 
	{
		std::cout << "The opponent cannot play on row " << blockedRowForNextTurn << " in this turn.\n";
	}

	blockedRowForNextTurn = -1;
}

std::string Element_Mode::GetPowerName(Putere power)
{
	switch (power) 
	{
	case Putere::ExplozieControlata: return "Explozie Controlata";
	case Putere::Distrugere: return "Distrugere";
	case Putere::Flacari: return "Flacari";
	case Putere::Lava: return "Lava";
	case Putere::DinCenusa: return "Din Cenusa";
	case Putere::Scantei: return "Scantei";
	case Putere::Viscol: return "Viscol";
	case Putere::Vijelie: return "Vijelie";
	case Putere::Uragan: return "Uragan";
	case Putere::Rafala: return "Rafala";
	case Putere::Miraj: return "Miraj";
	case Putere::Furtuna: return "Furtuna";
	case Putere::Maree: return "Maree";
	case Putere::Ceata: return "Ceata";
	case Putere::Val: return "Val";
	case Putere::VartejDeApa: return "Vartej De Apa";
	case Putere::Tsunami: return "Tsunami";
	case Putere::Cascada: return "Cascada";
	case Putere::Sprijin: return "Sprijin";
	case Putere::Cutremur: return "Cutremur";
	case Putere::Sfaramare: return "Sfaramare";
	case Putere::Granite: return "Granite";
	case Putere::Avalansa: return "Avalansa";
	case Putere::Bolovan: return "Bolovan";
	default: return "Unknown";
	}
}

std::string Element_Mode::GetPowerDescription(Putere power)
{
	switch (power)
	{
	case Putere::ExplozieControlata:
		return "Explodes the board in a controlled manner.";
	case Putere::Distrugere:
		return "Destroys the last card played by the opponent.";
	case Putere::Flacari:
		return "Flips the opponent's illusion and lets you play a card.";
	case Putere::Lava:
		return "Returns all visible cards with a specific number to their owners.";
	case Putere::DinCenusa:
		return "Allows you to immediately play an eliminated card.";
	case Putere::Scantei:
		return "Plays a hidden card of the opponent in another position.";
	case Putere::Viscol:
		return "Returns a visible card from the opponent to their hand.";
	case Putere::Vijelie:
		return "Returns all covered cards to their owners.";
	case Putere::Uragan:
		return "Shifts a fully occupied row.";
	case Putere::Rafala:
		return "Moves a visible card adjacent to a card with a smaller number.";
	case Putere::Miraj:
		return "Replaces your placed illusion with another illusion.";
	case Putere::Furtuna:
		return "Removes from the game a stack of cards with 2 or more cards.";
	case Putere::Maree:
		return "Swaps positions of two stacks of cards.";
	case Putere::Ceata:
		return "Plays another illusion.";
	case Putere::Val:
		return "Moves a stack to an adjacent empty position and plays a card on the new empty position.";
	case Putere::VartejDeApa:
		return "Moves two cards separated by an empty space into that space.";
	case Putere::Tsunami:
		return "Blocks a row for the opponent in the next turn.";
	case Putere::Cascada:
		return "Stacks from a row collapse towards an edge and form a new stack.";
	case Putere::Sprijin:
		return "Increases the value of one of your cards (1/2/3) by 1.";
	case Putere::Cutremur:
		return "Removes all visible cards with the value 1 from the table.";
	case Putere::Sfaramare:
		return "Decreases the value of an opponent's card (2/3/4) by 1.";
	case Putere::Granite:
		return "Places a neutral card that defines a boundary.";
	case Putere::Avalansa:
		return "Shifts two adjacent stacks.";
	case Putere::Bolovan:
		return "Covers an illusion without revealing it.";
	default:
		return "Unknown power.";
	}
}

void Element_Mode::InitializePowers()
{
	std::vector<Putere> allPowers = 
	{
		Putere::ExplozieControlata, Putere::Distrugere, Putere::Flacari, Putere::Lava,
		Putere::DinCenusa, Putere::Scantei, Putere::Viscol, Putere::Vijelie, Putere::Uragan,
		Putere::Rafala, Putere::Miraj, Putere::Furtuna, Putere::Maree, Putere::Ceata,
		Putere::Val, Putere::VartejDeApa, Putere::Tsunami, Putere::Cascada, Putere::Sprijin,
		Putere::Cutremur, Putere::Sfaramare, Putere::Granite, Putere::Avalansa, Putere::Bolovan
	};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(allPowers.begin(), allPowers.end(), gen);

	availablePowers = { allPowers[0], allPowers[1] };

	std::cout << "Selected powers for this round:\n";
	for (const auto& putere : availablePowers) 
	{
		std::cout << "- " << GetPowerName(putere) << "\n";
	}
}

bool Element_Mode::CanUsePower(Putere power) 
{
	return std::find(availablePowers.begin(), availablePowers.end(), power) != availablePowers.end() && usedPowers.find(power) == usedPowers.end();
}

void Element_Mode::UsePower(Putere power) 
{
	usedPowers.insert(power);
	std::cout << "Power " << static_cast<int>(power) << " has been used and is no longer available.\n";
}

Element_Mode::Element_Mode()
{
    currentPlayer = NULL;
}

void Element_Mode::InitGame(std::string name1, std::string name2)
{
	player1.setName(name1);
	player2.setName(name2);
	board.SetSize(4);
	std::vector<int> values = { 1, 1, 2,2, 2, 3, 3 ,3, 4 };
	player1.setColor("red");
	player2.setColor("blue");
	for (const auto& value : values) {
		player1.AddCard(Card(value, player1.getColor()));
		player2.AddCard(Card(value, player2.getColor()));
	}
	player1.AddCard(Card(1, player1.getColor(), "Eter"));

	player2.AddCard(Card(1, player2.getColor(), "Eter"));

	currentPlayer = &player1;
}

void Element_Mode::PlayGame()
{
	bool gameOver = false;
	int player1Wins = 0;
	int player2Wins = 0;

	InitializePowers();

	while (!gameOver)
	{
		board.Display();
		currentPlayer->ShowHand();
		bool& currentPlayerUsedAnyPower = (currentPlayer == &player1) ? player1UsedAnyPower : player2UsedAnyPower;

		if (currentPlayerUsedAnyPower)
		{
			std::cout << currentPlayer->getName() << ", you have already used your power and cannot use another.\n";
		}
		else if (!availablePowers.empty())
		{
			char usePower;
			std::cout << currentPlayer->getName() << ", do you want to use your power this turn? y/[n]: ";
			std::cin >> usePower;

			if (usePower == 'y')
			{
				while (true)
				{
					int chosenPowerIndex = -1;
					std::cout << "Choose a power to apply (or enter 0 to exit):\n";
					for (size_t i = 0; i < availablePowers.size(); ++i)
					{
						std::cout << i + 1 << ": " << GetPowerName(availablePowers[i])
							<< "\n - " << GetPowerDescription(availablePowers[i]) << "\n";
					}

					std::cout << "Enter the number of the power you want to use: ";
					std::cin >> chosenPowerIndex;

					if (chosenPowerIndex == 0)
					{
						std::cout << "Exiting power menu.\n";
						break;
					}

					if (chosenPowerIndex >= 1 && chosenPowerIndex <= availablePowers.size())
					{
						Putere selectedPower = availablePowers[chosenPowerIndex - 1];

						if (CanUsePower(selectedPower))
						{
							std::string currentPlayerName1 = currentPlayer->getName();
							ActivatePower(selectedPower);
							UsePower(selectedPower);

							availablePowers.erase(availablePowers.begin() + (chosenPowerIndex - 1));

							currentPlayerUsedAnyPower = true;

							if (availablePowers.empty())
							{
								std::cout << "All powers have been used.\n";
							}

							std::cout << currentPlayerName1 << " has used their power. Turn ends.\n";

							break;
						}
						else
						{
							std::cout << "You cannot use this power right now.\n";
						}
					}
					else
					{
						std::cout << "Invalid power choice! Please try again.\n";
					}
				}
				continue;
			}
		}
		else
		{
			std::cout << "No powers available to use.\n";
		}


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
			currentPlayer->setLastMove(row, col);
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

		if (board.CheckWinner(chosenCard.getColor()))
		{
			std::pair<int, int> cords(row, col);
			currentPlayer->setWinnCords(cords);
			board.Display();
			std::cout << currentPlayer->getName() << " wins this round!\n";

			if (currentPlayer->getName() == player1.getName()) 
				player1Wins++;
			else
				player2Wins++;

			if (player1Wins == 3)
			{
				std::cout << player1.getName() << " wins the game with 3 round wins!\n";
				gameOver = true;
			}
			else if (player2Wins == 3)
			{
				std::cout << player2.getName() << " wins the game with 3 round wins!\n";
				gameOver = true;
			}
			else
			{
				board.Clear();
				InitializePowers();
				player1UsedAnyPower = false;
				player2UsedAnyPower = false;
				SwitchTurn();
			}
			break;
		}
		else if (board.IsDraw())
		{
			board.Display();
			std::cout << "It's a draw!\n";

			if (player1Wins == 3)
			{
				std::cout << player1.getName() << " wins the game with 3 round wins!\n";
				gameOver = true;
			}
			else if (player2Wins == 3)
			{
				std::cout << player2.getName() << " wins the game with 3 round wins!\n";
				gameOver = true;
			}
			else
			{
				board.Clear();
				InitializePowers();
				player1UsedAnyPower = false;
				player2UsedAnyPower = false;
				SwitchTurn();
			}
			break;
		}
		else
		{
			SwitchTurn();
		}
	}
	if(gameOver==true)
		std::cout << "Game over! Thanks for playing.\n";
}

void Element_Mode::ResetGame()
{
	board.Clear();
	player1.ClearCards();
	player2.ClearCards();
	InitGame(player1.getName(), player2.getName());
}

void Element_Mode::RemoveCard(int row, int col)
{
	board.Remove(row, col);
}

void Element_Mode::ReturnCardToPlayer(int row, int col)
{
    if (!board.IsEmpty(row, col))  
    {
        
        Card card = board.TopCard(row, col);
        board.Remove(row, col); 

        if (card.getColor() == currentPlayer->getColor()) {
            currentPlayer->AddCard(card);
            std::cout << "Card returned to " << currentPlayer->getName() << "'s hand.\n";
        }
        else {
            Player* otherPlayer = (currentPlayer == &player1) ? &player2 : &player1;
            otherPlayer->AddCard(card);  
            std::cout << "Card returned to " << otherPlayer->getName() << "'s hand.\n";
        }
    }
    else
    {
        std::cout << "No card to return at position (" << row << ", " << col << ").\n";
    }
}


void Element_Mode::DestroyLastOpponentCard() 
{
	// Identify the opponent
	Player* opponent = (currentPlayer == &player1) ? &player2 : &player1;
	std::pair<int, int> move = opponent->getLastMove();

	int row = move.first;
	int col = move.second;
	// Locate and remove the card from the board if present
	bool cardFound = false;

	Card card1 = board.TopCard(row, col);
	if (card1.getColor() == opponent->getColor())
		board.Remove(row, col);

}

void Element_Mode::CreatePit(int row, int col)
{
	if (!board.IsValidPosition(row, col)) 
	{
		std::cout << "Cannot create pit at (" << row << ", " << col << "). Invalid position.\n";
		return;
	}

	if (board.IsBlockedCell(row, col)) 
	{
		std::cout << "Cannot create pit at (" << row << ", " << col << "). This cell is already a pit.\n";
		return;
	}

	while (!board.IsEmpty(row, col)) 
	{
		board.Remove(row, col);
	}

	board.BlockCell(row, col);

	std::cout << "Pit created at position (" << row << ", " << col << "). All cards removed, and no cards can be placed here.\n";
}


Player* Element_Mode::CurrentTurn()
{
	return currentPlayer;
}

Player* Element_Mode::PreviousTurn()
{
	if (currentPlayer->getName() == player1.getName())
		return &player2;
	else
		return &player1;
}
 
Element_Mode::Element_Mode(Putere putere) : tipPutere(putere) {}

Element_Mode::~Element_Mode()
{
	std::cout << "Element_Mode destructor called.\n";
}

Element_Mode::Element_Mode(const Element_Mode& other) : tipPutere(other.tipPutere), board(other.board), 
player1(other.player1), player2(other.player2), currentPlayer((other.currentPlayer == &other.player1) ? &player1 : &player2), 
blockedRowForNextTurn(other.blockedRowForNextTurn) 
{
	std::cout << "Element_Mode copy constructor called.\n";
}

Element_Mode& Element_Mode::operator=(const Element_Mode& other)
{
	if (this == &other) {
		return *this;
	}

	tipPutere = other.tipPutere;
	board = other.board;
	player1 = other.player1;
	player2 = other.player2;
	currentPlayer = (other.currentPlayer == &other.player1) ? &player1 : &player2;
	blockedRowForNextTurn = other.blockedRowForNextTurn;

	std::cout << "Element_Mode copy assignment operator called.\n";

	return *this;
}

Element_Mode::Element_Mode(Element_Mode&& other) noexcept : tipPutere(std::move(other.tipPutere)), 
board(std::move(other.board)), 
player1(std::move(other.player1)), player2(std::move(other.player2)), 
currentPlayer((other.currentPlayer == &other.player1) ? &player1 : &player2), 
blockedRowForNextTurn(other.blockedRowForNextTurn)
{
	other.currentPlayer = nullptr;

	std::cout << "Element_Mode move constructor called.\n";

}

Element_Mode& Element_Mode::operator=(Element_Mode&& other) noexcept
{
	if (this == &other) {
		return *this;
	}

	tipPutere = std::move(other.tipPutere);
	board = std::move(other.board);
	player1 = std::move(other.player1);
	player2 = std::move(other.player2);
	currentPlayer = (other.currentPlayer == &other.player1) ? &player1 : &player2;
	blockedRowForNextTurn = other.blockedRowForNextTurn;

	other.currentPlayer = nullptr;

	std::cout << "Element_Mode move assignment operator called.\n";

	return *this;
}

Element_Mode::Putere Element_Mode::GetTipPutere()
{
	return tipPutere;
}

void Element_Mode::ActivatePower(Putere power)
{
	if (!CanUsePower(power))
	{
		std::cout << "This power is either unavailable or already used.\n";
		return;
	}

	if (usedPowers.find(power) != usedPowers.end())
	{
		std::cout << "This power has already been used in this match.\n";
		return;
	}

	switch (power)
	{
	case Putere::ExplozieControlata:
		std::cout << "Activating Controlled Explosion: The board explodes!" << std::endl;
		ActivateControlledExplosion();
		break;
	case Putere::Distrugere:
		std::cout << "Activating Destruction: Removes the last card played by the opponent." << std::endl;
		DestroyLastOpponentCard();
		break;
	case Putere::Flacari:
		std::cout << "Activating Flames: Reveals the opponent's illusion and allows you to play a card." << std::endl;
		Flacari();
		break;
	case Putere::Lava:
		std::cout << "Activating Lava: All visible cards with a specific number return to their owners." << std::endl;
		Lava();
		break;
	case Putere::DinCenusa:
		std::cout << "Activating From the Ashes: Immediately play an eliminated card." << std::endl;
		DinCenusa();
		break;
	case Putere::Scantei:
		std::cout << "Activating Sparks: Play a card covered by the opponent in a different position." << std::endl;
		Scantei();
		break;
	case Putere::Viscol:
		std::cout << "Activating Blizzard: Return a visible opponent's card to their hand." << std::endl;
		Viscol();
		break;
	case Putere::Vijelie:
		std::cout << "Activating Storm: All covered cards return to their owners." << std::endl;
		Vijelie();
		break;
	case Putere::Uragan:
		std::cout << "Activating Hurricane: Shift a fully occupied row." << std::endl;

		int row;
		std::cout << "Enter the row number you want to shift (0-indexed): ";
		std::cin >> row;

		try
		{
			Uragan(row);
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Error activating Hurricane: " << ex.what() << std::endl;
		}
		break;
	case Putere::Rafala:
		std::cout << "Activating Gust: Move a visible card adjacent to a smaller-numbered card." << std::endl;

		int row1, col, targetRow, targetCol;
		std::cout << "Enter the row and column of the card to move (0-indexed): ";
		std::cin >> row1 >> col;

		std::cout << "Enter the row and column of the target position (0-indexed): ";
		std::cin >> targetRow >> targetCol;

		try
		{
			ActivateRafala(row1, col, targetRow, targetCol);
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Error activating Gust: " << ex.what() << std::endl;
		}
		break;
	case Putere::Miraj:
		std::cout << "Activating Mirage: Replace your placed illusion with another illusion." << std::endl;

		int cardIndex;

		std::cout << "Enter the index of the card from your hand to replace the illusion: ";
		std::cin >> cardIndex;

		try {
			ActivateMiraj(cardIndex);
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Error activating Mirage: " << ex.what() << std::endl;
		}
		break;
	case Putere::Furtuna:
		std::cout << "Activating Storm: Remove a stack of cards with 2 or more cards from the game." << std::endl;
		ActivateFurtuna();
		break;
	case Putere::Maree:
		std::cout << "Activating Tide: Swap the positions of two stacks of cards." << std::endl;
		SwapStacks();
		break;
	case Putere::Ceata:
		std::cout << "Activating Mist: Play another illusion." << std::endl;
		Ceata();
		break;
	case Putere::Val:
		std::cout << "Activating Wave: Move a stack to an adjacent empty position and play a card on the new empty position." << std::endl;
		Val();
		break;
	case Putere::VartejDeApa:
		std::cout << "Activating Whirlpool: Move 2 cards separated by an empty space onto that space." << std::endl;
		VartejDeApa();
		break;
	case Putere::Tsunami:
		std::cout << "Activating Tsunami: Block a row for the opponent on the next turn." << std::endl;
		ActivateTsunami();
		break;
	case Putere::Cascada:
		std::cout << "Activating Cascade: Stacks on a row fall towards one edge to form a new stack." << std::endl;
		Cascada();
		break;
	case Putere::Sprijin:
		std::cout << "Activating Support: The value of one of your cards (1/2/3) increases by 1." << std::endl;
		Sprijin();
		break;
	case Putere::Cutremur:
		std::cout << "Activating Earthquake: Remove all visible cards with the number 1 from the board." << std::endl;
		Cutremur();
		break;
	case Putere::Sfaramare:
		std::cout << "Activating Shatter: The value of an opponent's card (2/3/4) decreases by 1." << std::endl;
		Sfaramare();
		break;
	case Putere::Granite:
		std::cout << "Activating Granite: Place a neutral card that defines a boundary." << std::endl;
		Granita();
		break;
	case Putere::Avalansa:
		std::cout << "Activated: Avalanche - Shifts two adjacent stacks." << std::endl;

		int row3, col3, row4, col4;
		std::cout << "Enter the coordinates of the first stack (row and column 0-indexed): ";
		std::cin >> row3 >> col3;

		std::cout << "Enter the coordinates of the second stack (row and column 0-indexed): ";
		std::cin >> row4 >> col4;

		try
		{
			Avalansa(row3, col3, row4, col4);
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Error activating Avalanche: " << ex.what() << std::endl;
		}
		break;
	case Putere::Bolovan:
		std::cout << "Activated: Boulder - Covers an illusion without revealing it." << std::endl;
		int row5, col5, cardIndex1;
		std::cout << "Enter the coordinates of the stack (row and column 0-indexed): ";
		std::cin >> row5 >> col5;

		std::cout << "Enter the index of the card in the stack (0-indexed): ";
		std::cin >> cardIndex1;

		try
		{
			Bolovan(row5, col5, cardIndex1);
		}
		catch (const std::exception& ex)
		{
			std::cerr << "Error activating Boulder: " << ex.what() << std::endl;
		}
		break;
	default:
		std::cout << "Unknown power!" << std::endl;
		break;
	}

	usedPowers.insert(tipPutere);

	auto it = std::find(availablePowers.begin(), availablePowers.end(), tipPutere);
	if (it != availablePowers.end())
	{
		availablePowers.erase(it);
	}

	SwitchTurn();

}

void Element_Mode::ActivateControlledExplosion()
{
	Explosion_Card explosionCard(4);
	explosionCard.activateExplosion();
}

void Element_Mode::Flacari()
{
	Player* opponent = (currentPlayer == &player1) ? &player2 : &player1;
	bool cardRevealed = false;

	for (int row = 0; row < board.GetSize(); ++row)
	{
		for (int col = 0; col < board.GetSize(); ++col)
		{
			if (!board.IsEmpty(row, col))
			{
				Card topCard = board.TopCard(row, col);

				if (topCard.getColor() == opponent->getColor() && topCard.getIsFaceDown())
				{
					topCard.setFaceDown(false);
					board.UpdateCard(row, col, topCard);
					std::cout << "Flăcări activated: Card at (" << row << ", " << col
						<< ") belonging to " << opponent->getName()
						<< " is now face-up.\n";
					cardRevealed = true;
					break;
				}
			}
		}
		if (cardRevealed) break;
	}

	if (!cardRevealed)
	{
		std::cout << "No face-down cards belonging to the opponent were found.\n";
	}

	currentPlayer->ShowHand();
	int cardIndex = -1;
	while (!currentPlayer->HasCardAtIndex(cardIndex))
	{
		std::cout << currentPlayer->getName() << ", choose a card index to play: ";
		std::cin >> cardIndex;
	}
	Card chosenCard = currentPlayer->PlayCard(cardIndex);

	int row = -1, col = -1;
	do
	{
		std::cout << "Enter row and column (0 to " << board.GetSize() - 1 << ") to place the card: ";
		std::cin >> row >> col;

		if (!board.IsEmpty(row, col)) 
		{
			std::cout << "Position (" << row << ", " << col << ") is not empty! Try again.\n";
		}
	} while (!board.IsEmpty(row, col)); 

	currentPlayer->setLastMove(row, col);
	board.MakeMove(row, col, chosenCard); 

	std::cout << currentPlayer->getName() << " placed card with value "<< chosenCard.getValue() << " at (" << row << ", " << col << ").\n";
}

void Element_Mode::Lava()
{
	std::unordered_map<int, int> visibleCardCount;

	for (int row = 0; row < board.GetSize(); ++row)
	{
		for (int col = 0; col < board.GetSize(); ++col)
		{
			if (!board.IsEmpty(row, col))
			{
				Card topCard = board.TopCard(row, col);
				if (!topCard.getIsFaceDown()) 
				{
					visibleCardCount[topCard.getValue()]++;
				}
			}
		}
	}

	std::vector<int> eligibleNumbers;
	for (const auto& pair : visibleCardCount)
	{
		if (pair.second >= 2)
		{
			eligibleNumbers.push_back(pair.first);
		}
	}

	if (eligibleNumbers.empty())
	{
		std::cout << "No number has at least two visible cards.\n";
		return;
	}

	std::cout << "Choose a number from the following visible numbers with at least two cards:\n";
	for (int number : eligibleNumbers)
	{
		std::cout << number << " ";
	}
	std::cout << "\nYour choice: ";

	int chosenNumber;
	while (true)
	{
		std::cin >> chosenNumber;

		if (std::cin.fail() || std::find(eligibleNumbers.begin(), eligibleNumbers.end(), chosenNumber) == eligibleNumbers.end())
		{
			std::cin.clear(); 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid choice. Please choose a number from the list: ";
		}
		else
		{
			break;
		}
	}

	for (int row = 0; row < board.GetSize(); ++row)
	{
		for (int col = 0; col < board.GetSize(); ++col)
		{
			if (!board.IsEmpty(row, col))
			{
				Card topCard = board.TopCard(row, col);
				if (!topCard.getIsFaceDown() && topCard.getValue() == chosenNumber)
				{
					std::cout << "Returning card with value " << chosenNumber
						<< " at position (" << row << ", " << col << ").\n";
					ReturnCardToPlayer(row, col);
				}
			}
		}
	}
}


void Element_Mode::DinCenusa()
{
	const auto& removedCards = currentPlayer->GetRemovedCards();

	if (removedCards.empty()) {
		std::cout << "No removed cards available to play.\n";
		return;
	}

	
	std::cout << "Removed cards:\n";
	for (size_t i = 0; i < removedCards.size(); ++i) 
	{
		const Card& card = removedCards[i];
		std::cout << i << ": Value " << card.getValue()<< ", Color " << card.getColor()<<"\n";
	}

	
	int cardIndex = -1;
	while (cardIndex < 0 || cardIndex >= static_cast<int>(removedCards.size())) 
	{
		std::cout << "Choose a card index to play: ";
		std::cin >> cardIndex;
	}

	Card chosenCard = removedCards[cardIndex];
	currentPlayer->RemoveFromRemovedCards(chosenCard);

	
	int row = -1, col = -1;
	int result = board.CanMakeMove(row, col, chosenCard);
	while (result == 0) 
	{
		std::cout << "Enter row and column (0-" << (board.GetSize() - 1) << ") to place the card: ";
		std::cin >> row >> col;
		result = board.CanMakeMove(row, col, chosenCard);
	}

	if (result == 1) 
	{
		currentPlayer->setLastMove(row, col);
		board.MakeMove(row, col, chosenCard);
		std::cout << "Card played successfully!\n";
	}
	else 
	{
		std::cout << "Unable to play the card.\n";
	}
}


void Element_Mode::Scantei()
{
	int row = -1, col = -1;
	bool coveredCardFound = false;

	for (int r = 0; r < board.GetSize(); ++r)
	{
		for (int c = 0; c < board.GetSize(); ++c)
		{
			if (board.HasCoveredCard(r, c, currentPlayer->getColor()) && board.IsCoveredByOpponent(r, c, currentPlayer->getColor()))
			{
				row = r;
				col = c;
				coveredCardFound = true;
				break;
			}
		}
		if (coveredCardFound)
			break;
	}

	if (!coveredCardFound)
	{
		std::cout << "No covered card found that is owned by you and covered by the opponent.\n";
		return;
	}

	std::cout << "Covered card found at position (" << row << ", " << col << ").\n";

	int newRow, newCol;
	std::cout << "Enter new row and column to place the card: ";
	std::cin >> newRow >> newCol;

	while (!board.IsValidPosition(newRow, newCol) || !board.IsEmpty(newRow, newCol))
	{
		std::cout << "Invalid position. Enter new row and column: ";
		std::cin >> newRow >> newCol;
	}

	Card card = board.TopCard(row, col);
	board.Remove(row, col);

	if (board.MakeMove(newRow, newCol, card))
	{
		std::cout << "Card moved to new position (" << newRow << ", " << newCol << ").\n";
	}
	else
	{
		std::cout << "Failed to place card at the new position. Returning the card to the original position.\n";
		board.MakeMove(row, col, card);
	}
}


void Element_Mode::Viscol()
{
	Player* opponent = (currentPlayer == &player1) ? &player2 : &player1;
	std::vector<std::pair<int, int>> visibleCards;

	for (int row = 0; row < board.GetSize(); ++row)
	{
		for (int col = 0; col < board.GetSize(); ++col)
		{
			if (!board.IsEmpty(row, col))
			{
				Card topCard = board.TopCard(row, col);
				if (topCard.getColor() == opponent->getColor() && !topCard.getIsFaceDown())
				{
					visibleCards.emplace_back(row, col);
				}
			}
		}
	}

	if (visibleCards.empty())
	{
		std::cout << "No visible cards belonging to the opponent are available to return.\n";
		return;
	}

	std::cout << "Choose a card to return to the opponent's hand:\n";
	for (size_t i = 0; i < visibleCards.size(); ++i)
	{
		int row = visibleCards[i].first;
		int col = visibleCards[i].second;
		Card card = board.TopCard(row, col);
		std::cout << i << ": Card at (" << row << ", " << col << ") - Value: "
			<< card.getValue() << ", Color: " << card.getColor() << "\n";
	}

	int choice = -1;
	while (choice < 0 || choice >= static_cast<int>(visibleCards.size()))
	{
		std::cout << "Enter the index of the card to return: ";
		std::cin >> choice;
	}

	int row = visibleCards[choice].first;
	int col = visibleCards[choice].second;
	ReturnCardToPlayer(row, col);
	std::cout << "Card at (" << row << ", " << col << ") returned to the opponent's hand.\n";
}

void Element_Mode::Vijelie()
{
	for (int row = 0; row < board.GetSize(); row++)
	{
		for (int col = 0; col < board.GetSize(); col++)
		{
			if (!board.IsEmpty(row, col) && board.GetStackSize(row, col) > 1)
			{
				while (board.GetStackSize(row, col) > 1)
				{
					Card card = board.TopCard(row, col);
					board.Remove(row, col);

					if (card.getColor() == player1.getColor())
					{
						player1.AddCard(card);
						std::cout << "Card returned to " << player1.getName() << "'s hand.\n";
					}
					else if (card.getColor() == player2.getColor())
					{
						player2.AddCard(card);
						std::cout << "Card returned to " << player2.getName() << "'s hand.\n";
					}
				}
			}
		}
	}
}

void Element_Mode::ActivateRafala(int row, int col, int targetRow, int targetCol) {
    if (!board.IsValidPosition(row, col) || !board.IsValidPosition(targetRow, targetCol)) {
        std::cout << "Invalid positions for Rafala.\n";
        return;
    }

    if (board.IsEmpty(row, col)) {
        std::cout << "No card at the selected position to move.\n";
        return;
    }

    if (board.IsEmpty(targetRow, targetCol)) {
        std::cout << "Target position is empty. Rafala cannot be applied.\n";
        return;
    }

    Card sourceCard = board.TopCard(row, col);
    Card targetCard = board.TopCard(targetRow, targetCol);

    if (sourceCard.getValue() < targetCard.getValue() && !targetCard.getIsFaceDown()) {
        board.Remove(row, col);
        board.AddCard(targetRow, targetCol, sourceCard);
        std::cout << "Rafala applied: Moved card " << sourceCard.getValue() << " to (" << targetRow << ", " << targetCol << ").\n";
    } else {
        std::cout << "Target card must have a higher value, and it must be visible for Rafala to be applied.\n";
    }
}

void Element_Mode::ActivateMiraj(int cardIndex) 
{
	if (!currentPlayer->HasCardAtIndex(cardIndex)) 
	{
		std::cout << "Invalid card index in hand for Miraj.\n";
		return;
	}

	Card replacementCard = currentPlayer->PlayCard(cardIndex);
	replacementCard.setFaceDown(true);

	int row = -1, col = -1;

	do 
	{
		std::cout << "Enter the row (0 to " << board.GetSize() - 1 << ") to place the illusion: ";
		std::cin >> row;
		std::cout << "Enter the column (0 to " << board.GetSize() - 1 << ") to place the illusion: ";
		std::cin >> col;
	} while (!board.IsValidPosition(row, col) || !board.IsEmpty(row, col)); 

	board.AddCard(row, col, replacementCard);
	std::cout << "Miraj applied: Placed an illusion at (" << row << ", " << col << ").\n";
}

void Element_Mode::ActivateFurtuna() {
    for (int row = 0; row < board.GetSize(); ++row) {
        for (int col = 0; col < board.GetSize(); ++col) {
            if (!board.IsEmpty(row, col)) {
                std::stack<Card>& stack = board.GetBoard()[row][col];
                if (stack.size() >= 2) {
                    std::cout << "Furtuna applied: Removed stack at (" << row << ", " << col << ").\n";
                    while (!stack.empty()) {
                        stack.pop();
                    }
                }
            }
        }
    }
}

void Element_Mode::Uragan(int row) {
    if (row < 0 || row >= board.GetSize()) {
        std::cout << "Invalid row for Uragan.\n";
        return;
    }

    std::vector<Card> rowCards;
    for (int col = 0; col < board.GetSize(); ++col) {
        if (!board.IsEmpty(row, col)) {
            while (!board.GetBoard()[row][col].empty()) {
                rowCards.push_back(board.GetBoard()[row][col].top());
                board.GetBoard()[row][col].pop();
            }
        }
    }

    if (rowCards.empty()) {
        std::cout << "No cards to move in row " << row << ".\n";
        return;
    }

    int newRow;
    std::cout << "Enter the new row to move the cards: ";
    std::cin >> newRow;

    if (newRow < 0 || newRow >= board.GetSize() || newRow == row) {
        std::cout << "Invalid row or same row for Uragan.\n";
        return;
    }

    for (int col = 0; col < board.GetSize() && !rowCards.empty(); ++col) {
        if (board.IsEmpty(newRow, col)) {
            board.AddCard(newRow, col, rowCards.back());
            rowCards.pop_back();
        }
    }

    std::cout << "Uragan activated: Moved cards from row " << row << " to row " << newRow << ".\n";
}

void Element_Mode::SwapStacks() {
	int row1, col1, row2, col2;

	std::cout << "Enter the row and column of the first stack to swap: ";
	std::cin >> row1 >> col1;
	std::cout << "Enter the row and column of the second stack to swap: ";
	std::cin >> row2 >> col2;

	board.SwapStacks(row1, col1, row2, col2);
}

void Element_Mode::Ceata() 
{

	for (int row = 0; row < board.GetSize(); ++row) 
	{
		for (int col = 0; col < board.GetSize(); ++col) 
		{
			if (board.HasCoveredCard(row, col, currentPlayer->getColor())) 
			{
				std::cout << currentPlayer->getName() << " already has an active illusion on the board!\n";
				return;
			}
		}
	}

	currentPlayer->ShowHand();

	int cardIndex = -1;
	while (!currentPlayer->HasCardAtIndex(cardIndex)) {
		std::cout << currentPlayer->getName() << ", choose a card index to play as an illusion: ";
		std::cin >> cardIndex;
	}

	Card chosenCard = currentPlayer->PlayCard(cardIndex);
	chosenCard.setFaceDown(true);

	int row = -1, col = -1;
	while (true) 
	{
		std::cout << "Enter row and column (0 - " << board.GetSize() - 1 << ") to place the illusion: ";
		std::cin >> row >> col;

		if (row < 0 || row >= board.GetSize() || col < 0 || col >= board.GetSize()) 
		{
			std::cout << "Invalid position! Row and column must be within the board boundaries.\n";
			continue;
		}

		if (board.CanMakeMove(row, col, chosenCard) == 1) 
		{
			break; 
		}
		else 
		{
			std::cout << "Invalid move! That position is occupied or not valid for an illusion.\n";
		}
	}

	currentPlayer->setLastMove(row, col);
	board.MakeMove(row, col, chosenCard);

	std::cout << currentPlayer->getName() << " played an illusion at position (" << row << ", " << col << ").\n";
}


void Element_Mode::Val() 
{
	board.Display();

	std::cout << currentPlayer->getName() << ", choose the source row and column: ";
	int srcRow, srcCol;
	std::cin >> srcRow >> srcCol;

	if (!board.IsValidPosition(srcRow, srcCol) || board.IsEmpty(srcRow, srcCol)) 
	{
		std::cout << "Invalid source position. Try again.\n";
		return;
	}

	std::cout << "Choose the destination row and column: ";
	int destRow, destCol;
	std::cin >> destRow >> destCol;

	if (!board.IsValidPosition(destRow, destCol) || !board.IsEmpty(destRow, destCol)) 
	{
		std::cout << "Invalid destination position. Try again.\n";
		return;
	}

	if (!board.AreAdjacent(srcRow, srcCol, destRow, destCol)) 
	{
		std::cout << "The destination position must be adjacent to the source position. Try again.\n";
		return;
	}

	board.MoveStack(srcRow, srcCol, destRow, destCol);
	std::cout << "Moved stack from (" << srcRow << ", " << srcCol << ") to (" << destRow << ", " << destCol << ").\n";

	currentPlayer->ShowHand();
	std::cout << "Choose a card index to play on the new empty position: ";
	int cardIndex;
	std::cin >> cardIndex;

	if (!currentPlayer->HasCardAtIndex(cardIndex)) 
	{
		std::cout << "Invalid card index. Try again.\n";
		return;
	}

	Card cardToPlay = currentPlayer->PlayCard(cardIndex);
	if (board.CanMakeMove(srcRow, srcCol, cardToPlay)) 
	{
		board.MakeMove(srcRow, srcCol, cardToPlay);
		std::cout << "Played card on the new empty position at (" << srcRow << ", " << srcCol << ").\n";
	}
	else 
	{
		std::cout << "Cannot place the card on the new empty position. Returning card to your hand.\n";
		currentPlayer->AddCard(cardToPlay);
	}
}

void Element_Mode::VartejDeApa()
{
	int row, col1, col2;
	std::cout << "Enter the row number (0, 1, 2, or 3): ";
	std::cin >> row;

	std::cout << "Enter the column number for the first card: ";
	std::cin >> col1;

	std::cout << "Enter the column number for the second card: ";
	std::cin >> col2;

	if (col1 == col2 || abs(col1 - col2) != 2) 
	{
		std::cout << "Invalid positions. The two cards must be separated by exactly one empty space.\n";
		return;
	}

	int emptyCol = (col1 + col2) / 2;

	if (board.IsEmpty(row, col1) || board.IsEmpty(row, col2) || !board.IsEmpty(row, emptyCol)) 
	{
		std::cout << "Invalid move. Make sure the chosen positions meet the criteria.\n";
		return;
	}

	Card card1 = board.TopCard(row, col1);
	Card card2 = board.TopCard(row, col2);

	Card topCard, bottomCard;
	if (card1.getValue() > card2.getValue()) 
	{
		topCard = card1;
		bottomCard = card2;
	}
	else if (card1.getValue() < card2.getValue()) 
	{
		topCard = card2;
		bottomCard = card1;
	}
	else 
	{
		int choice = 0;
		while (choice != 1 && choice != 2) 
		{
			std::cout << "Both cards have the same value.\n";
			std::cout << "Choose which card goes on top (1 for card at (" << row << "," << col1
				<< "), 2 for card at (" << row << "," << col2 << ")): ";
			std::cin >> choice;

			if (choice == 1) 
			{
				topCard = card1;
				bottomCard = card2;
			}
			else if (choice == 2) 
			{
				topCard = card2;
				bottomCard = card1;
			}
			else 
			{
				std::cout << "Invalid choice. Please choose 1 or 2.\n";
			}
		}
	}

	board.Remove(row, col1);
	board.Remove(row, col2);
	board.MakeMove(row, emptyCol, bottomCard);
	board.MakeMove(row, emptyCol, topCard);

	std::cout << "Cards moved to position (" << row << "," << emptyCol << ").\n";
}

void Element_Mode::ActivateTsunami() 
{
	std::cout << "Activating Tsunami: Select a row to block for the opponent's next turn.\n";

	std::vector<int> validRows;
	for (int row = 0; row < board.GetSize(); ++row) {
		for (int col = 0; col < board.GetSize(); ++col) {
			if (board.IsEmpty(row, col)) {
				validRows.push_back(row);
				break;
			}
		}
	}

	if (validRows.empty()) {
		std::cout << "No valid rows to block. Tsunami cannot be activated.\n";
		return;
	}

	std::cout << "Available rows to block: ";
	for (size_t i = 0; i < validRows.size(); ++i) {
		std::cout << validRows[i];
		if (i < validRows.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << ".\n";

	int chosenRow = -1;
	while (std::find(validRows.begin(), validRows.end(), chosenRow) == validRows.end()) {
		std::cout << "Enter the row number to block: ";
		std::cin >> chosenRow;

		if (std::find(validRows.begin(), validRows.end(), chosenRow) == validRows.end()) {
			std::cout << "Invalid row. Please select a row with empty spaces.\n";
		}
	}

	blockedRowForNextTurn = chosenRow;
	std::cout << "Row " << chosenRow << " has been blocked for the opponent's next turn.\n";
}


void Element_Mode::Cutremur()
{
	int boardSize = board.GetSize();
	for (int row = 0; row < boardSize; ++row)
	{
		for (int col = 0; col < boardSize; ++col)
		{
			if (!board.IsEmpty(row, col))
			{
				Card card = board.TopCard(row, col);
				if (card.getValue() == 1 && !card.getIsFaceDown())
				{
					std::cout << "Removing card with value 1 at (" << row << ", " << col << ").\n";
					board.Remove(row, col);
				}
			}
		}
	}
}

void Element_Mode::Cascada()
{
    board.Display();

    int row;
    std::cout << currentPlayer->getName() << ", select the row (0-" << board.GetSize() - 1 << ") for the cascade: ";
    std::cin >> row;

    if (row < 0 || row >= board.GetSize()) {
        std::cout << "Invalid row selected. Try again.\n";
        return;
    }

    char direction;
    std::cout << "Choose the direction for the cascade (l for left, r for right): ";
    std::cin >> direction;

    if (direction != 'l' && direction != 'r') {
        std::cout << "Invalid direction. Choose 'l' for left or 'r' for right.\n";
        return;
    }

    std::stack<Card> cascadeStack;
    for (int col = 0; col < board.GetSize(); ++col) {
        while (!board.IsEmpty(row, col)) {
            cascadeStack.push(board.TopCard(row, col));
            board.Remove(row, col);
        }
    }

    int targetCol = (direction == 'l') ? 0 : board.GetSize() - 1;

    while (!cascadeStack.empty()) {
        board.AddCard(row, targetCol, cascadeStack.top());
        cascadeStack.pop();
    }

    std::cout << "Cascada completed on row " << row << " toward " << (direction == 'l' ? "left" : "right") << ".\n";
    board.Display();
}

void Element_Mode::Sprijin()
{
    std::vector<std::pair<int, int>> ownCards;

    for (int row = 0; row < board.GetSize(); ++row) {
        for (int col = 0; col < board.GetSize(); ++col) {
            if (!board.IsEmpty(row, col)) {
                const Card& topCard = board.TopCard(row, col); // Use const reference here
                if (topCard.getColor() == currentPlayer->getColor() && !topCard.getIsFaceDown() &&
                    (topCard.getValue() == 1 || topCard.getValue() == 2 || topCard.getValue() == 3)) {
                    ownCards.emplace_back(row, col);
                }
            }
        }
    }

    if (ownCards.empty()) {
        std::cout << "No eligible cards to increase the value of.\n";
        return;
    }

    std::cout << "Eligible cards for Sprijin:\n";
    for (size_t i = 0; i < ownCards.size(); ++i) {
        int row = ownCards[i].first;
        int col = ownCards[i].second;
        const Card& card = board.TopCard(row, col);
        std::cout << i << ": Card at (" << row << ", " << col << ") - Value: "
                  << card.getValue() << ", Color: " << card.getColor() << "\n";
    }

    int choice = -1;
    while (choice < 0 || choice >= static_cast<int>(ownCards.size())) {
        std::cout << "Enter the index of the card to increase its value: ";
        std::cin >> choice;
    }

    int chosenRow = ownCards[choice].first;
    int chosenCol = ownCards[choice].second;

    Card updatedCard = board.TopCard(chosenRow, chosenCol); // Get a copy of the card
    updatedCard.setValue(updatedCard.getValue() + 1); // Modify the copy
    board.UpdateCard(chosenRow, chosenCol, updatedCard); // Update the card on the board

    std::cout << "Sprijin applied: Card at (" << chosenRow << ", " << chosenCol
              << ") now has a value of " << updatedCard.getValue() << ".\n";
}

void Element_Mode::Sfaramare()
{
    Player* opponent = (currentPlayer == &player1) ? &player2 : &player1;

    std::vector<std::pair<int, int>> eligibleCards;
    for (int row = 0; row < board.GetSize(); ++row) {
        for (int col = 0; col < board.GetSize(); ++col) {
            if (!board.IsEmpty(row, col)) {
                Card topCard = board.TopCard(row, col);
                if (topCard.getColor() == opponent->getColor() &&
                    !topCard.getIsFaceDown() &&
                    (topCard.getValue() == 2 || topCard.getValue() == 3 || topCard.getValue() == 4))
                {
                    eligibleCards.emplace_back(row, col);
                }
            }
        }
    }

    if (eligibleCards.empty()) {
        std::cout << "No eligible cards belonging to the opponent are available for Sfaramare.\n";
        return;
    }

    std::cout << "Eligible opponent cards for Sfaramare:\n";
    for (size_t i = 0; i < eligibleCards.size(); ++i) {
        int row = eligibleCards[i].first;
        int col = eligibleCards[i].second;
        Card card = board.TopCard(row, col);
        std::cout << i << ": Card at (" << row << ", " << col << ") - Value: "
                  << card.getValue() << ", Color: " << card.getColor() << "\n";
    }

    int choice = -1;
    while (choice < 0 || choice >= static_cast<int>(eligibleCards.size())) {
        std::cout << "Enter the index of the card to reduce its value: ";
        std::cin >> choice;
    }

    int chosenRow = eligibleCards[choice].first;
    int chosenCol = eligibleCards[choice].second;

    Card card = board.TopCard(chosenRow, chosenCol);
    card.setValue(card.getValue() - 1);
    board.UpdateCard(chosenRow, chosenCol, card);

    std::cout << "Sfaramare applied: Card at (" << chosenRow << ", " << chosenCol
              << ") now has a value of " << card.getValue() << ".\n";
}

void Element_Mode::Granita()
{
	Card neutralCard(0, "neutral");
	int row = -1, col = -1;

	std::cout << "Choose a position to place the neutral card to define a boundary.\n";
	do
	{
		std::cout << "Enter the row and column (0 to " << board.GetSize() - 1 << "): ";
		std::cin >> row >> col;

		if (!board.IsEmpty(row, col))
		{
			std::cout << "Position (" << row << ", " << col << ") is not empty! Try again.\n";
		}
	} while (!board.IsEmpty(row, col));

	board.MakeMove(row, col, neutralCard);
	std::cout << "Neutral card placed at (" << row << ", " << col << ").\n";

	int cardIndex = -1;
	while (!currentPlayer->HasCardAtIndex(cardIndex))
	{
		std::cout << currentPlayer->getName() << ", choose a card index to play: ";
		std::cin >> cardIndex;
	}

	Card chosenCard = currentPlayer->PlayCard(cardIndex);

	int playRow, playCol;
	do
	{
		std::cout << "Enter the row and column to place the card (0 to " << board.GetSize() - 1 << "): ";
		std::cin >> playRow >> playCol;

		if (!board.IsEmpty(playRow, playCol))
		{
			std::cout << "Position (" << playRow << ", " << playCol << ") is not empty! Try again.\n";
		}
	} while (!board.IsEmpty(playRow, playCol));

	board.MakeMove(playRow, playCol, chosenCard);
	std::cout << "Card placed by " << currentPlayer->getName() << " at (" << playRow << ", " << playCol << ").\n";
}


void Element_Mode::Avalansa(int row1, int col1, int row2, int col2)
{
	if (!((row1 == row2 && abs(col1 - col2) == 1) || (col1 == col2 && abs(row1 - row2) == 1))) {
		std::cout << "Teancurile nu sunt adiacente. Alegerea este invalidă.\n";
		return;
	}

	if (board.IsEmpty(row1, col1) || board.IsEmpty(row2, col2)) {
		std::cout << "Una sau ambele poziții selectate sunt goale. Alegerea este invalidă.\n";
		return;
	}

	int shiftRow1 = row1, shiftCol1 = col1;
	int shiftRow2 = row2, shiftCol2 = col2;

	if (row1 == row2) {
		if (board.IsEmpty(row1, col1 - 1)) {
			shiftCol1 = col1 - 1;
		}
		else if (board.IsEmpty(row1, col1 + 1)) {
			shiftCol1 = col1 + 1;
		}

		if (board.IsEmpty(row2, col2 - 1)) {
			shiftCol2 = col2 - 1;
		}
		else if (board.IsEmpty(row2, col2 + 1)) {
			shiftCol2 = col2 + 1;
		}
	}
	else {
		if (board.IsEmpty(row1 - 1, col1)) {
			shiftRow1 = row1 - 1;
		}
		else if (board.IsEmpty(row1 + 1, col1)) {
			shiftRow1 = row1 + 1;
		}

		if (board.IsEmpty(row2 - 1, col2)) {
			shiftRow2 = row2 - 1;
		}
		else if (board.IsEmpty(row2 + 1, col2)) {
			shiftRow2 = row2 + 1;
		}
	}

	if ((shiftRow1 != row1 || shiftCol1 != col1) && board.IsEmpty(shiftRow1, shiftCol1)) {
		board.MoveStack(row1, col1, shiftRow1, shiftCol1);
		std::cout << "Teancul de la (" << row1 << ", " << col1 << ") a fost mutat la (" << shiftRow1 << ", " << shiftCol1 << ").\n";
	}
	else {
		std::cout << "Teancul de la (" << row1 << ", " << col1 << ") nu poate fi mutat.\n";
	}

	if ((shiftRow2 != row2 || shiftCol2 != col2) && board.IsEmpty(shiftRow2, shiftCol2)) {
		board.MoveStack(row2, col2, shiftRow2, shiftCol2);
		std::cout << "Teancul de la (" << row2 << ", " << col2 << ") a fost mutat la (" << shiftRow2 << ", " << shiftCol2 << ").\n";
	}
	else {
		std::cout << "Teancul de la (" << row2 << ", " << col2 << ") nu poate fi mutat.\n";
	}
}

void Element_Mode::Bolovan(int row, int col, int cardIndex)
{
	if (!board.IsFaceDown(row, col))
	{
		std::cout << "Poziția (" << row << ", " << col << ") nu conține o iluzie.\n";
		return;
	}

	while (cardIndex < 0 || cardIndex >= currentPlayer->getCards().size())
	{
		std::cout << currentPlayer->getName() << ", alegi un index de card valid: ";
		std::cin >> cardIndex;
	}

	Card cardToCover = currentPlayer->PlayCard(cardIndex);

	cardToCover.setFaceDown(true);

	board.AddCard(row, col, cardToCover);

	std::cout << "Iluzia de la poziția (" << row << ", " << col << ") a fost acoperită cu o carte.\n";
}
