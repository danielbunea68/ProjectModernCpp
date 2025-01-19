#include "Wizard_Mode.h"
#include "Board.h"
#include "IGame.h"
#include "Explosion_Card.h"
#include <queue>
#include <iostream>

Board& Wizard_Mode::GetBoard()
{
	return board;
}

void Wizard_Mode::removeOpponentCard(int row, int col) {
	if (!board.IsValidPosition(row, col) || board.IsEmpty(row, col) || board.TopCard(row, col).getColor() == currentPlayer->getColor()) {
		std::cout << "Cannot remove card at (" << row << ", " << col << "). Invalid position or not an opponent's card.\n";
		return;
	}

	board.Remove(row, col);
	std::cout << "Removed opponent's card at (" << row << ", " << col << ").\n";
}


void Wizard_Mode::removeRow(int row) {
	if (board.GetSize() > row) {
		bool hasPlayerCard = false;
		for (int col = 0; col < board.GetSize(); ++col) {
			if (!board.IsEmpty(row, col) && board.TopCard(row, col).getColor() == currentPlayer->getColor()) {
				hasPlayerCard = true;
				break;
			}
		}
		if (hasPlayerCard) {
			for (int col = 0; col < board.GetSize(); ++col) {
				while (!board.IsEmpty(row, col)) {
					RemoveCard(row, col);
				}
			}
			std::cout << "Row " << row << " removed.\n";
		}
	}
}


void Wizard_Mode::coverOpponentCard(int row, int col) {
	if (!board.IsValidPosition(row, col) || board.IsEmpty(row, col) || board.TopCard(row, col).getColor() == currentPlayer->getColor()) {
		std::cout << "Cannot cover card at (" << row << ", " << col << "). Invalid position or not an opponent's card.\n";
		return;
	}

	currentPlayer->ShowHand();
	int cardIndex = -1;
	std::cout << "Choose a lower card from hand to cover opponent's card: ";
	while (!currentPlayer->HasCardAtIndex(cardIndex)) {
		std::cin >> cardIndex;
	}

	Card chosenCard = currentPlayer->PlayCard(cardIndex);
	if (chosenCard.getValue() < board.TopCard(row, col).getValue()) {
		board.AddCard(row, col, chosenCard);
		std::cout << "Covered opponent's card with " << chosenCard.getValue() << ".\n";
	}
	else {
		std::cout << "Cannot cover with card of equal or higher value.\n";
		currentPlayer->AddCard(chosenCard);
	}
}


void Wizard_Mode::createPit(int row, int col)
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

	auto& boardGrid = board.GetBoard();
	while (!board.IsEmpty(row, col))
	{
		boardGrid[row][col].pop();
	}

	board.BlockCell(row, col);

	std::cout << "Pit created at (" << row << ", " << col << "). All cards removed, and no cards can be placed here.\n";
}


void Wizard_Mode::moveOwnStack(int fromRow, int fromCol, int toRow, int toCol)
{
	if (!board.IsValidPosition(fromRow, fromCol))
	{
		std::cout << "Invalid source position (" << fromRow << ", " << fromCol << ").\n";
		return;
	}

	if (board.IsEmpty(fromRow, fromCol))
	{
		std::cout << "There is no stack at the specified source position (" << fromRow << ", " << fromCol << ").\n";
		return;
	}

	if (board.TopCard(fromRow, fromCol).getColor() != currentPlayer->getColor())
	{
		std::cout << "The stack at (" << fromRow << ", " << fromCol << ") does not belong to you.\n";
		return;
	}

	if (!board.IsValidPosition(toRow, toCol))
	{
		std::cout << "Invalid destination position (" << toRow << ", " << toCol << ").\n";
		return;
	}

	if (!board.IsEmpty(toRow, toCol))
	{
		std::cout << "The destination position (" << toRow << ", " << toCol << ") is not empty.\n";
		return;
	}

	std::deque<Card> stack;

	while (!board.IsEmpty(fromRow, fromCol))
	{
		stack.push_back(board.TopCard(fromRow, fromCol));
		board.Remove(fromRow, fromCol);
	}

	while (!stack.empty()) {
		board.AddCard(toRow, toCol, stack.back());
		stack.pop_back();
	}

	std::cout << "Moved your stack from (" << fromRow << ", " << fromCol << ") to (" << toRow << ", " << toCol << ").\n";
}


void Wizard_Mode::grantExtraEterCard(int row, int col)
{
	Card extraCard(5, currentPlayer->getColor(), "Eter");
	currentPlayer->AddCard(extraCard);
	board.MakeMove(row, col, extraCard);
}


