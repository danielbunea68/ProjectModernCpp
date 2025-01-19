#pragma once

#include "Game.h"
#include "Wizard_Mode.h"
#include "Element_Mode.h"

class Combined_Mode : public IGame
{
private:
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    Player* currentPlayer = nullptr;
    Board board;
    int totalRounds;
    std::unordered_set<Element_Mode::Putere> usedPowers;
    int blockedRowForNextTurn = -1;

    bool player1UsedAnyPower;
    bool player2UsedAnyPower;

    std::vector<Element_Mode::Putere> elementPowers;

    void InitializeWizardPowers();
    void InitializeElementPowers();
    bool PlayCardAction();
    bool UsePower();

public:


    Combined_Mode();

    // Destructor
    ~Combined_Mode();

    // Constructor de copiere
    Combined_Mode(const Combined_Mode& other);

    // Operator de atribuire prin copiere
    Combined_Mode& operator=(const Combined_Mode& other);

    // Constructor de mutare
    Combined_Mode(Combined_Mode&& other) noexcept;

    // Operator de atribuire prin mutare
    Combined_Mode& operator=(Combined_Mode&& other) noexcept;



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
    void VartejDeApa();
    void ActivateTsunami();
    void Cutremur();
    void Cascada();
    void Sprijin();
    void Sfaramare();
    void Granita();
    void Avalansa(int row1, int col1, int row2, int col2);
    void Bolovan(int row, int col, int cardIndex);
};