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

void Tournament_Mode::Wizard_Element(std::string name1, std::string name2) 
{
    Wizard_Mode wizardGame;
    Element_Mode elementGame;

    wizardGame.InitGame(name1, name2);
    elementGame.InitGame(name1, name2);

    int totalRounds = 5;
    Player* currentPlayer = wizardGame.CurrentTurn();
    bool isover = false;

    while (totalRounds > 0 && !isover) {
        std::cout << "\nRound " << 6 - totalRounds << " begins!\n";

        bool useWizardPower = totalRounds % 2 == 0;
        std::cout << currentPlayer->getName()
            << (useWizardPower ? " is using a Wizard power.\n" : " is using an Element power.\n");

        while (true) {
            std::cout << "\n" << currentPlayer->getName() << "'s turn.\n";
            std::cout << "Choose an action:\n";
            std::cout << "1. Play card\n";
            std::cout << "2. Use power\n";
            std::cout << "3. End turn\n";
            int choice;
            std::cin >> choice;

            if (choice == 2) {
                if (useWizardPower && !currentPlayer->getPowerUsed()) {
                    char confirmChoice;
                    std::cout << "Are you sure you want to use your Wizard power? (y/n): ";
                    std::cin >> confirmChoice;

                    if (confirmChoice == 'y' || confirmChoice == 'Y') {
                        WizardPower power = currentPlayer->getWizardPower();
                        currentPlayer->setPowerUsed();
                        break;
                    }
                    else {
                        std::cout << "Action canceled.\n";
                    }
                }
                else if (!useWizardPower /* && !currentPlayer->getElementPowerUsed()*/) 
                {
                    char confirmChoice;
                    std::cout << "Are you sure you want to use your Element power? (y/n): ";
                    std::cin >> confirmChoice;

                    if (confirmChoice == 'y' || confirmChoice == 'Y') 
                    {
                        //Element_Mode::Putere power = currentPlayer->getElementPower(); 

                        //elementGame.ActivatePower(power);

                        //currentPlayer->setElementPowerUsed();
                        break;
                    }
                    else {
                        std::cout << "Action canceled.\n";
                    }
                }
                else {
                    std::cout << "Power already used or unavailable.\n";
                }
            }
            else if (choice == 1) {
                // Play card logic here
                currentPlayer->ShowHand();
                int cardIndex = -1;
                while (!currentPlayer->HasCardAtIndex(cardIndex)) {
                    std::cout << "Choose a card index to play: ";
                    std::cin >> cardIndex;
                }

                Card chosenCard = currentPlayer->PlayCard(cardIndex);
                int row, col;
                int result;
                do {
                    std::cout << "Enter row and column to place the card: ";
                    std::cin >> row >> col;
                    result = wizardGame.GetBoard().CanMakeMove(row, col, chosenCard);
                } while (result == 0);

                if (result == 1) {
                    wizardGame.GetBoard().MakeMove(row, col, chosenCard);
                    break;
                }
            }
            else if (choice == 3) {
                std::cout << "Turn ended.\n";
                break;
            }
            else {
                std::cout << "Invalid choice.\n";
            }
        }

        int x = currentPlayer->getWinnCords().first;
        int y = currentPlayer->getWinnCords().second;
        tournament_board[x][y] = currentPlayer->getColor();

        isover = CheckWinner(currentPlayer->getColor());
        if (isover) {
            std::cout << currentPlayer->getName() << " wins the hybrid mode!\n";
            break;
        }

        wizardGame.SwitchTurn();
        elementGame.SwitchTurn();
        currentPlayer = wizardGame.CurrentTurn();
        totalRounds--;
    }

    if (!isover) {
        std::cout << "Hybrid mode ended without a decisive winner!\n";
    }
}





void Tournament_Mode::DisplayTournamentBoard() {
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
