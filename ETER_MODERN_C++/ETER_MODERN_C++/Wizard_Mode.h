
#pragma once
#include "Game.h"
#include "Player.h"
#include "Board.h"

#include "IGame.h"

class Wizard_Mode : public IGame {
private :
    Board board;
    Player player1, player2;
    Player* currentPlayer;

    void removeOpponentCard(int row, int col);
    void removeRow(int row);
    void coverOpponentCard(int row, int col);
    void createPit(int row, int col);
    void moveOwnStack(int row, int col);
    void grantExtraEterCard(int row ,int col);
    void moveOpponentStack(int row, int col);
    void moveEdgeRow(int row);

    void SwitchTurn();
public :
    Wizard_Mode();
    void RemoveCard(int row, int col) override;

    void ReturnCardToPlayer(int row, int col)override;

    void CreatePit(int row, int col)override;

    void InitGame(std::string name1, std::string name2)override;

    Player* CurrentTurn() override;
    Player* PreviousTurn() override;

    void PlayGame()override;

    void ResetGame()override;

    void activatePower(WizardPower power, int row = -1, int col = -1);


   
};