void Wizard_Mode::moveOpponentStack(int fromRow, int fromCol, int toRow, int toCol)
{

	if (board.IsEmpty(fromRow, fromCol))
	{
		std::cout << "There is no stack at the specified source position (" << fromRow << ", " << fromCol << ").\n";
		return;
	}

	if (board.TopCard(fromRow, fromCol).getColor() == currentPlayer->getColor())
	{
		std::cout << "You cannot move your own stack!\n";
		return;
	}

	if (!board.IsEmpty(toRow, toCol))
	{
		std::cout << "The destination position (" << toRow << ", " << toCol << ") is not empty.\n";
		return;
	}

	std::deque<Card> tempStack;

	while (!board.IsEmpty(fromRow, fromCol))
	{
		Card topCard = board.TopCard(fromRow, fromCol);
		RemoveCard(fromRow, fromCol);
		tempStack.push_back(topCard);
	}

	while (!tempStack.empty())
	{
		board.AddCard(toRow, toCol, tempStack.back());
		tempStack.pop_back();
	}
	std::cout << "Moved stack from (" << fromRow << ", " << fromCol << ") to (" << toRow << ", " << toCol << ").\n";
}

void Wizard_Mode::moveEdgeRow(int row) {
	int newRow;
	std::cout << "Enter the new edge row position: ";
	std::cin >> newRow;

	if (board.GetSize() > row && board.GetSize() > newRow && row != newRow) {
		for (int col = 0; col < board.GetSize(); ++col) {
			if (!board.IsEmpty(row, col)) {
				Card card = board.TopCard(row, col);
				RemoveCard(row, col);
				board.MakeMove(newRow, col, card);
			}
		}
		std::cout << "Moved row " << row << " to edge row " << newRow << ".\n";
	}
}



void Wizard_Mode::InitGame(std::string name1, std::string name2)
{
	board.SetSize(4);

	std::vector<int> values = { 1, 1, 2, 2, 2, 3, 3, 3, 4 };
	player1->setName(name1);
	player2->setName(name2);
	player1->setColor("red");
	player2->setColor("blue");

	std::ranges::for_each(values, [&](const auto& value) {
		player1->AddCard(Card(value, player1->getColor()));
		player2->AddCard(Card(value, player2->getColor()));
	});

	player1->AddCard(Card(5, player1->getColor(), "Eter"));
	player2->AddCard(Card(5, player2->getColor(), "Eter"));

	player1->setRandomWizardPower();
	player2->setRandomWizardPower();

	std::cout << player1->getName() << " has the power: " << GetWizardPowerName(player1->getWizardPower()) << std::endl;
	std::cout << player2->getName() << " has the power: " << GetWizardPowerName(player2->getWizardPower()) << std::endl;

	currentPlayer = player1.get();
}

Player* Wizard_Mode::CurrentTurn()
{
	return currentPlayer;
}

Player* Wizard_Mode::PreviousTurn()
{
	if (currentPlayer->getName() == player1->getName())
		return player2.get();
	else
		return player1.get();
}

std::string Wizard_Mode::GetWizardPowerName(WizardPower power)
{
	switch (power)
	{
	case WizardPower::RemoveOpponentCard:
		return "RemoveOpponentCard";
	case WizardPower::RemoveRow:
		return "RemoveRow";
	case WizardPower::CoverOpponentCard:
		return "CoverOpponentCard";
	case WizardPower::CreatePit:
		return "CreatePit";
	case WizardPower::MoveOwnStack:
		return "MoveOwnStack";
	case WizardPower::ExtraEterCard:
		return "ExtraEterCard";
	case WizardPower::MoveOpponentStack:
		return "MoveOpponentStack";
	case WizardPower::MoveEdgeRow:
		return "MoveEdgeRow";
	default:
		return "Unknown Power";
	}
}

void Wizard_Mode::SwitchTurn()
{
	if (currentPlayer->getName() == player1->getName())
	{
		currentPlayer = player2.get();
	}
	else
	{
		currentPlayer = player1.get();
	}
}


Wizard_Mode::Wizard_Mode()
{
	player1 = std::make_unique<Player>();
	player2 = std::make_unique<Player>();
	currentPlayer = NULL;
}

Wizard_Mode::~Wizard_Mode()
{
}


Wizard_Mode::Wizard_Mode(const Wizard_Mode& other) : board(other.board), player1(std::make_unique<Player>()), player2(std::make_unique<Player>()), currentPlayer(nullptr)
{}


