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
    std::unordered_set<Element_Mode::Putere> usedPowers;

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

    void RemoveCard(int row, int col) override;
    void ReturnCardToPlayer(int row, int col) override;
    void CreatePit(int row, int col) override;
    Player* PreviousTurn() override;

    //Functii wizard mode

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

    //Functii element mode

    std::string GetPowerName(Element_Mode::Putere power);
    std::string GetPowerDescription(Element_Mode::Putere power);
    bool CanUsePower(Element_Mode::Putere power);
    void UsePower1(Element_Mode::Putere power);
    void ActivatePower1(Element_Mode::Putere power);
    void ActivateControlledExplosion();
    void  DestroyLastOpponentCard();
    void Flacari();
    void Lava();
    void DinCenusa();
    void Scantei();
    void Viscol();
    void Vijelie();
    void ActivateRafala(int row, int col, int targetRow, int targetCol);
    void ActivateMiraj(int cardIndex);
    void ActivateFurtuna();
    void Uragan(int row);
    void SwapStacks();
    void Ceata();
    void Val();
};
