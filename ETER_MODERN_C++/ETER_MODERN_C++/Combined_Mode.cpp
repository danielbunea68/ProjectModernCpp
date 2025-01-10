#include "Combined_Mode.h"
#include "Element_Mode.h"
#include <iostream>

Combined_Mode::Combined_Mode() : totalRounds(5) 
{
    unifiedBoard.SetSize(4);
}

void Combined_Mode::InitGame(std::string name1, std::string name2) {
    wizardGame.InitGame(name1, name2);
    elementGame.InitGame(name1, name2);
    elementGame.InitializePowers();
}

void Combined_Mode::PlayGame() {
    Player* currentPlayer = wizardGame.CurrentTurn();
    bool isGameOver = false;

    while (totalRounds > 0 && !isGameOver) 
    {
        std::cout << "\nRound " << (6 - totalRounds) << " begins!\n";
        unifiedBoard.Display();

        for (int i = 0; i < 2; ++i) {
            std::cout << currentPlayer->getName() << "'s turn.\n";

            std::cout << "Choose an action:\n";
            std::cout << "1. Play card\n2. Use Wizard power\n3. Use Element power\n";
            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1: {
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
                } while (result == 0); 

                if (result == 1) {
                    unifiedBoard.MakeMove(row, col, chosenCard);
                    unifiedBoard.Display();
                }
                else {
                    std::cout << "Invalid move. Try again.\n";
                }
                break;
            }
            case 2: {
                if (!currentPlayer->getPowerUsed()) {

                    char confirmChoice;
                    std::cout << "Are you sure you want to use your power? (y/n): ";
                    std::cin >> confirmChoice;

                    if (confirmChoice == 'y' || confirmChoice == 'Y') {

                        WizardPower power = currentPlayer->getWizardPower();
                        wizardGame.ActivatePower(power);

                        currentPlayer->setPowerUsed();

                        std::cout << currentPlayer->getName() << " has used their Wizard power.\n";
                    }
                    else {
                        std::cout << "Action canceled. Returning to the main menu.\n";
                    }
                }
                else {
                    std::cout << currentPlayer->getName() << " has already used their Wizard power this turn.\n";
                }
                break;
            }
            case 3: { 
                if (currentPlayer->getElementPowerUsed()) {
                    std::cout << currentPlayer->getName() << " has already used their Element power this turn.\n";
                    break;  
                }

                auto availablePowers = elementGame.GetAvailablePowers();
                if (availablePowers.empty()) {
                    std::cout << "No Element powers available to use.\n";
                    break; 
                }

                char usePower;
                std::cout << currentPlayer->getName() << ", do you want to use your Element power this turn? (y/n): ";
                std::cin >> usePower;

                if (usePower != 'y' && usePower != 'Y' && usePower != 'n' && usePower != 'N') {
                    std::cout << "Invalid choice. Exiting Element power menu.\n";
                    break;
                }

                if (usePower == 'y' || usePower == 'Y') {
                    while (true) {
                        int chosenPowerIndex = -1;
                        std::cout << "Choose an Element power to apply (or enter 0 to exit):\n";
                        for (size_t i = 0; i < availablePowers.size(); ++i) {
                            std::cout << i + 1 << ": " << elementGame.GetPowerName(availablePowers[i]) << "\n - " 
                                << elementGame.GetPowerDescription(availablePowers[i]) << "\n";
                        }

                        std::cout << "Enter the number of the power you want to use: ";
                        std::cin >> chosenPowerIndex;

                        if (chosenPowerIndex == 0) {
                            std::cout << "Exiting Element power menu.\n";
                            break;
                        }

                        if (chosenPowerIndex < 1 || chosenPowerIndex > availablePowers.size()) {
                            std::cout << "Invalid power choice! Please try again.\n";
                            continue;
                        }

                        Element_Mode::Putere selectedPower = availablePowers[chosenPowerIndex - 1];

                        if (elementGame.CanUsePower(selectedPower)) 
                        {
                            std::cout << currentPlayer->getName() << " is using the power: " << elementGame.GetPowerName(selectedPower) << "\n";

                            elementGame.ActivatePower(selectedPower);

                            currentPlayer->setElementPowerUsed(true);

                            availablePowers.erase(availablePowers.begin() + (chosenPowerIndex - 1));

                            std::cout << currentPlayer->getName() << " has used their Element power. Turn ends.\n";
                            break;
                        }
                        else {
                            std::cout << "You cannot use this Element power right now.\n";
                        }
                    }
                }
                else {
                    std::cout << "You chose not to use your Element power.\n";
                }
                break;
            }



            default:
                std::cout << "Invalid choice.\n";
            }

            SwitchTurn();
            currentPlayer = wizardGame.CurrentTurn();
        }

        totalRounds--;
    }

    if (!isGameOver) {
        std::cout << "The game ended without a decisive winner.\n";
    }
}


void Combined_Mode::SwitchTurn() 
{

    Player* currentWizardPlayer = wizardGame.CurrentTurn();
    Player* currentElementPlayer = elementGame.CurrentTurn();
    std::cout << "Switching turn from " << currentWizardPlayer->getName() << " and " << currentElementPlayer->getName() << "\n";

    wizardGame.SwitchTurn();
    elementGame.SwitchTurn();

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
