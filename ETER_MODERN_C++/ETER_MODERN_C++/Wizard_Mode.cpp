#include "Wizard_Mode.h"
#include "Board.h"
#include "IGame.h"
#include "Explosion_Card.h"
#include <iostream>


/*
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
*/

void Wizard_Mode::InitGame(std::string name1, std::string name2)
{
    player1.setName(name1);
    player2.setName(name2);
    board.SetSize(4);
    std::vector<int> values = { 1, 1, 2, 2, 2, 3, 3, 3, 4 };
    player1.setColor("red");
    player2.setColor("blue");
    for (const auto& value : values) {
        player1.AddCard(Card(value, player1.getColor()));
        player2.AddCard(Card(value, player2.getColor()));
    }
    player1.AddCard(Card(5, player1.getColor(), "Eter"));
    player2.AddCard(Card(5, player2.getColor(), "Eter"));

    player1.setRandomWizardPower();
    player2.setRandomWizardPower();
    currentPlayer = &player1;
}

Player* Wizard_Mode::CurrentTurn() const
{
    return currentPlayer;
}



void Wizard_Mode::SwitchTurn()
{
    if (currentPlayer->getName() == player1.getName())
    {
        currentPlayer = &player2;
    }
    else
    {
        currentPlayer = &player1;
    }
}

Wizard_Mode::Wizard_Mode()
{
    currentPlayer = NULL;
}

void Wizard_Mode::RemoveCard(int row, int col)
{
    board.Remove(row, col);
}

void Wizard_Mode::ReturnCardToPlayer(int row, int col)
{
    if (!board.IsEmpty(row, col))  // Check if there's a card to return
    {
        // Get the card from the board
        Card card = board.TopCard(row, col);
        board.Remove(row, col);  // Remove the card from the board

        if (card.getColor() == currentPlayer->getColor()) {
            currentPlayer->AddCard(card);
            std::cout << "Card returned to " << currentPlayer->getName() << "'s hand.\n";
        }
        else {
            // Return the card to the other player's hand
            Player* otherPlayer = (currentPlayer == &player1) ? &player2 : &player1;
            otherPlayer->AddCard(card);  // Add the card to the other player's hand
            std::cout << "Card returned to " << otherPlayer->getName() << "'s hand.\n";
        }
    }
    else
    {
        std::cout << "No card to return at position (" << row << ", " << col << ").\n";
    }
}

void Wizard_Mode::CreatePit(int row, int col)
{
    board.UpdateMarked(row, col);  // Mark the position as a pit

    // Now, remove all cards from that position using the getter function to access the internal board
    auto& boardGrid = board.GetBoard();  // Get a reference to the board
    while (!boardGrid[row][col].empty())
    {
        boardGrid[row][col].pop();  // Remove all cards from the stack at that position
    }

    std::cout << "Pit created at position (" << row << ", " << col << "). All cards removed.\n";
}

