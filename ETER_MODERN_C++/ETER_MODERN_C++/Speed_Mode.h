#pragma once
#include "Board.h"
#include "IGame.h"
#include <chrono>


class Speed_Mode : public IGame {
private:
    Board board;
    Player player1, player2;
    Player* currentPlayer;
    bool isGameOver;

    int timeLimit;
    std::chrono::steady_clock::time_point turnStartTime;
    int remainingTimePlayer1;
    int remainingTimePlayer2;

    void SwitchTurn();
    void CheckWinner();
    void StartTurnTimer();
    bool CheckTimer();

public:
    Speed_Mode();
    ~Speed_Mode();
    Speed_Mode(const Speed_Mode& other);
    Speed_Mode& operator=(const Speed_Mode& other);
    Speed_Mode(Speed_Mode&& other) noexcept;
    Speed_Mode& operator=(Speed_Mode&& other) noexcept;

    void InitGame(std::string name1, std::string name2) override;
    //Player* CurrentTurn() override;
    //Player* PreviousTurn() override;
    void PlayGame() override;
    void ResetGame() override;

    void TimerBasedPlay();
    void ConfigureTimeLimit(int seconds);
};
