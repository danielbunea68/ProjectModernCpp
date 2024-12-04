/*#pragma once
#include "Board.h"
#include "Player.h"
#include "IGame.h"

class Speed_Mode : public IGame {
private:
    Board board;
    Player player1, player2;
    Player* currentPlayer;
    bool isGameOver;

    void SwitchTurn();
    void CheckWinner();
public:
    Speed_Mode();
    ~Speed_Mode();

    void InitGame(std::string name1, std::string name2) override;
    Player* CurrentTurn() override;
    Player* PreviousTurn() override;
    void PlayGame() override;
    void ResetGame() override;

    void TimerBasedPlay();
};
*/
