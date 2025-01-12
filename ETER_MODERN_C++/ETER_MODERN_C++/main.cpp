//
//#include "Game.h"
//#include "IGame.h"
//#include "Element_Mode.h"
//#include "Wizard_Mode.h"
//#include "Tournament_Mode.h"
//#include "Combined_Mode.h"
//#include <iostream>
//
//int main() {
//    std::string name1, name2;
//    std::cout << "Please insert name for player 1 and player 2: \n";
//    std::cin >> name1 >> name2;
//
//    // Abstract class Game
//    // This is where you define all common methods
//    // You will override only those methods that are modified in subclasses
//
//    // Template Pattern (Design Pattern)
//    // https://refactoring.guru/design-patterns/template-method
//    // Define hook methods in the parent class.
//    // In the child class that inherits the parent, you override the hook methods.
//
//    // Mark hook methods as virtual.
//    // In the WizardMode class, override these methods and add the new logic.
//
//    // IGame - Interface
//    // Game -> TrainingMode : IGame
//    // In the interface, the methods will be virtual and = 0 (pure virtual).
//    // In concrete classes, you will override them.
//
//    IGame* game = nullptr;
//    Tournament_Mode* game_special = nullptr;  // Keep this if you need to handle a Tournament Mode separately.
//
//    // User selects the game mode
//    char mode;
//    std::cout << "Choose a game mode: \nTraining (t)\nWizard Mode (w)\nElemental Cards (e)\nTournament Mode (T)\n";
//    std::cin >> mode;
//    int ok = 0;
//    switch (mode) {
//    case 't':
//        std::cout << "You chose Training mode.\n";
//        game = new Game();  // Instantiate the Game mode
//        break;
//    case 'w':
//        std::cout << "You chose Wizard Mode.\n";
//        game = new Wizard_Mode();  // Instantiate the Wizard Mode
//        break;
//    case 'e':
//        std::cout << "You chose Elemental Cards mode.\n";
//        game = new Element_Mode();  // Instantiate the Element Mode
//        break;
//    case 'T':
//        std::cout << "You chose Tournament Mode.\n";
//        game_special = new Tournament_Mode();  // Instantiate the Tournament Mode
//        ok = 1; 
//        break;
//    case 'c':
//        std::cout << "You chose Combined mode.\n";
//        game = new Combined_Mode();  // Instantiate the Combined Mode
//        break;
//    default:
//        std::cout << "Invalid option! Defaulting to Training mode.\n";
//        game = new Game();  // Default to Game mode if an invalid option is selected
//        break;
//    }
//
//    // Initialize the game with player names
//
//    if (ok == 1)
//    {
//        char c; 
//        std::cout << "Choose your game (Choose x for element + wizard): ";
//        std::cin >> c; 
//        game_special->setmode(c); /// steteaza modul de joc 
//        game_special->choseGame();/// creeaza obiectul 
//    
//        game_special->PlayGameChosen(name1,name2);
//    }
//    else
//    {
//        game->InitGame(name1, name2);
//        bool keepPlaying = true;
//
//        // Main game loop
//        while (keepPlaying) {
//            game->PlayGame();  // Run the main game logic
//
//            char answer = 'n';
//            std::cout << "Do you want to play again? y/[n]\n";
//            std::cin >> answer;
//            if (answer == 'y') {
//                game->ResetGame();  // Reset the game if the player chooses to play again
//            }
//            else {
//                break;  // Exit the loop if the player chooses not to play again
//            }
//        }
//
//        std::cout << "Game over. Thanks for playing!\n";  // End of game message
//    }
//    return 0;
//}

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
