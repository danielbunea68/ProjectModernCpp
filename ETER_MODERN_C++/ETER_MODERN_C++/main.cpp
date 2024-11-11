#include "Game.h"
#include <iostream>

int main() {
	std::string name1, name2;
	std::cout << "Please insert name for player 1 and player 2: \n";
	std::cin >> name1 >> name2;


	// Clasa abstracta game
	// Aici pui toate metodele comune
	// Vei suprascrie doar ceea ce se modifica
	


	// Template pattern
	// https://refactoring.guru/design-patterns/template-method
	// Definesti metode hook in clasa parinte
	// In clasa copil care mosteneste parinte dai override la metodele hook



	// Marchezi metodele hook ca si virtual
	// In clasa WizardMode suprascrii aceste metode si adaugi logica noua




	// IGame - interfata
	// Game -> TrainingMode : IGame
	// In interfata metodele vor fi virtual ... = 0;
	// In clasele concrete vei da override
	Game game;

	/*char mode;
	std::cout << "Alege un mod de joc: \nTraining (t)\nWizard Mode (w)\nElemental Cards (e)\n";
	std::cin >> mode;

	switch (mode) {
	case 't':
		std::cout << "Ai ales modul trainig\n";
		game = new Training();
		break;
	case 'w':
		game = new Wizard();
		break;
	case 'e':
		game = new Elemental();
		break;
	default:
		game = Training();
		break;
	}*/

	game.InitGame(name1, name2);
	bool keepPlaying = true;
	while (keepPlaying) {
		game.PlayGame();

		char answer = 'n';
		std::cout << "Do you want to play again? y/[n]\n";
		std::cin >> answer;
		if (answer == 'y') {
			game.ResetGame();
		}
		else {
			break;
		}
	}

	std::cout << "Game over. Thanks for playing!\n";
	return 0;
}//