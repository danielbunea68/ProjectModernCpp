//
//#include "Game.h"
//#include "IGame.h"
//#include "Element_Mode.h"
//#include "Wizard_Mode.h"
//#include "Tournament_Mode.h"
//#include <iostream>
//
//int main() {
//	std::string name1, name2;
//	std::cout << "Please insert name for player 1 and player 2: \n";
//	std::cin >> name1 >> name2;
//
//
//	// Clasa abstracta game
//	// Aici pui toate metodele comune
//	// Vei suprascrie doar ceea ce se modifica
//	
//
//
//	// Template pattern
//	// https://refactoring.guru/design-patterns/template-method
//	// Definesti metode hook in clasa parinte
//	// In clasa copil care mosteneste parinte dai override la metodele hook
//
//
//
//	// Marchezi metodele hook ca si virtual
//	// In clasa WizardMode suprascrii aceste metode si adaugi logica noua
//
//
//
//
//	// IGame - interfata
//	// Game -> TrainingMode : IGame
//	// In interfata metodele vor fi virtual ... = 0;
//	// In clasele concrete vei da override
//	IGame *game = nullptr; 
//	Tournament_Mode* game_special = nullptr;;
//
//
//	char mode;
//	std::cout << "Alege un mod de joc: \nTraining (t)\nWizard Mode (w)\nElemental Cards (e)\nTournament Mode (T)\n";
//	std::cin >> mode;
//
//	switch (mode) {
//	case 't':
//		std::cout << "Ai ales modul Trainig\n";
//		game = new Game();
//		break;
//	case 'w':
//		std::cout << "Ai ales modul Wizard\n";
//		game = new Wizard_Mode();
//		break;
//	case 'e':
//		std::cout << "Ai ales modul Element\n";
//		game = new Element_Mode();
//		break;
//	case 'T':
//		std::cout << "Ai ales modul Tournament\n";
//		game_special = new Tournament_Mode();
//		break;
//	default : 
//		std::cout << "Optiune invalida! Se alege implicit modul Training\n";
//		game = new Game();
//		break;
//	}
//
//	game->InitGame(name1, name2);
//	bool keepPlaying = true;
//	while (keepPlaying) {
//		game->PlayGame();
//
//		char answer = 'n';
//		std::cout << "Do you want to play again? y/[n]\n";
//		std::cin >> answer;
//		if (answer == 'y') {
//			game->ResetGame();
//		}
//		else {
//			break;
//		}
//	}
//
//	std::cout << "Game over. Thanks for playing!\n";
//	return 0;
//}//
#include "Game.h"
#include "IGame.h"
#include "Element_Mode.h"
#include "Wizard_Mode.h"
#include "Tournament_Mode.h"
#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QFrame>
#include <QGridLayout>
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <MainWindow.h>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	MainWindow window;
	window.resize(800, 400);
	window.show();

	return app.exec();

}