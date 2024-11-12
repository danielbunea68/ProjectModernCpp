#include "Wizard_Card.h"
#include <iostream>

Wizard_Card::Wizard_Card(WizardAbility abilityType) : ability(abilityType), isUsed(false) {}

WizardAbility Wizard_Card::GetAbilityType() const {
    return ability;
}

bool Wizard_Card::IsUsed() const {
    return isUsed;
}

void Wizard_Card::ActivateAbility(Game* gameInstance, int row, int col) {
    if (isUsed) {
        std::cout << "Ability has already been used.\n";
        return;
    }

    switch (ability) {
        case WizardAbility::RemoveOpponentCard:
            gameInstance->RemoveCard(row, col);
            std::cout << "Removed opponent's card at (" << row << ", " << col << ").\n";
            break;
        case WizardAbility::RemoveRow:
            std::cout << "Removed row " << row << ".\n";
            break;
        case WizardAbility::CoverOpponentCard:
            std::cout << "Covered opponent's card at (" << row << ", " << col << ").\n";
            break;
        case WizardAbility::CreatePit:
            gameInstance->CreatePit(row, col);
            std::cout << "Created pit at (" << row << ", " << col << ").\n";
            break;
        case WizardAbility::MoveOwnStack:
            std::cout << "Moved own stack from (" << row << ", " << col << ").\n";
            break;
        case WizardAbility::ExtraEterCard:
            std::cout << "Granted an extra Eter card.\n";
            break;
        case WizardAbility::MoveOpponentStack:
            std::cout << "Moved opponent's stack from (" << row << ", " << col << ").\n";
            break;
        case WizardAbility::MoveEdgeRow:
            std::cout << "Moved edge row.\n";
            break;
    }

    isUsed = true;
    std::cout << "Ability activated!\n";
}