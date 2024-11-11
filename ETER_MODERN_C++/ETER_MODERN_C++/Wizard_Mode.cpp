#include "Wizard_Mode.h"
#include "Board.h"
#include <iostream>


// Dai override doar la metoda AfterInitialization

void Wizard_Mode::removeOpponentCard(int row, int col) {
    if (!board.IsEmpty(row, col) && board.TopCard(row, col).getColor() != currentPlayer->getColor()) {
        RemoveCard(row, col);
        std::cout << "Opponent's card removed from (" << row << ", " << col << ").\n";
    }
}


void Wizard_Mode::removeRow(int row) {
    if (board.GetSize() > row) {
        bool hasPlayerCard = false;
        for (int col = 0; col < board.GetSize(); ++col) {
            if (!board.IsEmpty(row, col) && board.TopCard(row, col).getColor() == currentPlayer->getColor()) {
                hasPlayerCard = true;
                break;
            }
        }
        if (hasPlayerCard) {
            for (int col = 0; col < board.GetSize(); ++col) {
                if (!board.IsEmpty(row, col)) {
                    RemoveCard(row, col);
                }
            }
            std::cout << "Row " << row << " removed.\n";
        }
    }
}


void Wizard_Mode::coverOpponentCard(int row, int col) {
    if (!board.IsEmpty(row, col) && board.TopCard(row, col).getColor() != currentPlayer->getColor()) {
        int cardIndex = -1;
        std::cout << "Choose a lower card from hand to cover opponent's card: ";
        while (!currentPlayer->HasCardAtIndex(cardIndex)) {
            std::cin >> cardIndex;
        }
        Card chosenCard = currentPlayer->PlayCard(cardIndex);
        if (chosenCard.getValue() < board.TopCard(row, col).getValue()) {
            board.MakeMove(row, col, chosenCard);
            std::cout << "Covered opponent's card with " << chosenCard.getValue() << ".\n";
        }
    }
}


void Wizard_Mode::createPit(int row, int col) {
    if (board.IsEmpty(row, col)) {
        CreatePit(row, col);
        std::cout << "Pit created at (" << row << ", " << col << ").\n";
    }
}


void Wizard_Mode::moveOwnStack(int row, int col) {
    if (!board.IsEmpty(row, col) && board.TopCard(row, col).getColor() == currentPlayer->getColor()) {
        int newRow, newCol;
        std::cout << "Enter new row and column to move stack: ";
        std::cin >> newRow >> newCol;
        if (board.IsEmpty(newRow, newCol)) {
            Card topCard = board.TopCard(row, col);
            RemoveCard(row, col);
            board.MakeMove(newRow, newCol, topCard);
            std::cout << "Moved stack to (" << newRow << ", " << newCol << ").\n";
        }
    }
}


void Wizard_Mode::grantExtraEterCard() {
    Card extraCard(5, currentPlayer->getColor(), "Eter");
    currentPlayer->AddCard(extraCard);
    std::cout << "Extra Eter card added.\n";
    int row, col;
    std::cout << "Place the extra Eter card. Enter row and column: ";
    std::cin >> row >> col;
    board.MakeMove(row, col, extraCard);
}


void Wizard_Mode::moveOpponentStack(int row, int col) {
    if (!board.IsEmpty(row, col) && board.TopCard(row, col).getColor() != currentPlayer->getColor()) {
        int newRow, newCol;
        std::cout << "Enter new row and column to move opponent's stack: ";
        std::cin >> newRow >> newCol;
        if (board.IsEmpty(newRow, newCol)) {
            Card topCard = board.TopCard(row, col);
            RemoveCard(row, col);
            board.MakeMove(newRow, newCol, topCard);
            std::cout << "Moved opponent's stack to (" << newRow << ", " << newCol << ").\n";
        }
    }
}

void Wizard_Mode::moveEdgeRow(int row) {
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

void Wizard_Mode::activatePower(WizardPower power, int row, int col) {
    if (currentPlayer->powerUsed) {
        std::cout << "Wizard power has already been used.\n";
        return;
    }

    switch (power) {
        case WizardPower::RemoveOpponentCard:
            removeOpponentCard(row, col);
            break;
        case WizardPower::RemoveRow:
            removeRow(row);
            break;
        case WizardPower::CoverOpponentCard:
            coverOpponentCard(row, col);
            break;
        case WizardPower::CreatePit:
            createPit(row, col);
            break;
        case WizardPower::MoveOwnStack:
            moveOwnStack(row, col);
            break;
        case WizardPower::ExtraEterCard:
            grantExtraEterCard();
            break;
        case WizardPower::MoveOpponentStack:
            moveOpponentStack(row, col);
            break;
        case WizardPower::MoveEdgeRow:
            moveEdgeRow(row);
            break;
    }

    currentPlayer->powerUsed = true;
    std::cout << "Wizard power activated!\n";
}
