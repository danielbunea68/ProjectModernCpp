#include "Combined_Mode.h"
#include "Element_Mode.h"
#include "Wizard_Mode.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <random>

Combined_Mode::Combined_Mode()
    : totalRounds(5), currentPlayer(nullptr), player1UsedAnyPower(false), player2UsedAnyPower(false) {}

void Combined_Mode::InitGame(std::string name1, std::string name2) {
    const int BOARD_SIZE = 4;
    const int INITIAL_ROUNDS = 5;

    // Initialize players
    player1.setName(name1);
    player2.setName(name2);
    player1.setColor("red");
    player2.setColor("blue");

    // Initialize cards for both players
    std::vector<int> values = { 1, 1, 2, 2, 2, 3, 3, 3, 4 };
    for (int value : values) {
        player1.AddCard(Card(value, player1.getColor()));
        player2.AddCard(Card(value, player2.getColor()));
    }
    player1.AddCard(Card(5, player1.getColor(), "Eter"));
    player2.AddCard(Card(5, player2.getColor(), "Eter"));

    // Initialize the board
    board.SetSize(BOARD_SIZE);

    wizardgame = Wizard_Mode();
    elementgame = Element_Mode();

    // Initialize powers
    InitializeWizardPowers();
    InitializeElementPowers();

    currentPlayer = &player1;
    totalRounds = INITIAL_ROUNDS;
}

void Combined_Mode::PlayGame() {
    while (totalRounds > 0) {
        bool player1ActionDone = false;
        bool player2ActionDone = false;

        while (!player1ActionDone || !player2ActionDone) {
            board.Display();
            std::cout << "Round " << (6 - totalRounds) << " begins!\n";
            currentPlayer->ShowHand();

            bool validChoice = false;
            while (!validChoice) {
                std::cout << currentPlayer->getName() << ", choose an action:\n";
                std::cout << "1. Play card\n2. Use Power\n";
                int choice;
                std::cin >> choice;

                switch (choice) {
                case 1:
                    validChoice = PlayCardAction();
                    break;
                case 2:
                    validChoice = UsePower();
                    break;
                default:
                    std::cout << "Invalid choice. Try again.\n";
                    break;
                }
            }

            // Mark player's turn as done
            if (currentPlayer == &player1) {
                player1ActionDone = true;
            }
            else {
                player2ActionDone = true;
            }

            SwitchTurn();  // Switch turns after a valid move
        }

        totalRounds--;
    }
    std::cout << "Game over! No more rounds.\n";
}


bool Combined_Mode::PlayCardAction() 
{
    int cardIndex;
    do {
        std::cout << currentPlayer->getName() << ", choose a card index to play: ";
        std::cin >> cardIndex;
    } while (!currentPlayer->HasCardAtIndex(cardIndex));

    Card chosenCard = currentPlayer->PlayCard(cardIndex);

    if (currentPlayer->CanPlaceCardFaceDown()) {
        char answer;
        std::cout << "Do you want to play this card face down? y/[n]: ";
        std::cin >> answer;
        if (answer == 'y') {
            currentPlayer->PlayedCardFaceDown();
            chosenCard.setFaceDown(true);
        }
    }

    int row, col;
    int result;
    do {
        std::cout << "Enter row and column (0, 1, 2, or 3): ";
        std::cin >> row >> col;
        result = board.CanMakeMove(row, col, chosenCard);
    } while (result == 0);

    if (result == 1) {
        board.MakeMove(row, col, chosenCard);
        return true;
    }

    return false;
}

