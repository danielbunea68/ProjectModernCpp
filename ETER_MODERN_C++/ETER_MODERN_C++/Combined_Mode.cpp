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

    player1.setName(name1);
    player2.setName(name2);
    player1.setColor("red");
    player2.setColor("blue");

    std::vector<int> values = { 1, 1, 2, 2, 2, 3, 3, 3, 4 };
    for (int value : values) {
        player1.AddCard(Card(value, player1.getColor()));
        player2.AddCard(Card(value, player2.getColor()));
    }
    player1.AddCard(Card(5, player1.getColor(), "Eter"));
    player2.AddCard(Card(5, player2.getColor(), "Eter"));

    board.SetSize(BOARD_SIZE);

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
            std::cout << "Current Wizard Power: " << GetWizardPowerName(power) << "\n";

            ActivatePower(power);

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
                    std::cout << i + 1 << ": " << GetPowerName(elementPowers[i])
                        << "\n - " << GetPowerDescription(elementPowers[i]) << "\n";
                } 

                int chosenElementPowerIndex;
                std::cout << "Enter the number of the power you want to use: ";
                std::cin >> chosenElementPowerIndex;

                if (chosenElementPowerIndex == 0) {
                    std::cout << "Exiting Element Power menu.\n";
                    return false;
                }

                if (chosenElementPowerIndex >= 1 && chosenElementPowerIndex <= elementPowers.size()) {
                    Element_Mode::Putere selectedElementPower = elementPowers[chosenElementPowerIndex - 1];

                    if (CanUsePower(selectedElementPower)) {
                        std::cout << "Activating Element Power: "
                            << GetPowerName(selectedElementPower) << "\n";
                        ActivatePower(selectedElementPower);
                        UsePower(selectedElementPower);

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
            return false;
        }
    }
    else {
        std::cout << "No Element Powers left to use.\n";
        return false;
    }
}



void Combined_Mode::SwitchTurn() 
{
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}

void Combined_Mode::InitializeWizardPowers() 
{
    player1.setRandomWizardPower();
    player2.setRandomWizardPower();
    std::cout << player1.getName() << "'s Wizard Power: " <<GetWizardPowerName(player1.getWizardPower()) << "\n";
    std::cout << player2.getName() << "'s Wizard Power: " <<GetWizardPowerName(player2.getWizardPower()) << "\n";
}

