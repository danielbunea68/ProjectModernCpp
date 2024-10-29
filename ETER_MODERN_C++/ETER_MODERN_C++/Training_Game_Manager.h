#pragma once

#include "Training_Board.h"
#include <vector>

class Training_Game_Manager {
private:
    Training_Board board;
    int current_player;
    std::vector<int> player_cards[2];

public:
    Training_Game_Manager(int board_size = 3);
    void SwitchPlayer();
    void PlayTrainingMode();
};
