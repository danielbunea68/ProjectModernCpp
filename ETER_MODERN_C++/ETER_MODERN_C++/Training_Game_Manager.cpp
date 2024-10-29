#include "Training_Game_Manager.h"
#include <iostream>

Training_Game_Manager::Training_Game_Manager(int board_size) : board(board_size), current_player(1) {
    player_cards[0] = {1, 1, 2, 2, 3, 3, 4};
    player_cards[1] = {1, 1, 2, 2, 3, 3, 4};
}

void Training_Game_Manager::SwitchPlayer() {
    current_player = (current_player == 1) ? 2 : 1;
}

void Training_Game_Manager::PlayTrainingMode() {
    int x, y, card_index;

    std::cout << "Training Mode - Eter Game\n";
    while (true) {
        board.DrawBoard();
        std::cout << "Player " << current_player << "'s turn.\n";

        std::cout << "Your cards: ";
        for (int i = 0; i < player_cards[current_player - 1].size(); i++) {
            std::cout << player_cards[current_player - 1][i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Choose card index (0-" << player_cards[current_player - 1].size() - 1 << ") to play, or -1 to quit: ";
        std::cin >> card_index;
        if (card_index == -1) break;
        if (card_index < 0 || card_index >= player_cards[current_player - 1].size()) {
            std::cout << "Invalid card selection! Try again.\n";
            continue;
        }

        std::cout << "Enter x y (row col) to place card: ";
        std::cin >> x >> y;

        TrainingCard chosen_card(player_cards[current_player - 1][card_index]);
        if (board.PlaceCard(x, y, chosen_card)) {
            std::cout << "Card placed successfully.\n";
            player_cards[current_player - 1].erase(player_cards[current_player - 1].begin() + card_index);

            if (board.CheckWin(current_player)) {
                board.DrawBoard();
                std::cout << "Player " << current_player << " wins!\n";
                break;
            }

            SwitchPlayer();
        } else {
            std::cout << "Invalid placement! Try again.\n";
        }

        if (player_cards[0].empty() && player_cards[1].empty()) {
            std::cout << "It's a draw!\n";
            break;
        }
    }
}
