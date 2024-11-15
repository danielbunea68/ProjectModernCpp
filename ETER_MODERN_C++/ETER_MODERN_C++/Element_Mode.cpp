
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
	player1.AddCard(Card(5, player1.getColor(), "Eter"));

	player2.AddCard(Card(5, player2.getColor(), "Eter"));

	currentPlayer = &player1;
}

void Element_Mode::PlayGame()
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
    board.UpdateMarked(row, col);  

    auto& boardGrid = board.GetBoard(); 
    while (!boardGrid[row][col].empty())
    {
        boardGrid[row][col].pop();  
    }
	board.UpdateMarked(row, col);  // Mark the position as a pit

	// Now, remove all cards from that position using the getter function to access the internal board
	auto& boardGrid = board.GetBoard();  // Get a reference to the board
	while (!boardGrid[row][col].empty())
	{
		boardGrid[row][col].pop();  // Remove all cards from the stack at that position
	}

	std::cout << "Pit created at position (" << row << ", " << col << "). All cards removed.\n";
}

 
Element_Mode::Element_Mode(Putere putere) : tipPutere(putere) {}

Element_Mode::Putere Element_Mode::GetTipPutere()
{
	return tipPutere;
}

void Element_Mode::ActivatePower() 
{
    switch (tipPutere) 
    {
    case Putere::ExplozieControlata:
        std::cout << "Activating Explozie Controlata: Tabla explodează!" << std::endl;
        ActivateControlledExplosion();
        break;
    case Putere::Distrugere:
        std::cout << "Activating Distrugere: Elimină ultima carte jucată de adversar." << std::endl;
        DestroyLastOpponentCard();
        break;
    case Putere::Flacari:
        std::cout << "Activating Flacari: Întoarce iluzia adversarului și joacă o carte." << std::endl;
        Flacari();
        break;
    case Putere::Lava:
        std::cout << "Activating Lava: Toate cărțile vizibile cu un anumit număr se întorc la proprietari." << std::endl;
		Lava();
        break;
    case Putere::DinCenusa:
        std::cout << "Activating Din Cenusa: Joacă imediat o carte eliminată." << std::endl;
		DinCenusa();
        break;
    case Putere::Scantei:
        std::cout << "Activating Scantei: Joacă o carte acoperită de adversar pe o altă poziție." << std::endl;
		Scantei();
        break;
    case Putere::Viscol:
        std::cout << "Activating Viscol: Întoarce o carte vizibilă a oponentului în mâna sa." << std::endl;
        // Logic for Viscol goes here
        break;
    case Putere::Vijelie:
        std::cout << "Activating Vijelie: Toate cărțile acoperite se întorc la proprietari." << std::endl;
        // Logic for Vijelie goes here
        break;
    case Putere::Uragan:
        std::cout << "Activating Uragan: Shiftează un rând complet ocupat." << std::endl;
        // Logic for Uragan goes here
        break;
    case Putere::Rafala:
        std::cout << "Activating Rafala: Mută o carte vizibilă adiacent unei cărți cu număr mai mic." << std::endl;
        // Logic for Rafala goes here
        break;
    case Putere::Miraj:
        std::cout << "Activating Miraj: Înlocuiește propria iluzie plasată cu o altă iluzie." << std::endl;
        // Logic for Miraj goes here
        break;
    case Putere::Furtuna:
        std::cout << "Activating Furtuna: Elimină din joc un teanc de cărți cu 2 sau mai multe cărți." << std::endl;
        // Logic for Furtuna goes here
        break;
    case Putere::Maree:
        std::cout << "Activating Maree: Interschimbă pozițiile a două teancuri de cărți." << std::endl;
        // Logic for Maree goes here
        break;
    case Putere::Ceata:
        std::cout << "Activating Ceata: Joacă încă o iluzie." << std::endl;
        // Logic for Ceata goes here
        break;
    case Putere::Val:
        std::cout << "Activating Val: Mută un teanc pe o poziție adiacentă goală și joacă o carte pe noua poziție goală." << std::endl;
        // Logic for Val goes here
        break;
    case Putere::VartejDeApa:
        std::cout << "Activating Vartej De Apa: Mută 2 cărți despărțite de un spațiu gol pe acel spațiu." << std::endl;
        // Logic for Vartej De Apa goes here
        break;
    case Putere::Tsunami:
        std::cout << "Activating Tsunami: Blochează un rând pentru adversar în următoarea tură." << std::endl;
        // Logic for Tsunami goes here
        break;
    case Putere::Cascada:
        std::cout << "Activating Cascade: Teancurile de pe un rând cad spre o margine și formează un nou teanc." << std::endl;
        // Logic for Cascade goes here
        break;
    case Putere::Sprijin:
        std::cout << "Activating Sprijin: Valoarea unei cărți proprii 1/2/3 crește cu 1." << std::endl;
        // Logic for Sprijin goes here
        break;
    case Putere::Cutremur:
        std::cout << "Activating Cutremur: Elimină de pe tablă toate cărțile vizibile cu numărul 1." << std::endl;
        // Logic for Cutremur goes here
        break;
    case Putere::Sfaramare:
        std::cout << "Activating Sfaramare: Valoarea unei cărți a adversarului 2/3/4 scade cu 1." << std::endl;
        // Logic for Sfaramare goes here
        break;
    case Putere::Granite:
        std::cout << "Activating Granite: Plasează o carte neutră care definește o graniță." << std::endl;
        // Logic for Granite goes here
        break;
    case Putere::Avalansa:
        std::cout << "Activating Avalansa: Shiftează două teancuri adiacente pe o poziție goală." << std::endl;
        // Logic for Avalansa goes here
        break;
    case Putere::Bolovan:
        std::cout << "Activating Bolovan: Acoperă o iluzie cu o carte fără a o întoarce." << std::endl;
        // Logic for Bolovan goes here
        break;
    default:
        std::cout << "Unknown power!" << std::endl;
        break;
    }
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
	int result = board.CanMakeMove(row, col, chosenCard);
	while (result == 0)
	{
		std::cout << "Enter row and column (0, 1, 2, or 3) to place the card: ";
		std::cin >> row >> col;
		result = board.CanMakeMove(row, col, chosenCard);
	}

	if (result == 1)
	{
		currentPlayer->setLastMove(row, col);
		board.MakeMove(row, col, chosenCard);
		std::cout << currentPlayer->getName() << " placed card with value "
			<< chosenCard.getValue() << " at (" << row << ", " << col << ").\n";
	}
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
				if (!topCard.getIsFaceDown()) {
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
	std::cin >> chosenNumber;

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
	int row, col;
	bool coveredCardFound = false;

	for (int r = 0; r < board.GetSize(); ++r) 
	{
		for (int c = 0; c < board.GetSize(); ++c) 
		{
			if (board.HasCoveredCard(r, c, currentPlayer->getColor())) 
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
		std::cout << "No covered card found.\n";
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
		std::cout << "Failed to place card at the new position.\n";
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

void Element_Mode::ActivateMiraj(int row, int col, int cardIndex) {
    if (!board.IsValidPosition(row, col) || board.IsEmpty(row, col)) {
        std::cout << "Invalid position or no illusion card found.\n";
        return;
    }

    Card topCard = board.TopCard(row, col);

    if (topCard.getIsFaceDown() && topCard.getColor() == currentPlayer->getColor()) {
        if (!currentPlayer->HasCardAtIndex(cardIndex)) {
            std::cout << "Invalid card index in hand for Miraj.\n";
            return;
        }

        Card replacementCard = currentPlayer->PlayCard(cardIndex);
        replacementCard.setFaceDown(true);  // Keep the new card as an illusion

        board.Remove(row, col);
        board.AddCard(row, col, replacementCard);

        std::cout << "Miraj applied: Replaced illusion at (" << row << ", " << col << ") with a new card.\n";
    } else {
        std::cout << "No illusion card found at the specified position.\n";
    }
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