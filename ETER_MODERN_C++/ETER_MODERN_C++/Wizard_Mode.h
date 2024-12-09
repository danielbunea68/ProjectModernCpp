
#pragma once
#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "IGame.h"

#include <unordered_set>
#include <vector>
#include <string>
#include<random>

class Wizard_Mode : public IGame 
{

public:

    enum class WizardPower 
    {
    RemoveOpponentCard,
    RemoveRow,
    CoverOpponentCard,
    CreatePit,
    MoveOwnStack,
    ExtraEterCard,
    MoveOpponentStack,
    MoveEdgeRow
    };


private :
    Board board;
    Player player1, player2;
    Player* currentPlayer;
    WizardPower tipPutere;     
    WizardPower currentPower;
    std::unordered_set<WizardPower> usedPowers; 
    std::vector<WizardPower> availablePowers;
    WizardPower player1Power; 
    WizardPower player2Power;

    void removeOpponentCard(int row, int col);
    void removeRow(int row);
    void coverOpponentCard(int row, int col);
    void createPit(int row, int col);
    void moveOwnStack(int row, int col);
    void grantExtraEterCard(int row ,int col);
    void moveOpponentStack(int row, int col);
    void moveEdgeRow(int row);

    void SwitchTurn();

    void InitializeWizardPowers();
    void AssignPowerToPlayer();
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