void Wizard_Mode::PlayGame()
{
    bool gameOver = false;
    while (!gameOver)
    {
        board.Display();
        currentPlayer->ShowHand();

     

        int cardIndex = -1;
        while (!currentPlayer->HasCardAtIndex(cardIndex))
        {
            std::cout << currentPlayer->getName() << ", choose a card index to play: ";
            std::cin >> cardIndex;
        }
        Card chosenCard = currentPlayer->PlayCard(cardIndex);

        if (currentPlayer->CanPlaceCardFaceDown()) {
            char answer = 'n';
            std::cout << "Do you want to play this card face down? y/[n]\n";
            std::cin >> answer;
            if (answer == 'y')
            {
                currentPlayer->PlayedCardFaceDown();
                chosenCard.setFaceDown(true);
            }
        }

        int row = -1, col = -1;
        int result = board.CanMakeMove(row, col, chosenCard);
        while (result == 0) {
            std::cout << "Enter row and column (0, 1, or 2) to place the card: ";
            std::cin >> row >> col;
            result = board.CanMakeMove(row, col, chosenCard);
        }
        if (result == 1)
        {
            board.MakeMove(row, col, chosenCard);
        }

        if (board.CheckIsBomb())//aici
        {
            Explosion_Card explosion_card(board.GetSize());
            explosion_card.activateExplosion();
            std::vector<std::pair<char, std::pair<int, int>>> coords;
            std::vector<std::pair<char, std::pair<int, int>>> left_coords;
            std::vector<std::pair<char, std::pair<int, int>>> right_coords;

            coords = explosion_card.AppliedPositions();

            for (const auto& pos : coords)
            {
                char bombType = pos.first;
                int row = pos.second.first;
                int col = pos.second.second;

                int right_r = col;
                int right_c = board.GetSize() - 1 - row;
                int left_r = board.GetSize() - 1 - col;
                int left_c = row;

                right_coords.push_back({ bombType, {right_r, right_c} });
                left_coords.push_back({ bombType, {left_r, left_c} });
            }
            std::cout << "pozitile aplicate pt dreapta: \n";
            for (const auto& pos : right_coords)
            {
                std::cout << pos.first << " " << pos.second.first << " " << pos.second.second << "\n";
            }
            std::cout << "pozitile aplicate pt stanga: \n";
            for (const auto& pos : left_coords)
            {
                std::cout << pos.first << " " << pos.second.first << " " << pos.second.second << "\n";
            }
            std::cout << "pozitile aplicate normal: \n";
            for (const auto& pos : coords)
            {
                std::cout << pos.first << " " << pos.second.first << " " << pos.second.second << "\n";
            }

            std::cout << " alege unde vrei sa pui : ";
            char c;
            std::cin >> c;

            switch (c)
            {
            case 'r':
                for (const auto& pos : right_coords)
                {
                    switch (pos.first)
                    {
                    case 'r':
                        std::cout << "Removing card at (" << pos.second.first << ", " << pos.second.second << ").\n";
                        RemoveCard(pos.second.first, pos.second.first);
                        break;
                    case 'u':
                        std::cout << "Returning card to player at (" << pos.second.first << ", " << pos.second.second << ").\n";
                        ReturnCardToPlayer(pos.second.first, pos.second.second);
                        break;
                    case 'p':
                        std::cout << "Creating pit at (" << pos.second.first << ", " << pos.second.second << ").\n";
                        CreatePit(pos.second.first, pos.second.second);
                        break;

                        break;
                    }
                }
                break;

            case 's':

                for (const auto& pos : left_coords)
                {
                    switch (pos.first)
                    {
                    case 'r':
                        std::cout << "Removing card at (" << pos.second.first << ", " << pos.second.second << ").\n";
                        RemoveCard(pos.second.first, pos.second.first);
                        break;
                    case 'u':
                        std::cout << "Returning card to player at (" << pos.second.first << ", " << pos.second.second << ").\n";
                        ReturnCardToPlayer(pos.second.first, pos.second.second);
                        break;
                    case 'p':
                        std::cout << "Creating pit at (" << pos.second.first << ", " << pos.second.second << ").\n";
                        CreatePit(pos.second.first, pos.second.second);
                        break;

                        break;
                    }
                }
                break;

            case 'n':
                for (const auto& pos : coords)
                {
                    switch (pos.first)
                    {
                    case 'r':
                        std::cout << "Removing card at (" << pos.second.first << ", " << pos.second.second << ").\n";
                        RemoveCard(pos.second.first, pos.second.first);
                        break;
                    case 'u':
                        std::cout << "Returning card to player at (" << pos.second.first << ", " << pos.second.second << ").\n";
                        ReturnCardToPlayer(pos.second.first, pos.second.second);
                        break;
                    case 'p':
                        std::cout << "Creating pit at (" << pos.second.first << ", " << pos.second.second << ").\n";
                        CreatePit(pos.second.first, pos.second.second);
                        break;

                        break;
                    }
                }
                break;

            default:
                break;
            }



        }

        if (board.CheckWinner(chosenCard.getColor())) {
            board.Display();
            std::cout << currentPlayer->getName() << " wins!\n";
            gameOver = true;
        }
        else if (board.IsDraw()) {
            board.Display();
            std::cout << "It's a draw!\n";
            gameOver = true;
        }
        else {
            SwitchTurn();
        }
    }
}

void Wizard_Mode::ResetGame()
{
    board.Clear();
    player1.ClearCards();
    player2.ClearCards();
    InitGame(player1.getName(), player2.getName());
}
