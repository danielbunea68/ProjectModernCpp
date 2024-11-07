#include "Game.h"
#include <iostream>

int main() {
	std::string name1, name2;
	std::cout << "Please insert name for player 1 and player 2: \n";
	std::cin >> name1 >> name2;

	Game game;
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
