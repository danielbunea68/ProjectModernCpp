#include "Game.h"
#include "Board.h"
#include "Player.h"
#include <iostream>

    int main() {
        int board_size = 4;
        Game game(board_size);

        Player player1("Player 1");
        Player player2("Player 2");
        game.AddPlayer(player1);
        game.AddPlayer(player2);

        game.Start();

        while (!game.IsGameOver()) {
            game.DisplayBoard();

            Player& current_player = game.GetCurrentPlayer();
            std::cout << current_player.GetName() << "'s turn.\n";

            current_player.DisplayAvailableCards();

            int x, y, card_index;
            std::cout << "Enter the card index to play: ";
            std::cin >> card_index;
            std::cout << "Enter the coordinates (x y) for placement: ";
            std::cin >> x >> y;

            if (game.PlaceCard(current_player, card_index, x, y)) {
                std::cout << "Card placed successfully.\n";
            } else {
                std::cout << "Invalid move. Try again.\n";
                continue;
            }

            if (game.CheckWinCondition(current_player)) {
                std::cout << current_player.GetName() << " wins!\n";
                break;
            } else if (game.CheckDrawCondition()) {
                std::cout << "The game is a draw!\n";
                break;
            }
            game.NextTurn();
        }

        std::cout << "Game over. Thanks for playing!\n";
        return 0;
    }
	return 0;
}