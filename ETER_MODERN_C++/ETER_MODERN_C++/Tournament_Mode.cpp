#include "Tournament_Mode.h"

Tournament_Mode::~Tournament_Mode()
{
	delete game;
}

Tournament_Mode::Tournament_Mode(const Tournament_Mode& other)
{
	
	tournament_board = other.tournament_board;
	m_mode = other.m_mode;
	isover = other.isover;
}

Tournament_Mode& Tournament_Mode::operator=(const Tournament_Mode& other)
{
	if (this == &other) return *this; // Auto-atribuire
	delete game; // Eliberăm resursa existentă
	tournament_board = other.tournament_board;
	m_mode = other.m_mode;
	isover = other.isover;
	return *this;
}

Tournament_Mode::Tournament_Mode(Tournament_Mode&& other) noexcept
{
	game = other.game;
	tournament_board = std::move(other.tournament_board);
	m_mode = other.m_mode;
	isover = other.isover;
	other.game = nullptr; 
}

Tournament_Mode& Tournament_Mode::operator=(Tournament_Mode&& other) noexcept
{
	if (this == &other) return *this; // Auto-atribuire
	delete game; // Eliberăm resursa existentă
	game = other.game;
	tournament_board = std::move(other.tournament_board);
	m_mode = other.m_mode;
	isover = other.isover;
	other.game = nullptr; // Invalidăm resursa din other
	return *this;
}


void Tournament_Mode::choseGame()
{	
	switch (m_mode)
	{
	case 't' :
		game = new Game();
		break;
	case 'w':
		game = new Wizard_Mode();
		break;
	case 'e':
		game = new Element_Mode();
			break;
    case 'a': 
        game = new Combined_Mode();
        break;
	default:
		break;
	}
	

}



void Tournament_Mode::setmode(char mode)
{
	m_mode = mode;
}

bool Tournament_Mode::CheckWinner(std::string color)
{
	for (int i = 0; i < 3; i++)
	{
		if (tournament_board[i][0].empty() || tournament_board[0][i].empty() || tournament_board[i][1].empty() || tournament_board[1][i].empty() || tournament_board[i][2].empty() || tournament_board[2][i].empty())
			return false;
		if ((tournament_board[i][0] == color && tournament_board[i][1] == color && tournament_board[i][2] == color) ||
			(tournament_board[0][i] == color && tournament_board[1][i] == color && tournament_board[2][i] == color)) {
			return true;
		}
	}
	if ((tournament_board[0][0]== color && tournament_board[1][1] == color && tournament_board[2][2] == color) ||
		(tournament_board[0][2] == color && tournament_board[1][1]== color && tournament_board[2][0] == color)) {
		return true;
	}
	return false;
}

int Tournament_Mode::NumberOfTokens(std::string color)
{
	int nr = 0; 
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tournament_board[i][j] == color)
				nr++;
		}
	}

	return nr;
}

