#include "Game.h"
#include "Explosion_Card.h"

//Game::Game()
//{
//
//	currentPlayer = NULL;
//
//}

//Game::Game(const Game& other)
//{
//	board = other.board;
//	player1 = other.player1;
//	player2 = other.player2;
//	if (other.currentPlayer == &other.player1)
//		currentPlayer = &player1;
//	else if (other.currentPlayer == &other.player2)
//		currentPlayer = &player2;
//	else
//		currentPlayer = nullptr;
//}
//
//Game& Game::operator=(const Game& other)
//{
//	if (this == &other)
//		return *this; // Handle self-assignment
//
//	board = other.board;
//	player1 = other.player1;
//	player2 = other.player2;
//
//	// Deep copy for currentPlayer
//	if (other.currentPlayer == &other.player1)
//		currentPlayer = &player1;
//	else if (other.currentPlayer == &other.player2)
//		currentPlayer = &player2;
//	else
//		currentPlayer = nullptr;
//
//	return *this;
//}
//
//Game::Game(Game&& other) noexcept
//{
//	board = std::move(other.board);
//	player1 = std::move(other.player1);
//	player2 = std::move(other.player2);
//	currentPlayer = other.currentPlayer == &other.player1 ? &player1 :
//		other.currentPlayer == &other.player2 ? &player2 : nullptr;
//	other.currentPlayer = nullptr;
//
//}
//
//Game& Game::operator=(Game&& other) noexcept
//{
//	if (this == &other)
//		return *this; // Handle self-assignment
//
//	board = std::move(other.board);
//	player1 = std::move(other.player1);
//	player2 = std::move(other.player2);
//
//	// Move currentPlayer
//	currentPlayer = (other.currentPlayer == &other.player1) ? &player1 :
//		(other.currentPlayer == &other.player2) ? &player2 : nullptr;
//
//	other.currentPlayer = nullptr;
//
//	return *this;
//}
Game::Game()
	: player1(std::make_unique<Player>()), player2(std::make_unique<Player>()), currentPlayer(nullptr) {}



Game::Game(Game&& other) noexcept
	: board(std::move(other.board)), player1(std::move(other.player1)), player2(std::move(other.player2)),
	currentPlayer(other.currentPlayer) {
	other.currentPlayer = nullptr;
}

Game& Game::operator=(const Game& other) {
	if (this != &other) {
		board = other.board;
		player1 = std::make_unique<Player>(*other.player1);
		player2 = std::make_unique<Player>(*other.player2);
		currentPlayer = (other.currentPlayer == other.player1.get()) ? player1.get() : player2.get();
	}
	return *this;
}

Game& Game::operator=(Game&& other) noexcept {
	if (this != &other) {
		board = std::move(other.board);
		player1 = std::move(other.player1);
		player2 = std::move(other.player2);
		currentPlayer = other.currentPlayer;
		other.currentPlayer = nullptr;
	}
	return *this;
}

//void Game::InitGame(std::string name1, std::string name2)
//{
//	player1.setName(name1);
//	player2.setName(name2);
//	board.SetSize(3);
//	std::vector<int> values = { 1, 1, 2, 2, 3, 3, 4 };
//	player1.setColor("red");
//	player2.setColor("blue");
//	for (const auto& value : values) {
//		player1.AddCard(Card(value, player1.getColor()));
//		player2.AddCard(Card(value, player2.getColor()));
//	}
//	currentPlayer = &player1;
//	player1.isTurn = true;
//}
void Game::InitGame(std::string name1, std::string name2) {
	player1->setName(name1);
	player2->setName(name2);
	board.SetSize(3);
	player1->setColor("red");
	player2->setColor("blue");

	// Adding cards to the players
	std::vector<int> values = { 1, 1, 2, 2, 3, 3, 4 };
	for (const auto& value : values) {
		player1->AddCard(Card(value, player1->getColor()));
		player2->AddCard(Card(value, player2->getColor()));
	}

	currentPlayer = player1.get();
	player1->isTurn = true;
}

