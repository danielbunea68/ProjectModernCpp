#pragma once

#include "TrainingCard.h"
#include <vector>
#include <iostream>

class TrainingBoard {
private:
    int size;
    std::vector<std::vector<TrainingCard>> board;

public:
    TrainingBoard(int s = 3);
    void DrawBoard();
    bool PlaceCard(int x, int y, const TrainingCard& card);
    bool CheckWin(int player_value);
    int GetSize() const;
};
