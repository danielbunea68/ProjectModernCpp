#ifndef COMBINED_MODE_H
#define COMBINED_MODE_H

#include "Game.h"
#include "Wizard_Mode.h"
#include "Element_Mode.h"

class Combined_Mode : public Game 
{
private:
    Wizard_Mode wizardGame;
    Element_Mode elementGame;
    Board unifiedBoard;
    int totalRounds;

public:
    Combined_Mode();
    void InitGame(std::string name1, std::string name2) override;
    void PlayGame() override;
    void SwitchTurn();
    Player* CurrentTurn() override;
    void ResetGame() override;
};

#endif // COMBINED_MODE_H