//void Game::InitGameWizard(std::string name1, std::string name2)
//{
//	player1.setName(name1);
//	player2.setName(name2);
//	board.SetSize(4);
//	std::vector<int> values = { 1, 1, 2, 2, 2, 3, 3, 3, 4 };
//	player1.setColor("red");
//	player2.setColor("blue");
//	for (const auto& value : values) {
//		player1.AddCard(Card(value, player1.getColor()));
//		player2.AddCard(Card(value, player2.getColor()));
//	}
//	player1.AddCard(Card(5, player1.getColor(), "Eter"));
//	player2.AddCard(Card(5, player2.getColor(), "Eter"));
//
//	player1.setRandomWizardPower();
//	player2.setRandomWizardPower();
//
//
//	currentPlayer = &player1;
//}
void Game::InitGameWizard(std::string name1, std::string name2)
{
	player1->setName(name1);
	player2->setName(name2);
	board.SetSize(4);
	std::vector<int> values = { 1, 1, 2, 2, 2, 3, 3, 3, 4 };
	player1->setColor("red");
	player2->setColor("blue");
	for (const auto& value : values) {
		player1->AddCard(Card(value, player1->getColor()));
		player2->AddCard(Card(value, player2->getColor()));
	}
	player1->AddCard(Card(5, player1->getColor(), "Eter"));
	player2->AddCard(Card(5, player2->getColor(), "Eter"));

	player1->setRandomWizardPower();
	player2->setRandomWizardPower();


	currentPlayer = player1.get();
}

int Game::GetScore(std::string color)
{
	int score = 0;
	/*for (int i = 0; i < board.GetSize(); i++)
	{
		for (int j = 0; j < board.GetSize(); j++)
		{
			if (!board.GetBoard()[i][j].empty() && board.GetBoard()[i][j].top().getColor() == color) {
				if (board.GetBoard()[i][j].top().getIsFaceDown() == true)
					score++;
				else
					score += board.GetBoard()[i][j].top().getValue();

			}
		}
	}*/
	std::ranges::for_each(board.GetBoard(), [&](const std::vector<std::stack<Card>>& row) {
		// Iterăm prin fiecare coloană din rândul curent
		std::ranges::for_each(row, [&](const std::stack<Card>& cell) {
			if (!cell.empty() && cell.top().getColor() == color) {
				if (cell.top().getIsFaceDown()) {
					score++; // Dacă este față în jos, incrementăm cu 1
				}
				else {
					score += cell.top().getValue(); // Dacă nu este față în jos, adăugăm valoarea cărții
				}
			}
			});
		});
	return score;
}

Player* Game::CurrentTurn()
{
	return currentPlayer;
}

//Player* Game::PreviousTurn()
//{
//	if (currentPlayer == &player1)
//		return &player2;
//	else
//		return &player1;
//}
Player* Game::PreviousTurn()
{
	if (currentPlayer == player1.get())
		return player2.get();
	else
		return player1.get();
}

Player* Game::getPlayer1()
{
	return player1.get();
}

Player* Game::getPlayer2()
{
	return player2.get();
}

//void Game::SwitchTurn()
//{
//	if (currentPlayer->getName() == player1.getName())
//	{
//		currentPlayer = &player2;
//	}
//	else
//	{
//		currentPlayer = &player1;
//	}
//	player1.isTurn = !player1.isTurn;
//	player2.isTurn = !player2.isTurn;
//	currentPlayer->selectedIndex = 0;
//	currentPlayer->selectedBomb = false;
//	
//}
void Game::SwitchTurn()
{
	if (currentPlayer->getName() == player1->getName())
	{
		currentPlayer = player2.get();
	}
	else
	{
		currentPlayer = player1.get();
	}
	player1->isTurn = !player1->isTurn;
	player2->isTurn = !player2->isTurn;
	currentPlayer->selectedIndex = 0;
	currentPlayer->selectedBomb = false;

}

void Game::useBomb(Player* player)
{
	auto bomb = player->getBomb();
	player->hasBomb = false;
	player->selectedBomb = false;



	//for (int i = 0; i < bomb->board.size(); i++) {
	//	for (int j = 0; j < bomb->board.size(); j++) {
	//		char action = bomb->board[i][j];
	//		switch (action)
	//		{
	//		case 'r':
	//			RemoveCard(i, j);
	//			break;
	//		case 'u':
	//			ReturnCardToPlayer(i, j);
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	for (auto i : std::views::iota(0, static_cast<int>(bomb->board.size()))) {
		for (auto j : std::views::iota(0, static_cast<int>(bomb->board.size()))) {
			char action = bomb->board[i][j];
			switch (action) {
			case 'r':
				RemoveCard(i, j);
				break;
			case 'u':
				ReturnCardToPlayer(i, j);
				break;
			default:
				break;
			}
		}
	}

}

