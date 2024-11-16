#include "Game.h"
enum class WizardAbility {
    RemoveOpponentCard,
    RemoveRow,
    CoverOpponentCard,
    CreatePit,
    MoveOwnStack,
    ExtraEterCard,
    MoveOpponentStack,
    MoveEdgeRow
};
class Wizard_Card {
private:
    WizardAbility ability;
    bool isUsed;
public:
    Wizard_Card(WizardAbility abilityType);
    WizardAbility GetAbilityType() const;
    void ActivateAbility(Game* gameInstance, int row = -1, int col = -1);
    bool IsUsed() const;
};
