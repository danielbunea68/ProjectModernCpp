#include "Speed_Mode.h"
#include <iostream>
#include <chrono>

Speed_Mode::Speed_Mode()
    : isGameOver(false), currentPlayer(nullptr), timeLimit(60), remainingTimePlayer1(60), remainingTimePlayer2(60) {}

Speed_Mode::~Speed_Mode()= default;

// Constructor de copiere șters
Speed_Mode::Speed_Mode(const Speed_Mode& other) = default;

// Operator de atribuire șters
Speed_Mode& Speed_Mode::operator=(const Speed_Mode& other) = default;


Speed_Mode::Speed_Mode(Speed_Mode&& other) noexcept
: board(std::move(other.board)),
player1(std::move(other.player1)),
player2(std::move(other.player2)),
currentPlayer(other.currentPlayer),
isGameOver(other.isGameOver),
timeLimit(other.timeLimit),
turnStartTime(other.turnStartTime),
remainingTimePlayer1(other.remainingTimePlayer1),
remainingTimePlayer2(other.remainingTimePlayer2) {}

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
    player1 = std::make_unique<Player>(name1, "Blue");
    player2 = std::make_unique<Player>(name2, "Red");
    currentPlayer = player1.get();
    isGameOver = false;

    ResetTimers();
    std::cout << "Game initialized between " << player1->getName() << " and " << player2->getName() << ".\n";
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
    currentPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
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
    remainingTimePlayer1 = 300;//5 minute
    remainingTimePlayer2 = 300;
}
bool Speed_Mode::CheckTimer()
{
    auto now = std::chrono::steady_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - turnStartTime).count();

    if (currentPlayer == player1.get()) {
        remainingTimePlayer1 -= elapsed;
        return remainingTimePlayer1 > 0;
    } else {
        remainingTimePlayer2 -= elapsed;
        return remainingTimePlayer2 > 0;
    }
}

void Speed_Mode::PlayGame() {
    while (!isGameOver) {
        board.Display();
        StartTurnTimer();

        std::cout << currentPlayer->getName() << "'s turn. Remaining time: ";
        if (currentPlayer == player1.get()) {
            std::cout << remainingTimePlayer1 << " seconds\n";
        } else {
            std::cout << remainingTimePlayer2 << " seconds\n";
        }

        TimerBasedPlay();

        if (!CheckTimer()) {
            HandleTimeout(currentPlayer);
            break;
        }

        SwitchTurn();
    }

    CheckWinner();
}

void Speed_Mode::ResetGame() {
    board.Reset();
    ResetTimers();
    currentPlayer = player1.get();
    isGameOver = false;
    std::cout << "Game has been reset.\n";
}

void Speed_Mode::TimerBasedPlay() {
    using namespace std::chrono;
    StartTurnTimer();

    int row, col;
    bool validMove = false;

    while (!validMove && !isGameOver) {
        auto now = steady_clock::now();
        int elapsed = duration_cast<seconds>(now - turnStartTime).count();

        // Actualizează timpul rămas pentru jucătorul curent
        if (currentPlayer == player1.get()) {
            remainingTimePlayer1 -= elapsed;
        } else if (currentPlayer == player2.get()) {
            remainingTimePlayer2 -= elapsed;
        }

        // Verifică dacă timpul s-a terminat pentru jucătorul curent
        if (remainingTimePlayer1 <= 0 || remainingTimePlayer2 <= 0) {
            std::cout << currentPlayer->getName() << " ran out of time and loses the game!\n";
            isGameOver = true;
            return;
        }

        // Afișează timpul rămas
        std::cout << "Remaining time for " << currentPlayer->getName() << ": "
                  << (currentPlayer == player1.get() ? remainingTimePlayer1 : remainingTimePlayer2) << " seconds.\n";

        // Cere jucătorului să introducă o mutare
        std::cout << "Enter row and column for your move: ";
        std::cin >> row >> col;

        // Încearcă să facă mutarea
        validMove = board.MakeMove(row, col, currentPlayer->PlayCard(0));

        if (!validMove) {
            std::cout << "Invalid move. Try again!\n";
        }

        // Resetează cronometrul pentru următoarea verificare
        turnStartTime = steady_clock::now();
    }
}

void Speed_Mode::ConfigureTimeLimit(int seconds)
{
    timeLimit = seconds;
    remainingTimePlayer1 = seconds;
    remainingTimePlayer2 = seconds;
}

void Speed_Mode::HandleTimeout(Player* player) {
    std::cout << player->getName() << " ran out of time and loses!\n";
    isGameOver = true;
}

void Speed_Mode::DisplayTimeRemaining() const {
    std::cout << player1->getName() << ": " << remainingTimePlayer1 << " seconds\n";
    std::cout << player2->getName() << ": " << remainingTimePlayer2 << " seconds\n";
}