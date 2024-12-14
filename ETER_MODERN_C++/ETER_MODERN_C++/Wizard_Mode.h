#pragma once
#include "Player.h"
#include "Board.h"
#include "IGame.h"
#include <string>


class Wizard_Mode : public IGame 
{

private :
    Board board;
    Player player1, player2;
    Player* currentPlayer;
    int player1Wins = 0, player2Wins = 0;

    void removeOpponentCard(int row, int col);
    void removeRow(int row);
    void coverOpponentCard(int row, int col);
    void createPit(int row, int col);
    void moveOwnStack(int fromRow, int fromCol, int toRow, int toCol);
    void grantExtraEterCard(int row ,int col);
    void moveOpponentStack(int fromRow, int fromCol, int toRow, int toCol);
    void moveEdgeRow(int row);

    std::string GetWizardPowerName(WizardPower power);
    void SwitchTurn();

public :
    Wizard_Mode();

    ~Wizard_Mode();

    Wizard_Mode(const Wizard_Mode& other);

    Wizard_Mode& operator=(const Wizard_Mode& other);

    Wizard_Mode& operator=(Wizard_Mode&& other) noexcept;

    Wizard_Mode(Wizard_Mode&& other) noexcept;

    void ActivatePower(WizardPower power);

    void RemoveCard(int row, int col) override;

    void ReturnCardToPlayer(int row, int col)override;

    void CreatePit(int row, int col)override;

    void InitGame(std::string name1, std::string name2)override;

    Player* CurrentTurn() override;
    Player* PreviousTurn() override;

    void PlayGame()override;

    void ResetGame()override;

};