void Combined_Mode::InitializeElementPowers() 
{
    std::vector<Element_Mode::Putere> allPowers = {
    Element_Mode::Putere::ExplozieControlata,
    Element_Mode::Putere::Distrugere,
    Element_Mode::Putere::Flacari,
    Element_Mode::Putere::Lava,
    Element_Mode::Putere::DinCenusa,
    Element_Mode::Putere::Scantei,
    Element_Mode::Putere::Viscol,
    Element_Mode::Putere::Vijelie,
    Element_Mode::Putere::Uragan,
    Element_Mode::Putere::Rafala,
    Element_Mode::Putere::Miraj,
    Element_Mode::Putere::Furtuna,
    Element_Mode::Putere::Maree,
    Element_Mode::Putere::Ceata,
    Element_Mode::Putere::Val,
    Element_Mode::Putere::VartejDeApa,
    Element_Mode::Putere::Tsunami,
    Element_Mode::Putere::Cascada,
    Element_Mode::Putere::Sprijin,
    Element_Mode::Putere::Cutremur,
    Element_Mode::Putere::Sfaramare,
    Element_Mode::Putere::Granite,
    Element_Mode::Putere::Avalansa,
    Element_Mode::Putere::Bolovan
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(allPowers.begin(), allPowers.end(), gen);

    elementPowers = { allPowers[0], allPowers[1] };
    std::cout << "Element Powers initialized: ";

    for (size_t i = 0; i < elementPowers.size(); ++i)
    {
        std::cout << GetPowerName(elementPowers[i]);
        if (i != elementPowers.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}

void Combined_Mode::ResetGame() 
{
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
    return currentPlayer;
}

Player* Combined_Mode::PreviousTurn() {
    if (currentPlayer == &player1) {
        return &player2;
    }
    else {
        return &player1;
    }
}

std::string Combined_Mode::GetWizardPowerName(WizardPower power)
{
    switch (power)
    {
    case WizardPower::RemoveOpponentCard:
        return "RemoveOpponentCard";
    case WizardPower::RemoveRow:
        return "RemoveRow";
    case WizardPower::CoverOpponentCard:
        return "CoverOpponentCard";
    case WizardPower::CreatePit:
        return "CreatePit";
    case WizardPower::MoveOwnStack:
        return "MoveOwnStack";
    case WizardPower::ExtraEterCard:
        return "ExtraEterCard";
    case WizardPower::MoveOpponentStack:
        return "MoveOpponentStack";
    case WizardPower::MoveEdgeRow:
        return "MoveEdgeRow";
    default:
        return "Unknown Power";
    }
}

void Combined_Mode::ActivatePower(WizardPower power)
{
    switch (power)
    {
    case WizardPower::RemoveOpponentCard:
    {
        std::cout << currentPlayer->getName() << " used RemoveOpponentCard power!\n";
        int row, col;
        std::cout << "Enter the row and column of the opponent's card to remove: ";
        std::cin >> row >> col;

        removeOpponentCard(row, col);
        std::cout << "Removed the opponent's card at (" << row << ", " << col << ").\n";
        break;
    }

    case WizardPower::RemoveRow:
    {
        std::cout << currentPlayer->getName() << " used RemoveRow power!\n";
        int row1;
        std::cout << "Enter the row to remove: ";
        std::cin >> row1;

        removeRow(row1);
        std::cout << "Removed row " << row1 << ".\n";
        break;
    }

    case WizardPower::CoverOpponentCard:
    {
        std::cout << currentPlayer->getName() << " used CoverOpponentCard power!\n";
        int row2, col2;
        std::cout << "Enter the row and column of the opponent's card to cover: ";
        std::cin >> row2 >> col2;

        coverOpponentCard(row2, col2);
        std::cout << "Covered the opponent's card at (" << row2 << ", " << col2 << ").\n";
        break;
    }

    case WizardPower::CreatePit:
    {
        std::cout << currentPlayer->getName() << " used CreatePit power!\n";
        int row3, col3;
        std::cout << "Enter the row and column to create a pit: ";
        std::cin >> row3 >> col3;

        createPit(row3, col3);
        std::cout << "Created a pit at (" << row3 << ", " << col3 << ").\n";
        break;
    }

    case WizardPower::MoveOwnStack:
    {
        std::cout << currentPlayer->getName() << " used MoveOwnStack power!\n";

        int fromRow1, fromCol1;
        std::cout << "Enter the row and column of your stack to move: ";
        std::cin >> fromRow1 >> fromCol1;

        int toRow2, toCol2;
        std::cout << "Enter the row and column where you want to move the stack: ";
        std::cin >> toRow2 >> toCol2;

        moveOwnStack(fromRow1, fromCol1, toRow2, toCol2);
        break;
    }

    case WizardPower::ExtraEterCard:
    {
        std::cout << currentPlayer->getName() << " used ExtraEterCard power!\n";
        int row5, col5;
        std::cout << "Enter the row and column to grant an extra Eter card: ";
        std::cin >> row5 >> col5;

        grantExtraEterCard(row5, col5);
        std::cout << "Granted an extra Eter card at (" << row5 << ", " << col5 << ").\n";
        break;
    }

    case WizardPower::MoveOpponentStack:
    {
        std::cout << currentPlayer->getName() << " used MoveOpponentStack power!\n";

        int fromRow, fromCol;
        std::cout << "Enter the row and column of the opponent's stack to move: ";
        std::cin >> fromRow >> fromCol;

        int toRow, toCol;
        std::cout << "Enter the row and column where you want to move the stack: ";
        std::cin >> toRow >> toCol;

        moveOpponentStack(fromRow, fromCol, toRow, toCol);
        break;
    }

    case WizardPower::MoveEdgeRow:
    {
        std::cout << currentPlayer->getName() << " used MoveEdgeRow power!\n";
        int row7;
        std::cout << "Enter the edge row to move: ";
        std::cin >> row7;
        moveEdgeRow(row7);
        std::cout << "Moved edge row " << row7 << ".\n";
        break;
    }

    default:
        std::cout << "Unknown power.\n";
        break;
    }
}

void Combined_Mode::removeOpponentCard(int row, int col)
{
    if (!board.IsValidPosition(row, col) || board.IsEmpty(row, col) || board.TopCard(row, col).getColor() == currentPlayer->getColor()) 
    {
        std::cout << "Cannot remove card at (" << row << ", " << col << "). Invalid position or not an opponent's card.\n";
        return;
    }

    board.Remove(row, col); 
    std::cout << "Removed opponent's card at (" << row << ", " << col << ").\n";
}

void Combined_Mode::removeRow(int row)
{
    if (board.GetSize() > row) 
    {
        bool hasPlayerCard = false;
        for (int col = 0; col < board.GetSize(); ++col) 
        {
            if (!board.IsEmpty(row, col) && board.TopCard(row, col).getColor() == currentPlayer->getColor()) 
            {
                hasPlayerCard = true;
                break;
            }
        }
        if (hasPlayerCard) {
            for (int col = 0; col < board.GetSize(); ++col) {
                while (!board.IsEmpty(row, col)) {
                    RemoveCard(row, col);
                }
            }
            std::cout << "Row " << row << " removed.\n";
        }
    }
}

void Combined_Mode::coverOpponentCard(int row, int col)
{
    if (!board.IsValidPosition(row, col) || board.IsEmpty(row, col) || board.TopCard(row, col).getColor() == currentPlayer->getColor()) {
        std::cout << "Cannot cover card at (" << row << ", " << col << "). Invalid position or not an opponent's card.\n";
        return;
    }

    currentPlayer->ShowHand();
    int cardIndex = -1;
    std::cout << "Choose a lower card from hand to cover opponent's card: ";
    while (!currentPlayer->HasCardAtIndex(cardIndex)) {
        std::cin >> cardIndex;
    }

    Card chosenCard = currentPlayer->PlayCard(cardIndex);
    if (chosenCard.getValue() < board.TopCard(row, col).getValue()) {
        board.AddCard(row, col, chosenCard);
        std::cout << "Covered opponent's card with " << chosenCard.getValue() << ".\n";
    }
    else {
        std::cout << "Cannot cover with card of equal or higher value.\n";
        currentPlayer->AddCard(chosenCard);
    }
}

void Combined_Mode::createPit(int row, int col)
{
    if (!board.IsValidPosition(row, col))
    {
        std::cout << "Cannot create pit at (" << row << ", " << col << "). Invalid position.\n";
        return;
    }

    if (board.IsBlockedCell(row, col))
    {
        std::cout << "Cannot create pit at (" << row << ", " << col << "). This cell is already a pit.\n";
        return;
    }

    auto& boardGrid = board.GetBoard();
    while (!board.IsEmpty(row, col))
    {
        boardGrid[row][col].pop();
    }

    board.BlockCell(row, col);

    std::cout << "Pit created at (" << row << ", " << col << "). All cards removed, and no cards can be placed here.\n";
}

void Combined_Mode::moveOwnStack(int fromRow, int fromCol, int toRow, int toCol)
{
    if (!board.IsValidPosition(fromRow, fromCol))
    {
        std::cout << "Invalid source position (" << fromRow << ", " << fromCol << ").\n";
        return;
    }

    if (board.IsEmpty(fromRow, fromCol))
    {
        std::cout << "There is no stack at the specified source position (" << fromRow << ", " << fromCol << ").\n";
        return;
    }

    if (board.TopCard(fromRow, fromCol).getColor() != currentPlayer->getColor())
    {
        std::cout << "The stack at (" << fromRow << ", " << fromCol << ") does not belong to you.\n";
        return;
    }

    if (!board.IsValidPosition(toRow, toCol))
    {
        std::cout << "Invalid destination position (" << toRow << ", " << toCol << ").\n";
        return;
    }

    if (!board.IsEmpty(toRow, toCol))
    {
        std::cout << "The destination position (" << toRow << ", " << toCol << ") is not empty.\n";
        return;
    }

    std::deque<Card> stack;

    while (!board.IsEmpty(fromRow, fromCol))
    {
        stack.push_back(board.TopCard(fromRow, fromCol));
        board.Remove(fromRow, fromCol);
    }

    while (!stack.empty()) {
        board.AddCard(toRow, toCol, stack.back());
        stack.pop_back();
    }

    std::cout << "Moved your stack from (" << fromRow << ", " << fromCol << ") to (" << toRow << ", " << toCol << ").\n";
}

void Combined_Mode::grantExtraEterCard(int row, int col)
{
    Card extraCard(5, currentPlayer->getColor(), "Eter");
    currentPlayer->AddCard(extraCard);
    board.MakeMove(row, col, extraCard);
}

void Combined_Mode::moveOpponentStack(int fromRow, int fromCol, int toRow, int toCol)
{
    if (board.IsEmpty(fromRow, fromCol))
    {
        std::cout << "There is no stack at the specified source position (" << fromRow << ", " << fromCol << ").\n";
        return;
    }

    if (board.TopCard(fromRow, fromCol).getColor() == currentPlayer->getColor())
    {
        std::cout << "You cannot move your own stack!\n";
        return;
    }

    if (!board.IsEmpty(toRow, toCol))
    {
        std::cout << "The destination position (" << toRow << ", " << toCol << ") is not empty.\n";
        return;
    }

    std::deque<Card> tempStack;

    while (!board.IsEmpty(fromRow, fromCol))
    {
        Card topCard = board.TopCard(fromRow, fromCol);
        RemoveCard(fromRow, fromCol);
        tempStack.push_back(topCard);
    }

    while (!tempStack.empty())
    {
        board.AddCard(toRow, toCol, tempStack.back());
        tempStack.pop_back();
    }
    std::cout << "Moved stack from (" << fromRow << ", " << fromCol << ") to (" << toRow << ", " << toCol << ").\n";
}

void Combined_Mode::moveEdgeRow(int row)
{
    int newRow;
    std::cout << "Enter the new edge row position: ";
    std::cin >> newRow;

    if (board.GetSize() > row && board.GetSize() > newRow && row != newRow) {
        for (int col = 0; col < board.GetSize(); ++col) {
            if (!board.IsEmpty(row, col)) {
                Card card = board.TopCard(row, col);
                RemoveCard(row, col);
                board.MakeMove(newRow, col, card);
            }
        }
        std::cout << "Moved row " << row << " to edge row " << newRow << ".\n";
    }
}

std::string Combined_Mode::GetPowerName(Element_Mode::Putere power)
{
    switch (power)
    {
    case Element_Mode::Putere::ExplozieControlata: return "Explozie Controlată";
    case Element_Mode::Putere::Distrugere:        return "Distrugere";
    case Element_Mode::Putere::Flacari:           return "Flăcări";
    case Element_Mode::Putere::Lava:              return "Lava";
    case Element_Mode::Putere::DinCenusa:        return "Din Cenușă";
    case Element_Mode::Putere::Scantei:           return "Scântei";
    case Element_Mode::Putere::Viscol:            return "Viscol";
    case Element_Mode::Putere::Vijelie:           return "Vijelie";
    case Element_Mode::Putere::Uragan:            return "Uragan";
    case Element_Mode::Putere::Rafala:            return "Rafală";
    case Element_Mode::Putere::Miraj:             return "Miraj";
    case Element_Mode::Putere::Furtuna:           return "Furtună";
    case Element_Mode::Putere::Maree:             return "Maree";
    case Element_Mode::Putere::Ceata:             return "Ceață";
    case Element_Mode::Putere::Val:               return "Val";
    case Element_Mode::Putere::VartejDeApa:      return "Vârtej de Apă";
    case Element_Mode::Putere::Tsunami:           return "Tsunami";
    case Element_Mode::Putere::Cascada:           return "Cascadă";
    case Element_Mode::Putere::Sprijin:           return "Sprijin";
    case Element_Mode::Putere::Cutremur:          return "Cutremur";
    case Element_Mode::Putere::Sfaramare:         return "Sfărâmare";
    case Element_Mode::Putere::Granite:           return "Granițe";
    case Element_Mode::Putere::Avalansa:          return "Avalanșă";
    case Element_Mode::Putere::Bolovan:           return "Bolovan";
    default:                                       return "Necunoscută";
    }
}

std::string Combined_Mode::GetPowerDescription(Element_Mode::Putere power)
{
    switch (power)
    {
    case Element_Mode::Putere::ExplozieControlata:
        return "Detonates the board in a controlled manner, affecting specific areas.";
    case Element_Mode::Putere::Distrugere:
        return "Destroys the last card played by the opponent.";
    case Element_Mode::Putere::Flacari:
        return "Reveals the opponent's illusion and allows you to play an extra card.";
    case Element_Mode::Putere::Lava:
        return "Returns all visible cards of a chosen number to their owners.";
    case Element_Mode::Putere::DinCenusa:
        return "Instantly revives and plays one of your eliminated cards.";
    case Element_Mode::Putere::Scantei:
        return "Relocates one of the opponent's hidden cards to another position.";
    case Element_Mode::Putere::Viscol:
        return "Sends a visible opponent card back to their hand.";
    case Element_Mode::Putere::Vijelie:
        return "Returns all covered (face-down) cards to their owners.";
    case Element_Mode::Putere::Uragan:
        return "Shifts an entire fully occupied row to a new position.";
    case Element_Mode::Putere::Rafala:
        return "Moves a visible card next to a card with a smaller number.";
    case Element_Mode::Putere::Miraj:
        return "Swaps your placed illusion with another illusion.";
    case Element_Mode::Putere::Furtuna:
        return "Removes from play any stack containing two or more cards.";
    case Element_Mode::Putere::Maree:
        return "Swaps the positions of two stacks of cards.";
    case Element_Mode::Putere::Ceata:
        return "Allows you to play another illusion.";
    case Element_Mode::Putere::Val:
        return "Moves a stack to an adjacent empty spot and lets you play a card on the newly freed space.";
    case Element_Mode::Putere::VartejDeApa:
        return "Pulls two cards separated by an empty space into that space.";
    case Element_Mode::Putere::Tsunami:
        return "Blocks a row for the opponent during their next turn.";
    case Element_Mode::Putere::Cascada:
        return "Collapses a row of stacks towards an edge, forming a new stack.";
    case Element_Mode::Putere::Sprijin:
        return "Increases the value of one of your cards (1/2/3) by 1.";
    case Element_Mode::Putere::Cutremur:
        return "Removes all visible cards with the value 1 from the board.";
    case Element_Mode::Putere::Sfaramare:
        return "Decreases the value of an opponent's card (2/3/4) by 1.";
    case Element_Mode::Putere::Granite:
        return "Places a neutral card that defines a boundary.";
    case Element_Mode::Putere::Avalansa:
        return "Shifts two adjacent stacks together.";
    case Element_Mode::Putere::Bolovan:
        return "Covers an illusion without revealing it.";
    default:
        return "Unknown power.";
    }

}





