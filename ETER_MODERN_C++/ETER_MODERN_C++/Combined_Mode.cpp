#include "Combined_Mode.h"
#include <iostream>

Combined_Mode::Combined_Mode() : totalRounds(5) 
{
    unifiedBoard.SetSize(4); // Initialize a 4x4 board
}

void Combined_Mode::InitGame(std::string name1, std::string name2) {
    wizardGame.InitGame(name1, name2);
    elementGame.InitGame(name1, name2);
    elementGame.InitializePowers();
}

void Combined_Mode::PlayGame() {
    Player* currentPlayer = wizardGame.CurrentTurn();  // Get the first player (wizardGame's current turn)
    bool isGameOver = false;

    while (totalRounds > 0 && !isGameOver) {
        std::cout << "\nRound " << (6 - totalRounds) << " begins!\n";
        unifiedBoard.Display();

        // Let both players have their turn
        for (int i = 0; i < 2; ++i) {
            std::cout << currentPlayer->getName() << "'s turn.\n";

            std::cout << "Choose an action:\n";
            std::cout << "1. Play card\n2. Use Wizard power\n3. Use Element power\n";
            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1: { // Play a card
                currentPlayer->ShowHand();
                int cardIndex = -1;
                while (!currentPlayer->HasCardAtIndex(cardIndex)) {
                    std::cout << currentPlayer->getName() << ", choose a card index to play: ";
                    std::cin >> cardIndex;
                }

                Card chosenCard = currentPlayer->PlayCard(cardIndex);

                if (currentPlayer->CanPlaceCardFaceDown()) {
                    char answer = 'n';
                    std::cout << "Do you want to play this card face down? y/[n]\n";
                    std::cin >> answer;
                    if (answer == 'y') {
                        currentPlayer->PlayedCardFaceDown();
                        chosenCard.setFaceDown(true);
                    }
                }

                int row, col;
                int result;
                do {
                    std::cout << "Enter the row and column to place the card (0, 1, or 2).\n";
                    if (!unifiedBoard.IsDefinitiveBoard()) {
                        std::cout << "If the board is not definitive, you may also enter (-1, 3) to place the card in a special position.\n";
                    }

                    std::cin >> row >> col;
                    result = unifiedBoard.CanMakeMove(row, col, chosenCard);
                } while (result == 0);  // If the move is invalid, continue to ask for input

                if (result == 1) {
                    unifiedBoard.MakeMove(row, col, chosenCard);
                    unifiedBoard.Display();
                }
                else {
                    std::cout << "Invalid move. Try again.\n";
                }
                break;
            }
            case 2: { // Use Wizard power
                if (!currentPlayer->getPowerUsed()) {
                    wizardGame.ActivatePower(currentPlayer->getWizardPower());
                    currentPlayer->setPowerUsed();
                    std::cout << currentPlayer->getName() << " has used their Wizard power.\n";
                }
                else {
                    std::cout << currentPlayer->getName() << " has already used their Wizard power.\n";
                }
                break;
            }
            case 3: { // Use Element power
                if (!currentPlayer->getElementPowerUsed()) {
                    auto powers = elementGame.GetAvailablePowers();
                    if (!powers.empty()) {
                        elementGame.ActivatePower(powers[0]);
                        currentPlayer->setElementPowerUsed(true);
                        std::cout << currentPlayer->getName() << " has used their Element power.\n";
                    }
                }
                else {
                    std::cout << currentPlayer->getName() << " has already used their Element power.\n";
                }
                break;
            }
            default:
                std::cout << "Invalid choice.\n";
            }

            // Switch turn after player takes action
            SwitchTurn();
            currentPlayer = wizardGame.CurrentTurn();  // Update the current player after switching turn
        }

        // After both players have completed their turn, move to the next round
        totalRounds--;
    }

    if (!isGameOver) {
        std::cout << "The game ended without a decisive winner.\n";
    }
}


void Combined_Mode::SwitchTurn() {
    // Log the current players to see if the turn is switching correctly
    Player* currentWizardPlayer = wizardGame.CurrentTurn();
    Player* currentElementPlayer = elementGame.CurrentTurn();
    std::cout << "Switching turn from " << currentWizardPlayer->getName() << " and " << currentElementPlayer->getName() << "\n";

    // Switch turn in the wizard game and element game
    wizardGame.SwitchTurn();
    elementGame.SwitchTurn();

    // Log the new players after switching
    currentWizardPlayer = wizardGame.CurrentTurn();
    currentElementPlayer = elementGame.CurrentTurn();
    std::cout << "New turn: " << currentWizardPlayer->getName() << " and " << currentElementPlayer->getName() << "\n";
}


Player* Combined_Mode::CurrentTurn() {
    return wizardGame.CurrentTurn();
}

void Combined_Mode::ResetGame() {
    unifiedBoard.Clear();
    totalRounds = 5;
    wizardGame.ResetGame();
    elementGame.ResetGame();
}
