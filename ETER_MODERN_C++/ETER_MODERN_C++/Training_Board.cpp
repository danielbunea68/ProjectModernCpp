#include "Training_Board.h"

Training_Board::Training_Board(int s) : size(s), board(s, std::vector<TrainingCard>(s, TrainingCard(0))) {}

void Training_Board::DrawBoard() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j].IsEmpty()) {
                std::cout << " . ";
            } else {
                std::cout << " " << board[i][j].GetValue() << " ";
            }
            if (j < size - 1) std::cout << "|";
        }
        std::cout << std::endl;
        if (i < size - 1) std::cout << "---|---|---\n";
    }
}

bool Training_Board::PlaceCard(int x, int y, const TrainingCard& card) {
    if (x < 0 || x >= size || y < 0 || y >= size || (!board[x][y].IsEmpty() && board[x][y].GetValue() >= card.GetValue())) {
        return false;
    }

    board[x][y] = card;
    return true;
}

bool Training_Board::CheckWin(int player_value) {
    for (int i = 0; i < size; i++) {
        if ((board[i][0].GetValue() == player_value && board[i][1].GetValue() == player_value && board[i][2].GetValue() == player_value) ||
            (board[0][i].GetValue() == player_value && board[1][i].GetValue() == player_value && board[2][i].GetValue() == player_value)) {
            return true;
        }
    }
    return (board[0][0].GetValue() == player_value && board[1][1].GetValue() == player_value && board[2][2].GetValue() == player_value) ||
           (board[0][2].GetValue() == player_value && board[1][1].GetValue() == player_value && board[2][0].GetValue() == player_value);
}

int Training_Board::GetSize() const {
    return size;
}
