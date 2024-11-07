#pragma once
#include "Game.h"
#include "Player.h"

enum class WizardPower {
    RemoveOpponentCard,
    RemoveRow,
    CoverOpponentCard,
    CreatePit,
    MoveOwnStack,
    ExtraEterCard,
    MoveOpponentStack,
    MoveEdgeRow
};

class Wizard_Mode : public Game {
private:
    void removeOpponentCard(int row, int col);
    void removeRow(int row);
    void coverOpponentCard(int row, int col);
    void createPit(int row, int col);
    void moveOwnStack(int row, int col);
    void grantExtraEterCard();
    void moveOpponentStack(int row, int col);
    void moveEdgeRow(int row);

public:
    void activatePower(WizardPower power, int row = -1, int col = -1);
};