void Tournament_Mode::PlayGameChosen(std::string name1, std::string name2) 
{

    game->InitGame(name1, name2);
	Player* player=nullptr;
	Player* second_player = nullptr;
	int number_of_games = 5; 
	
	while (number_of_games&& isover!=true)
	{
		game->PlayGame();

		if ( second_player!=player)
			second_player = player; 

		player = game->CurrentTurn();
		int x = player->getWinnCords().first;
		int y = player->getWinnCords().second;
		tournament_board[x][y] = player->getColor();
		isover = CheckWinner(player->getColor());
		game->ResetGame();
		number_of_games--;

	}
	if (isover == true)
		std::cout << player->getName() << " a castigat !";
	else
	{
		int nr1 = NumberOfTokens(player->getColor());
		second_player = game->PreviousTurn();
		int nr2 = NumberOfTokens(second_player->getColor());
		if (nr1 > nr2)
			std::cout << player->getName() << " a castigat ";
		else
			std::cout << second_player->getName() << " a castigat";
	}
	 
}
/*
void Tournament_Mode::Wizard_Element(std::string name1, std::string name2) {
    Wizard_Mode wizardGame;
    Element_Mode elementGame;

    wizardGame.InitGame(name1, name2);
    elementGame.InitGame(name1, name2);
    elementGame.InitializePowers();

    int totalRounds = 5;
    Player* currentPlayer = wizardGame.CurrentTurn();
    bool isGameOver = false;

    // Create a unified board
    Board unifiedBoard;
    unifiedBoard.SetSize(4); // Initialize a 4x4 board

    while (totalRounds > 0 && !isGameOver) {
        std::cout << "\nRound " << (6 - totalRounds) << " begins!\n";

        while (true) 
        {
            unifiedBoard.Display();

            // Current player's turn
            std::cout << currentPlayer->getName() << "'s turn.\n";
            std::cout << "Choose an action:\n";
            std::cout << "1. Play card\n";
            std::cout << "2. Use Wizard power\n";
            std::cout << "3. Use Element power\n";

            int choice;
            std::cin >> choice;

            if (choice == 1) { // Play a card
                currentPlayer->ShowHand();
                int cardIndex = -1;
                while (true) {
                    std::cout << currentPlayer->getName() << ", choose a card index to play: ";
                    std::cin >> cardIndex;
                    if (currentPlayer->HasCardAtIndex(cardIndex)) {
                        break;
                    }
                    std::cout << "Invalid card index. Try again.\n";
                }

                Card chosenCard = currentPlayer->PlayCard(cardIndex);

                if (currentPlayer->CanPlaceCardFaceDown()) {
                    char answer = 'n';
                    std::cout << "Do you want to play this card face down? y/[n]\n";
                    std::cin >> answer;
                    if (answer == 'y') {
                        currentPlayer->PlayedCardFaceDown();
                        chosenCard.setFaceDown(true);
                    }
                }

                int row = -1, col = -1, result = 0;

                do {
                    std::cout << "Enter the row and column to place the card (0-3).\n";
                    std::cin >> row >> col;

                    // Validate board coordinates
                    if (row < 0 || row >= unifiedBoard.GetSize() || col < 0 || col >= unifiedBoard.GetSize()) {
                        std::cout << "Invalid board coordinates. Please try again.\n";
                        continue;
                    }

                    // Debugging: Check CanMakeMove call
                    std::cout << "Checking CanMakeMove for row: " << row << ", col: " << col << "\n";

                    result = unifiedBoard.CanMakeMove(row, col, chosenCard);

                    if (result == 0) {
                        std::cout << "Move not allowed. Try again.\n";
                    }
                } while (result == 0);

                if (result == 1) {
                    unifiedBoard.MakeMove(row, col, chosenCard);
                    unifiedBoard.Display();
                    currentPlayer->setLastMove(row, col);
                }

                break; // End turn after playing a card
            }
            else if (choice == 2) { // Use Wizard power
                if (!currentPlayer->getPowerUsed()) {
                    char confirmChoice;
                    std::cout << "Are you sure you want to use your Wizard power? (y/n): ";
                    std::cin >> confirmChoice;

                    if (confirmChoice == 'y' || confirmChoice == 'Y') {
                        WizardPower power = currentPlayer->getWizardPower();
                        wizardGame.ActivatePower(power);
                        currentPlayer->setPowerUsed();
                        std::cout << currentPlayer->getName() << " has used their Wizard power.\n";
                        break; // End turn after using Wizard power
                    }
                    else {
                        std::cout << "Action canceled. Returning to the main menu.\n";
                    }
                }
                else {
                    std::cout << "Wizard power has already been used this turn.\n";
                }
            }
            else if (choice == 3) { // Use Element power
                if (!currentPlayer->getElementPowerUsed()) {
                    std::vector<Element_Mode::Putere> availablePowers = elementGame.GetAvailablePowers();
                    if (availablePowers.empty()) {
                        std::cout << "No Element powers are available to use.\n";
                        continue;
                    }

                    std::cout << "Available Element powers:\n";
                    for (size_t i = 0; i < availablePowers.size(); ++i) {
                        std::cout << i + 1 << ". " << elementGame.GetPowerName(availablePowers[i]) << " - "
                            << elementGame.GetPowerDescription(availablePowers[i]) << "\n";
                    }

                    int powerChoice = -1;
                    while (true) {
                        std::cout << "Choose an Element power to use (1-" << availablePowers.size() << "): ";
                        std::cin >> powerChoice;

                        if (powerChoice > 0 && powerChoice <= static_cast<int>(availablePowers.size())) {
                            break;
                        }
                        std::cout << "Invalid choice. Try again.\n";
                    }

                    Element_Mode::Putere power = availablePowers[powerChoice - 1];
                    if (elementGame.CanUsePower(power)) {
                        elementGame.ActivatePower(power);
                        currentPlayer->setElementPowerUsed(true);
                        std::cout << currentPlayer->getName() << " has used their Element power.\n";
                        break; // End turn after using Element power
                    }
                    else {
                        std::cout << "This power is either unavailable or already used.\n";
                    }
                }
                else {
                    std::cout << "Element power has already been used this turn.\n";
                }
            }
            else {
                std::cout << "Invalid choice. Try again.\n";
            }
        }

        // Update the tournament board
        int x = currentPlayer->getWinnCords().first;
        int y = currentPlayer->getWinnCords().second;
        tournament_board[x][y] = currentPlayer->getColor();

        // Check for a winner
        isGameOver = CheckWinner(currentPlayer->getColor());
        if (isGameOver) {
            std::cout << currentPlayer->getName() << " wins the game!\n";
            break;
        }

        // Switch turns for both games
        wizardGame.SwitchTurn();
        elementGame.SwitchTurn();
        currentPlayer = wizardGame.CurrentTurn(); // Synchronize the current player
        totalRounds--;
    }

    if (!isGameOver) {
        std::cout << "The game ended without a decisive winner.\n";
    }
}

*/

void Tournament_Mode::DisplayTournamentBoard() 
{
    std::cout << "\nCurrent Tournament Board:\n";
    for (const auto& row : tournament_board) {
        for (const auto& cell : row) {
            if (cell.empty()) {
                std::cout << "   .   ";
            } else {
                std::cout << "   " << cell << "   ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
