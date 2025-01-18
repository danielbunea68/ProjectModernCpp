#pragma once
#include "Board.h"
#include "Player.h"
#include "IGame.h"
#include "Game.h"
#include "Wizard_Mode.h"
#include "Element_Mode.h"
#include "Combined_Mode.h"

#include <vector>
#include <string>
#include <chrono>

class Speed_Mode : public IGame {
private:
    IGame* game = nullptr;
    std::vector<std::vector<std::string>> speed_board;
    char m_mode;
    bool isGameOver = false;

    // Timer variables
    int timeLimit;
    std::chrono::steady_clock::time_point turnStartTime;
    int remainingTimePlayer1;
    int remainingTimePlayer2;
    Player* currentPlayer;

    // Private helper methods
    void StartTurnTimer();
    bool CheckTimer();
    void ResetTimers();
    void HandleTimeout(Player* player);

public:
    Speed_Mode();
    ~Speed_Mode();
    Speed_Mode(const Speed_Mode& other);
    Speed_Mode& operator=(const Speed_Mode& other);
    Speed_Mode(Speed_Mode&& other) noexcept;
    Speed_Mode& operator=(Speed_Mode&& other) noexcept;

    void chooseGame();
    void setMode(char mode);
    bool CheckWinner(std::string color);
    int NumberOfTokens(std::string color);
    void PlayGameChosen(std::string name1, std::string name2);
    void updateBoard(int row, int col, std::string color);
    void DisplaySpeedBoard();

    // Timer-specific methods
    void ConfigureTimeLimit(int seconds);
    void DisplayTimeRemaining() const;
};