bool Combined_Mode::UsePower() {
    bool& currentPlayerUsedPower = (currentPlayer == &player1) ? player1UsedAnyPower : player2UsedAnyPower;

    if (currentPlayerUsedPower) {
        std::cout << "You have already used a power this turn.\n";
        return false;
    }

    std::cout << "Choose a power:\n";
    std::cout << "1. Wizard Power\n2. Element Power\n";
    int powerChoice;

    while (!(std::cin >> powerChoice) || (powerChoice != 1 && powerChoice != 2)) {
        std::cout << "Invalid choice. Please enter 1 or 2: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (powerChoice == 1) 
    {
        char confirmChoice;
        std::cout << "Are you sure you want to use your Wizard Power? (y/n): ";
        std::cin >> confirmChoice;

        if (confirmChoice == 'y' || confirmChoice == 'Y') 
        {
            std::cout << "Activating Wizard Power...\n"; 
            WizardPower power = currentPlayer->getWizardPower(); 
            std::cout << "Current Wizard Power: " << wizardgame.GetWizardPowerName(power) << "\n";

            wizardgame.ActivatePower(power);

            currentPlayerUsedPower = true;
            std::cout << currentPlayer->getName() << " has used their Wizard Power.\n";
            return true;
        }
        else {
            std::cout << "Canceled using Wizard Power.\n";
            return false;
        }
    }
    else if (powerChoice == 2 && !elementPowers.empty()) {
        char useElementPower;
        std::cout << currentPlayer->getName() << ", do you want to use your Element Power this turn? y/[n]: ";
        std::cin >> useElementPower;

        if (useElementPower == 'y' || useElementPower == 'Y') {
            while (true) {
                std::cout << "Choose an Element Power to apply (or enter 0 to exit):\n";
                for (size_t i = 0; i < elementPowers.size(); ++i) {
                    std::cout << i + 1 << ": " << elementgame.GetPowerName(elementPowers[i])
                        << "\n - " << elementgame.GetPowerDescription(elementPowers[i]) << "\n";
                }

                int chosenElementPowerIndex;
                std::cout << "Enter the number of the power you want to use: ";
                std::cin >> chosenElementPowerIndex;

                if (chosenElementPowerIndex == 0) {
                    std::cout << "Exiting Element Power menu.\n";
                    return false;  // Return to action menu
                }

                if (chosenElementPowerIndex >= 1 && chosenElementPowerIndex <= elementPowers.size()) {
                    Element_Mode::Putere selectedElementPower = elementPowers[chosenElementPowerIndex - 1];

                    if (elementgame.CanUsePower(selectedElementPower)) {
                        std::cout << "Activating Element Power: "
                            << elementgame.GetPowerName(selectedElementPower) << "\n";
                        elementgame.ActivatePower(selectedElementPower);
                        elementgame.UsePower(selectedElementPower);

                        elementPowers.erase(elementPowers.begin() + (chosenElementPowerIndex - 1));
                        currentPlayerUsedPower = true;
                        std::cout << currentPlayer->getName() << " has used their Element Power.\n";
                        return true;
                    }
                    else {
                        std::cout << "You cannot use this Element Power right now.\n";
                    }
                }
                else {
                    std::cout << "Invalid choice! Please select a valid Element Power.\n";
                }
            }
        }
        else {
            std::cout << "Skipped using Element Power.\n";
            return false;  // Return to action menu
        }
    }
    else {
        std::cout << "No Element Powers left to use.\n";
        return false;
    }
}



void Combined_Mode::SwitchTurn() {
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}

void Combined_Mode::InitializeWizardPowers() 
{
    player1.setRandomWizardPower();
    player2.setRandomWizardPower();
    std::cout << player1.getName() << "'s Wizard Power: " << wizardgame.GetWizardPowerName(player1.getWizardPower()) << "\n";
    std::cout << player2.getName() << "'s Wizard Power: " << wizardgame.GetWizardPowerName(player2.getWizardPower()) << "\n";
}

void Combined_Mode::InitializeElementPowers() 
{
    std::vector<Element_Mode::Putere> allPowers = {
        Element_Mode::Putere::ExplozieControlata, Element_Mode::Putere::Distrugere,
        Element_Mode::Putere::Flacari, Element_Mode::Putere::Lava,
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(allPowers.begin(), allPowers.end(), gen);

    elementPowers = { allPowers[0], allPowers[1] };
    std::cout << "Element Powers initialized: ";
    for (const auto& power : elementPowers) {
        std::cout << elementgame.GetPowerName(power) << " ";
    }
    std::cout << "\n";
}

void Combined_Mode::ResetGame() {
    // Reset both wizardGame and elementGame
    wizardgame.ResetGame(); 
    elementgame.ResetGame(); 

    // Reset Combined_Mode specific settings
    board.Clear();
    player1.ClearCards();
    player2.ClearCards();
    totalRounds = 0;
    InitGame(player1.getName(), player2.getName());
    std::cout << "Combined Mode game has been reset.\n";
}

void Combined_Mode::RemoveCard(int row, int col) {
    if (!board.IsEmpty(row, col)) {
        board.Remove(row, col);
        std::cout << "Card removed from position (" << row << ", " << col << ").\n";
    }
    else {
        std::cout << "No card to remove at position (" << row << ", " << col << ").\n";
    }
}

void Combined_Mode::ReturnCardToPlayer(int row, int col) {
    if (!board.IsEmpty(row, col)) {
        Card card = board.TopCard(row, col);
        board.Remove(row, col);

        if (card.getColor() == currentPlayer->getColor()) {
            currentPlayer->AddCard(card);
            std::cout << "Card returned to " << currentPlayer->getName() << "'s hand.\n";
        }
        else {
            Player* otherPlayer = (currentPlayer == &player1) ? &player2 : &player1;
            otherPlayer->AddCard(card);
            std::cout << "Card returned to " << otherPlayer->getName() << "'s hand.\n";
        }
    }
    else {
        std::cout << "No card to return at position (" << row << ", " << col << ").\n";
    }
}

void Combined_Mode::CreatePit(int row, int col) {
    if (!board.IsValidPosition(row, col)) {
        std::cout << "Cannot create pit at (" << row << ", " << col << "). Invalid position.\n";
        return;
    }

    if (board.IsBlockedCell(row, col)) {
        std::cout << "Cannot create pit at (" << row << ", " << col << "). This cell is already a pit.\n";
        return;
    }

    while (!board.IsEmpty(row, col)) {
        board.Remove(row, col);
    }

    board.BlockCell(row, col);
    std::cout << "Pit created at position (" << row << ", " << col << ").\n";
}

Player* Combined_Mode::CurrentTurn() {
    return currentPlayer; // Assumes currentPlayer is maintained properly during gameplay
}

Player* Combined_Mode::PreviousTurn() {
    if (currentPlayer == &player1) {
        return &player2;
    }
    else {
        return &player1;
    }
}