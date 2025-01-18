#pragma once
#include "Board.h"
#include "IGame.h"
#include <chrono>


class Speed_Mode : public IGame {
private:
    Board board;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    Player* currentPlayer = nullptr;

    bool isGameOver;
    int timeLimit;
    std::chrono::steady_clock::time_point turnStartTime;
    int remainingTimePlayer1;
    int remainingTimePlayer2;

    void SwitchTurn();
    void CheckWinner();
    void StartTurnTimer();
    bool CheckTimer();
    void ResetTimers();
    void TimerBasedPlay();
    void HandleTimeout(Player* player);

public:
    Speed_Mode();
    ~Speed_Mode();
    Speed_Mode(const Speed_Mode& other) = delete;
    Speed_Mode& operator=(const Speed_Mode& other) = delete;
    Speed_Mode(Speed_Mode&& other) noexcept = default;
    Speed_Mode& operator=(Speed_Mode&& other) noexcept = default;

    void InitGame(std::string name1, std::string name2) override;
    //Player* CurrentTurn() override;
    //Player* PreviousTurn() override;
    void PlayGame() override;
    void ResetGame() override;

    void ConfigureTimeLimit(int seconds);
    //void InitGame(std::string name1, std::string name2) override;
    void DisplayTimeRemaining() const;
};
