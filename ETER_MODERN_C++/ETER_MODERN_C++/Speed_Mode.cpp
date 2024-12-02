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

