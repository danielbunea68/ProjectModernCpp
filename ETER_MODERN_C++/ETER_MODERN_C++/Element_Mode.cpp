#include "Elements_Mode.h"
#include "Explosion_Card.h"
#include "Element_Mode.h"
#include "Board.h"

void Element_Mode::SwitchTurn()
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

void Element_Mode::InitGame(std::string name1, std::string name2)
{
    player1.setName(name1);
    player2.setName(name2);
    board.SetSize(3);
    std::vector<int> values = { 1, 1, 2, 2, 3, 3, 4 };
    player1.setColor("red");
    player2.setColor("blue");
    for (const auto& value : values) {
        player1.AddCard(Card(value, player1.getColor()));
        player2.AddCard(Card(value, player2.getColor()));
    }
    currentPlayer = &player1;
}

void Element_Mode::PlayGame()
{
    bool gameOver = false;
    while (!gameOver)
    {
        board.Display();
        currentPlayer->ShowHand();

        // TODO: Daca player-ul curent are o bomba
        // Intreabal daca vrea sa o foloseasca si daca da, afiseaza un meniu in care sa ii spui ca poate roti bomba
        // si apoi sa confirme si sa fie aplicate efectele

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

void Element_Mode::ResetGame()
{
    board.Clear();
    player1.ClearCards();
    player2.ClearCards();
    InitGame(player1.getName(), player2.getName());
}

void Element_Mode::RemoveCard(int row, int col)
{
    board.Remove(row, col);
}

void Element_Mode::ReturnCardToPlayer(int row, int col)
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

void Element_Mode::CreatePit(int row, int col)
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

Element_Mode::Element_Mode(Putere putere) : tipPutere(putere){}

Element_Mode::Putere Element_Mode::GetTipPutere() const 
{
    return tipPutere;
}

void Element_Mode::ActivatePower() const
{
    switch (tipPutere) {
    case Putere::ExplozieControlata:
        std::cout << "Activating Explozie Controlata: Tabla explodează!" << std::endl;
        ActivateControlledExplosion();
        break;
    case Putere::Distrugere:
        std::cout << "Activating Distrugere: Elimină ultima carte jucată de adversar." << std::endl;
        break;
    case Putere::Flacari:
        std::cout << "Activating Flacari: Întoarce iluzia adversarului și joacă o carte." << std::endl;
        // Logic for Flacari goes here
        break;
    case Putere::Lava:
        std::cout << "Activating Lava: Toate cărțile vizibile cu un anumit număr se întorc la proprietari." << std::endl;
        // Logic for Lava goes here
        break;
    case Putere::DinCenusa:
        std::cout << "Activating Din Cenusa: Joacă imediat o carte eliminată." << std::endl;
        // Logic for Din Cenusa goes here
        break;
    case Putere::Scantei:
        std::cout << "Activating Scantei: Joacă o carte acoperită de adversar pe o altă poziție." << std::endl;
        // Logic for Scantei goes here
        break;
    case Putere::Viscol:
        std::cout << "Activating Viscol: Întoarce o carte vizibilă a oponentului în mâna sa." << std::endl;
        // Logic for Viscol goes here
        break;
    case Putere::Vijelie:
        std::cout << "Activating Vijelie: Toate cărțile acoperite se întorc la proprietari." << std::endl;
        // Logic for Vijelie goes here
        break;
    case Putere::Uragan:
        std::cout << "Activating Uragan: Shiftează un rând complet ocupat." << std::endl;
        // Logic for Uragan goes here
        break;
    case Putere::Rafala:
        std::cout << "Activating Rafala: Mută o carte vizibilă adiacent unei cărți cu număr mai mic." << std::endl;
        // Logic for Rafala goes here
        break;
    case Putere::Miraj:
        std::cout << "Activating Miraj: Înlocuiește propria iluzie plasată cu o altă iluzie." << std::endl;
        // Logic for Miraj goes here
        break;
    case Putere::Furtuna:
        std::cout << "Activating Furtuna: Elimină din joc un teanc de cărți cu 2 sau mai multe cărți." << std::endl;
        // Logic for Furtuna goes here
        break;
    case Putere::Maree:
        std::cout << "Activating Maree: Interschimbă pozițiile a două teancuri de cărți." << std::endl;
        // Logic for Maree goes here
        break;
    case Putere::Ceata:
        std::cout << "Activating Ceata: Joacă încă o iluzie." << std::endl;
        // Logic for Ceata goes here
        break;
    case Putere::Val:
        std::cout << "Activating Val: Mută un teanc pe o poziție adiacentă goală și joacă o carte pe noua poziție goală." << std::endl;
        // Logic for Val goes here
        break;
    case Putere::VartejDeApa:
        std::cout << "Activating Vartej De Apa: Mută 2 cărți despărțite de un spațiu gol pe acel spațiu." << std::endl;
        // Logic for Vartej De Apa goes here
        break;
    case Putere::Tsunami:
        std::cout << "Activating Tsunami: Blochează un rând pentru adversar în următoarea tură." << std::endl;
        // Logic for Tsunami goes here
        break;
    case Putere::Cascada:
        std::cout << "Activating Cascade: Teancurile de pe un rând cad spre o margine și formează un nou teanc." << std::endl;
        // Logic for Cascade goes here
        break;
    case Putere::Sprijin:
        std::cout << "Activating Sprijin: Valoarea unei cărți proprii 1/2/3 crește cu 1." << std::endl;
        // Logic for Sprijin goes here
        break;
    case Putere::Cutremur:
        std::cout << "Activating Cutremur: Elimină de pe tablă toate cărțile vizibile cu numărul 1." << std::endl;
        // Logic for Cutremur goes here
        break;
    case Putere::Sfaramare:
        std::cout << "Activating Sfaramare: Valoarea unei cărți a adversarului 2/3/4 scade cu 1." << std::endl;
        // Logic for Sfaramare goes here
        break;
    case Putere::Granite:
        std::cout << "Activating Granite: Plasează o carte neutră care definește o graniță." << std::endl;
        // Logic for Granite goes here
        break;
    case Putere::Avalansa:
        std::cout << "Activating Avalansa: Shiftează două teancuri adiacente pe o poziție goală." << std::endl;
        // Logic for Avalansa goes here
        break;
    case Putere::Bolovan:
        std::cout << "Activating Bolovan: Acoperă o iluzie cu o carte fără a o întoarce." << std::endl;
        // Logic for Bolovan goes here
        break;
    default:
        std::cout << "Unknown power!" << std::endl;
        break;
    }
}

void Element_Mode::ActivateControlledExplosion() const
{
    Explosion_Card explosionCard(4); 
    explosionCard.activateExplosion();
}