Wizard_Mode& Wizard_Mode::operator=(const Wizard_Mode& other)
{
	if (this != &other)
	{
		board = other.board;
		player1 = std::make_unique<Player>(*other.player1);
		player2 = std::make_unique<Player>(*other.player2);
		currentPlayer = other.currentPlayer;
	}
	return *this;
}

Wizard_Mode& Wizard_Mode::operator=(Wizard_Mode&& other) noexcept
{
	if (this != &other)
	{
		board = std::move(other.board);
		player1 = std::move(other.player1);
		player2 = std::move(other.player2);
		currentPlayer = other.currentPlayer;

		other.currentPlayer = nullptr;
	}
	return *this;
}

Wizard_Mode::Wizard_Mode(Wizard_Mode&& other) noexcept : board(std::move(other.board)), player1(std::move(other.player1)),
player2(std::move(other.player2)), currentPlayer(other.currentPlayer)
{
	other.currentPlayer = nullptr;
}

void Wizard_Mode::ActivatePower(WizardPower power)
{
	switch (power)
	{
	case WizardPower::RemoveOpponentCard:
	{
		std::cout << currentPlayer->getName() << " used RemoveOpponentCard power!\n";
		int row, col;
		std::cout << "Enter the row and column of the opponent's card to remove: ";
		std::cin >> row >> col;

		removeOpponentCard(row, col);
		std::cout << "Removed the opponent's card at (" << row << ", " << col << ").\n";
		break;
	}

	case WizardPower::RemoveRow:
	{
		std::cout << currentPlayer->getName() << " used RemoveRow power!\n";
		int row1;
		std::cout << "Enter the row to remove: ";
		std::cin >> row1;

		removeRow(row1);
		std::cout << "Removed row " << row1 << ".\n";
		break;
	}

	case WizardPower::CoverOpponentCard:
	{
		std::cout << currentPlayer->getName() << " used CoverOpponentCard power!\n";
		int row2, col2;
		std::cout << "Enter the row and column of the opponent's card to cover: ";
		std::cin >> row2 >> col2;

		coverOpponentCard(row2, col2);
		std::cout << "Covered the opponent's card at (" << row2 << ", " << col2 << ").\n";
		break;
	}

	case WizardPower::CreatePit:
	{
		std::cout << currentPlayer->getName() << " used CreatePit power!\n";
		int row3, col3;
		std::cout << "Enter the row and column to create a pit: ";
		std::cin >> row3 >> col3;

		createPit(row3, col3);
		std::cout << "Created a pit at (" << row3 << ", " << col3 << ").\n";
		break;
	}

	case WizardPower::MoveOwnStack:
	{
		std::cout << currentPlayer->getName() << " used MoveOwnStack power!\n";

		int fromRow1, fromCol1;
		std::cout << "Enter the row and column of your stack to move: ";
		std::cin >> fromRow1 >> fromCol1;

		int toRow2, toCol2;
		std::cout << "Enter the row and column where you want to move the stack: ";
		std::cin >> toRow2 >> toCol2;

		moveOwnStack(fromRow1, fromCol1, toRow2, toCol2);
		break;
	}

	case WizardPower::ExtraEterCard:
	{
		std::cout << currentPlayer->getName() << " used ExtraEterCard power!\n";
		int row5, col5;
		std::cout << "Enter the row and column to grant an extra Eter card: ";
		std::cin >> row5 >> col5;

		grantExtraEterCard(row5, col5);
		std::cout << "Granted an extra Eter card at (" << row5 << ", " << col5 << ").\n";
		break;
	}

	case WizardPower::MoveOpponentStack:
	{
		std::cout << currentPlayer->getName() << " used MoveOpponentStack power!\n";

		int fromRow, fromCol;
		std::cout << "Enter the row and column of the opponent's stack to move: ";
		std::cin >> fromRow >> fromCol;

		int toRow, toCol;
		std::cout << "Enter the row and column where you want to move the stack: ";
		std::cin >> toRow >> toCol;

		moveOpponentStack(fromRow, fromCol, toRow, toCol);
		break;
	}

	case WizardPower::MoveEdgeRow:
	{
		std::cout << currentPlayer->getName() << " used MoveEdgeRow power!\n";
		int row7;
		std::cout << "Enter the edge row to move: ";
		std::cin >> row7;
		moveEdgeRow(row7);
		std::cout << "Moved edge row " << row7 << ".\n";
		break;
	}

	default:
		std::cout << "Unknown power.\n";
		break;
	}
}

