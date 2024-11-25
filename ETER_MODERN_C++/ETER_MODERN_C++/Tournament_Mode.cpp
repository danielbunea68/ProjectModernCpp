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

void Tournament_Mode::PlayGameChosen(std::string name1, std::string name2)
{
	game->InitGame(name1, name2);
	game->PlayGame();

	game->ResetGame();

	 
}
