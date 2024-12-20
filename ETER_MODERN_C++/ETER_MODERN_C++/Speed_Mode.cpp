#include "Speed_Mode.h"
#include <iostream>
#include <chrono>

Speed_Mode::Speed_Mode()
    : isGameOver(false), currentPlayer(nullptr), timeLimit(60), remainingTimePlayer1(60), remainingTimePlayer2(60) {}

Speed_Mode::~Speed_Mode() {}

Speed_Mode::Speed_Mode(const Speed_Mode& other) : board(other.board),
player1(other.player1), player2(other.player2), currentPlayer(other.currentPlayer == &other.player1 ? &player1 : &player2),
isGameOver(other.isGameOver) {}

Speed_Mode& Speed_Mode::operator=(const Speed_Mode& other)
{
    if (this == &other)
        return *this;

    board = other.board;
    player1 = other.player1;
    player2 = other.player2;
    currentPlayer = (other.currentPlayer == &other.player1) ? &player1 : &player2;
    isGameOver = other.isGameOver;

    return *this;
}

Speed_Mode::Speed_Mode(Speed_Mode&& other) noexcept
:board(std::move(other.board)), player1(std::move(other.player1)), player2(std::move(other.player2)),
 currentPlayer(other.currentPlayer == &other.player1 ? &player1 : &player2), isGameOver(other.isGameOver) 
{
    other.currentPlayer = nullptr;
    other.isGameOver = false;
}

Speed_Mode& Speed_Mode::operator=(Speed_Mode&& other) noexcept
{
    if (this == &other)
        return *this;

    board = std::move(other.board);
    player1 = std::move(other.player1);
    player2 = std::move(other.player2);
    currentPlayer = (other.currentPlayer == &other.player1) ? &player1 : &player2;
    isGameOver = other.isGameOver;

    other.currentPlayer = nullptr;
    other.isGameOver = false;

    return *this;
}

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

    currentPlayer = &player1; // Set the first player
    ResetTimers(); // Ensure timers are reset at the start of the game
    isGameOver = false;
}

/*
Player* Speed_Mode::CurrentTurn()
{
    return nullptr;
}

Player* Speed_Mode::PreviousTurn()
{
    return nullptr;
}
*/

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

void Speed_Mode::StartTurnTimer()
{
    turnStartTime = std::chrono::steady_clock::now();
}

void Speed_Mode::ResetTimers() {
    remainingTimePlayer1 = timeLimit;
    remainingTimePlayer2 = timeLimit;
}
bool Speed_Mode::CheckTimer()
{
    using namespace std::chrono;

    auto now = steady_clock::now();
    int elapsed = duration_cast<seconds>(now - turnStartTime).count();

    if (currentPlayer == &player1) {
        remainingTimePlayer1 -= elapsed;
        if (remainingTimePlayer1 <= 0) {
            std::cout << player1.getName() << " ran out of time and loses the game!\n";
            isGameOver = true;
            return false;
        }
    }
    else {
        remainingTimePlayer2 -= elapsed;
        if (remainingTimePlayer2 <= 0) {
            std::cout << player2.getName() << " ran out of time and loses the game!\n";
            isGameOver = true;
            return false;
        }
    }

    return true;
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
    StartTurnTimer();

    int row, col;
    bool validMove = false;

    while (!validMove && !isGameOver) {
        auto now = steady_clock::now();
        int elapsed = duration_cast<seconds>(now - turnStartTime).count();
        
        if (currentPlayer == &player1) {
            remainingTimePlayer1 -= elapsed;
        } else {
            remainingTimePlayer2 -= elapsed;
        }

        if (remainingTimePlayer1 <= 0 || remainingTimePlayer2 <= 0) {
            std::cout << currentPlayer->getName() << " ran out of time and loses the game!\n";
            isGameOver = true;
            return;
        }

        std::cout << "Remaining time for " << currentPlayer->getName() << ": "
                  << (currentPlayer == &player1 ? remainingTimePlayer1 : remainingTimePlayer2) << " seconds.\n";

        std::cout << "Enter row and column for your move: ";
        std::cin >> row >> col;

        validMove = board.MakeMove(row, col, currentPlayer->PlayCard(0));

        if (!validMove) {
            std::cout << "Invalid move. Try again!\n";
        }
        turnStartTime = steady_clock::now();
    }
}

void Speed_Mode::ConfigureTimeLimit(int seconds)
{
    timeLimit = seconds;
    remainingTimePlayer1 = seconds;
    remainingTimePlayer2 = seconds;
}