void Game::usePower(Player* player, int prevCol, int prevRow, int row, int col)
{
	player->hasPower = false;
	player->selectedPower = false;
	WizardPower power = currentPlayer->getWizardPower();
	ActivatePower(power, prevRow, prevCol, row, col);

	currentPlayer->setPowerUsed();
}

void Game::ActivatePower(WizardPower power, int prevRow, int prevCol, int row , int col )
{
	switch (power)
	{
	case WizardPower::RemoveOpponentCard:
	{
		removeOpponentCard(row, col);
		break;
	}

	case WizardPower::RemoveRow:
	{
		removeRow(row);
		break;
	}

	case WizardPower::CoverOpponentCard:
	{
		coverOpponentCard(row, col);
		break;
	}

	case WizardPower::CreatePit:
	{
		createPit(row, col);
		break;
	}

	case WizardPower::MoveOwnStack:
	{

		moveOwnStack(prevRow, prevCol, row, col);
		break;
	}

	case WizardPower::ExtraEterCard:
	{
		grantExtraEterCard(row, col);
		break;
	}

	case WizardPower::MoveOpponentStack:
	{

		moveOpponentStack(prevRow, prevCol, row, col);
		break;
	}

	case WizardPower::MoveEdgeRow:
	{
		moveEdgeRow(row);
		break;
	}

	default:
		std::cout << "Unknown power.\n";
		break;
	}
}

void Game::removeOpponentCard(int row, int col)
{
	if (!board.IsValidPosition(row, col) || board.IsEmpty(row, col) || board.TopCard(row, col).getColor() == currentPlayer->getColor()) {
		std::cout << "Cannot remove card at (" << row << ", " << col << "). Invalid position or not an opponent's card.\n";
		return;
	}

	board.Remove(row, col);
	std::cout << "Removed opponent's card at (" << row << ", " << col << ").\n";
}

void Game::removeRow(int row)
{
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

void Game::coverOpponentCard(int row, int col)
{
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

void Game::createPit(int row, int col)
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

void Game::moveOwnStack(int fromRow, int fromCol, int toRow, int toCol)
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

void Game::moveOpponentStack(int fromRow, int fromCol, int toRow, int toCol)
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

void Game::moveEdgeRow(int row)
{
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

void Game::grantExtraEterCard(int row, int col)
{
	Card extraCard(5, currentPlayer->getColor(), "Eter");
	currentPlayer->AddCard(extraCard);
	board.MakeMove(row, col, extraCard);
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
			///Player* otherPlayer = (currentPlayer == &player1) ? &player2 : &player1;
			Player* otherPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
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
	if (board.IsBlockedCell(row, col)) 
	{
		std::cout << "Cannot create a pit at (" << row << ", " << col << "). The cell is already blocked.\n";
		return;
	}

	auto& boardGrid = board.GetBoard();
	while (!board.IsEmpty(row, col)) 
	{
		boardGrid[row][col].pop();
	}

	board.BlockCell(row, col);

	std::cout << "Pit created at (" << row << ", " << col << "). This cell is now blocked.\n";

}

bool Game::IsDraw()
{
	auto opponent = PreviousTurn();
	auto board = this->board.GetBoard();

	for (auto row : board) {
		for (auto col : row) {
			if (col.empty()) return false;

			for (auto card : opponent->getCards()) {
				if (card.getColor() == col.top().getColor()) continue;
				if (card.getValue() > col.top().getValue()) return false;
			}
		}
	}
	return true;
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

//void Game::ResetGame()
//{
//	board.Clear();
//	player1.ClearCards();
//	player2.ClearCards();
//	InitGame(player1.getName(), player2.getName());
//}
void Game::ResetGame()
{
	board.Clear();
	player1->ClearCards();
	player2->ClearCards();
	InitGame(player1->getName(), player2->getName());
}

Board Game::getboard()
{
	return board;
}
