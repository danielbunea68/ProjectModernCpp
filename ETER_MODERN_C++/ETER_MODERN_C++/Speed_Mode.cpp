#include "Speed_Mode.h"
#include <iostream>
#include <chrono>

Speed_Mode::Speed_Mode() : isGameOver(false), currentPlayer(nullptr) {}

Speed_Mode::~Speed_Mode() {}

void Speed_Mode::InitGame(std::string name1, std::string name2) {
    player1.setName(name1);
    player2.setName(name2);
    board.SetSize(3);
    player1.setColor("red");
    player2.setColor("blue");

    std::vector<int> values = { 1, 1, 2, 3, 3 };
    for (auto value : values) {
        player1.AddCard(Card(value, player1.getColor()));
        player2.AddCard(Card(value, player2.getColor()));
    }
    currentPlayer = &player1;
}

void Speed_Mode::SwitchTurn() {
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}

void Speed_Mode::CheckWinner() {
    if (board.CheckWinner(currentPlayer->getColor())) {
        std::cout << currentPlayer->getName() << " wins the Speed Mode game!\n";
        isGameOver = true;
    } else if (board.IsDraw()) {
        std::cout << "It's a draw!\n";
        isGameOver = true;
    }
}

void Speed_Mode::PlayGame() {
    while (!isGameOver) {
        board.Display();
        std::cout << currentPlayer->getName() << "'s turn.\n";

        TimerBasedPlay();

        CheckWinner();
        if (!isGameOver) {
            SwitchTurn();
        }
    }
}

void Speed_Mode::ResetGame() {
    board.Clear();
    player1.ClearCards();
    player2.ClearCards();
    InitGame(player1.getName(), player2.getName());
}

void Speed_Mode::TimerBasedPlay() {
    using namespace std::chrono;
    auto start = steady_clock::now();

    int row, col;
    bool validMove = false;

    do {
        auto now = steady_clock::now();
        auto elapsed = duration_cast<seconds>(now - start).count();

        if (elapsed > 10) {
            std::cout << currentPlayer->getName() << " ran out of time!\n";
            return;
        }

        std::cout << "Enter row and column (within 10 seconds): ";
        std::cin >> row >> col;

        validMove = board.MakeMove(row, col, currentPlayer->PlayCard(0));
    } while (!validMove);
}
