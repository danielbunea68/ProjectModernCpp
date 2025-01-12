#pragma once

#include "Game.h"
#include "Wizard_Mode.h"
#include "Element_Mode.h"

class Combined_Mode : public IGame
{
private:
    Player player1;
    Player player2;
    Player* currentPlayer;
    Board board;
    int totalRounds;
    Element_Mode elementgame;

    bool player1UsedAnyPower;
    bool player2UsedAnyPower;

    std::vector<Element_Mode::Putere> elementPowers;

    void InitializeWizardPowers();
    void InitializeElementPowers();
    bool PlayCardAction();
    bool UsePower();

public:
    Combined_Mode();

    void InitGame(std::string name1, std::string name2) override;
    void PlayGame() override;
    void SwitchTurn();
    Player* CurrentTurn() override;
    void ResetGame() override;

    // Additional methods required by IGame
    void RemoveCard(int row, int col) override;
    void ReturnCardToPlayer(int row, int col) override;
    void CreatePit(int row, int col) override;
    Player* PreviousTurn() override;
    std::string GetWizardPowerName(WizardPower power);
    void ActivatePower(WizardPower power);
    void removeOpponentCard(int row, int col);
    void removeRow(int row);
    void coverOpponentCard(int row, int col);
    void createPit(int row, int col);
    void moveOwnStack(int fromRow, int fromCol, int toRow, int toCol);
    void grantExtraEterCard(int row, int col);
    void moveOpponentStack(int fromRow, int fromCol, int toRow, int toCol);
    void moveEdgeRow(int row);
};