void Wizard_Mode::RemoveCard(int row, int col)
{
	board.Remove(row, col);
}

void Wizard_Mode::ReturnCardToPlayer(int row, int col)
{
	if (!board.IsEmpty(row, col))
	{

		Card card = board.TopCard(row, col);
		board.Remove(row, col);

		if (card.getColor() == currentPlayer->getColor()) {
			currentPlayer->AddCard(card);
			std::cout << "Card returned to " << currentPlayer->getName() << "'s hand.\n";
		}
		else
		{
			
			Player* otherPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
			otherPlayer->AddCard(card);
			std::cout << "Card returned to " << otherPlayer->getName() << "'s hand.\n";
		}
	}
	else
	{
		std::cout << "No card to return at position (" << row << ", " << col << ").\n";
	}
}

void Wizard_Mode::CreatePit(int row, int col)
{
	auto& boardGrid = board.GetBoard();
	while (!boardGrid[row][col].empty())
	{
		boardGrid[row][col].pop();
	}

	std::cout << "Pit created at position (" << row << ", " << col << "). All cards removed.\n";
}

void Wizard_Mode::PlayGame()
{
	bool gameOver = false;
	while (!gameOver)
	{
		board.Display();
		std::cout << currentPlayer->getName() << "'s turn.\n";
		std::cout << "Choose an action:\n";
		std::cout << "Play card (c) or use power (p): ";
		char choice;
		std::cin >> choice;
		if (choice == 'p' && !currentPlayer->getPowerUsed())
		{
			char confirmChoice;
			std::cout << "Are you sure you want to use your power? (y/n): ";
			std::cin >> confirmChoice;

			if (confirmChoice == 'y' || confirmChoice == 'Y')
			{
				WizardPower power = currentPlayer->getWizardPower();
				ActivatePower(power);

				currentPlayer->setPowerUsed();
				SwitchTurn();
			}
			else
			{
				std::cout << "Action canceled. Returning to the main menu.\n";
			}
		}
		else if (choice == 'p' && currentPlayer->getPowerUsed())
		{
			std::cout << "You have already used your power this turn.\n";
		}
		else if (choice == 'c')
		{

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
				std::string lastPlace = board.GetSize() == 3 ? "" : " or 3";
				std::cout << "Enter the row and column to place the card (0, 1, 2" + lastPlace + ").\n";
				if (!board.IsDefinitiveBoard()) {
					std::cout << "The board is not definitive, you may also enter (-1, " + std::to_string(board.GetSize()) + ") to place the card in a special position.\n";
				}

				std::cin >> row >> col;
				result = board.CanMakeMove(row, col, chosenCard);

			} while (result == 0);
			if (result == 1)
			{
				board.MakeMove(row, col, chosenCard);
			}

			if (board.CheckIsBomb())
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

				if (currentPlayer->getName() == player1->getName())
					player1Wins++;
				else
					player2Wins++;

				if (player1Wins == 3)
				{
					std::cout << player1->getName() << " wins the game with 3 round wins!\n";
					gameOver = true;
				}
				else if (player2Wins == 3)
				{
					std::cout << player2->getName() << " wins the game with 3 round wins!\n";
					gameOver = true;
				}
				else
				{
					board.Clear();
					player1->setRandomWizardPower();
					player2->setRandomWizardPower();
					std::cout << player1->getName() << " has the power: " << GetWizardPowerName(player1->getWizardPower()) << std::endl;
					std::cout << player2->getName() << " has the power: " << GetWizardPowerName(player2->getWizardPower()) << std::endl;
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
					std::cout << player1->getName() << " wins the game with 3 round wins!\n";
					gameOver = true;
				}
				else if (player2Wins == 3)
				{
					std::cout << player2->getName() << " wins the game with 3 round wins!\n";
					gameOver = true;
				}
				else
				{
					board.Clear();
					player1->setRandomWizardPower();
					player2->setRandomWizardPower();
					std::cout << player1->getName() << " has the power: " << GetWizardPowerName(player1->getWizardPower()) << std::endl;
					std::cout << player2->getName() << " has the power: " << GetWizardPowerName(player2->getWizardPower()) << std::endl;
					SwitchTurn();
				}
				break;

			}
			else
			{
				SwitchTurn();
			}
		}
	}
	if (gameOver == true)
		std::cout << "Game over! Thanks for playing.\n";
}


void Wizard_Mode::ResetGame()
{
	board.Clear();
	player1->ClearCards();
	player2->ClearCards();
	InitGame(player1->getName(), player2->getName());
}