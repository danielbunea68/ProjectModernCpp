#include "Tournament_Mode.h"

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
