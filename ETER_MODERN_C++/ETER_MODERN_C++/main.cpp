#include "Game.h"
#include "IGame.h"
#include "Element_Mode.h"
#include "Wizard_Mode.h"
#include "Tournament_Mode.h"
#include "Combined_Mode.h"
#include "Speed_Mode.h"
#include <iostream>

int main() {
    std::string name1, name2;
    std::cout << "Please insert name for player 1 and player 2: \n";
    std::cin >> name1 >> name2;

    IGame* game = nullptr;
    Tournament_Mode* game_special = nullptr;

    char mode;
    std::cout << "Choose a game mode: \nTraining (t)\nWizard Mode (w)\nElemental Cards (e)\nTournament Mode (T)\n Speed Mode (s)";
    std::cin >> mode;
    int ok = 0;
    switch (mode) {
    case 't':
        std::cout << "You chose Training mode.\n";
        game = new Game();
        break;
    case 'w':
        std::cout << "You chose Wizard Mode.\n";
        game = new Wizard_Mode();
        break;
    case 'e':
        std::cout << "You chose Elemental Cards mode.\n";
        game = new Element_Mode();
        break;
    case 'T':
        std::cout << "You chose Tournament Mode.\n";
        game_special = new Tournament_Mode();
        ok = 1;
        break;
    case 's':
        std::cout << "You chose Speed Mode.\n";
        game_special = new Speed_Mode();
        ok = 1;
        break;
    case 'c':
        std::cout << "You chose Combined mode.\n";
        game = new Combined_Mode();
        break;
    default:
        std::cout << "Invalid option! Defaulting to Training mode.\n";
        game = new Game();
        break;
    }

    if (ok == 1)
    {
        char c;
        std::cout << "Choose your game (Choose x for element + wizard): ";
        std::cin >> c;
        game_special->setmode(c);
        game_special->choseGame();
        game_special->PlayGameChosen(name1, name2);
    }
    else
    {
        game->InitGame(name1, name2);
        bool keepPlaying = true;

        while (keepPlaying) {
            game->PlayGame();

            char answer = 'n';
            std::cout << "Do you want to play again? y/[n]\n";
            std::cin >> answer;
            if (answer == 'y') {
                game->ResetGame();
            }
            else {
                break;
            }
        }

        std::cout << "Game over. Thanks for playing!\n";
    }
    return 0;
}


/*
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
    Q_INIT_RESOURCE(resources);
    


	MainWindow window;
	window.resize(1200, 400);
	window.show();

	return app.exec();

}
*/