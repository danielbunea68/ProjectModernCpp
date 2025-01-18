#include "Speed_Mode.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "Game.h"
#include "Wizard_Mode.h"
#include "Element_Mode.h"
#include "Combined_Mode.h"

Speed_Mode::Speed_Mode()
    : isGameOver(false), currentPlayer(nullptr), timeLimit(60), remainingTimePlayer1(60), remainingTimePlayer2(60), game(nullptr) {}

Speed_Mode::~Speed_Mode()
{
    delete game;
    game = nullptr;
}

Speed_Mode::Speed_Mode(const Speed_Mode& other)
{
    speed_board = other.speed_board;
    m_mode = other.m_mode;
    isGameOver = other.isGameOver;
    timeLimit = other.timeLimit;
    remainingTimePlayer1 = other.remainingTimePlayer1;
    remainingTimePlayer2 = other.remainingTimePlayer2;
}

Speed_Mode& Speed_Mode::operator=(const Speed_Mode& other)
{
    if (this == &other) return *this;
    delete game;
    speed_board = other.speed_board;
    m_mode = other.m_mode;
    isGameOver = other.isGameOver;
    timeLimit = other.timeLimit;
    remainingTimePlayer1 = other.remainingTimePlayer1;
    remainingTimePlayer2 = other.remainingTimePlayer2;
    return *this;
}

Speed_Mode::Speed_Mode(Speed_Mode&& other) noexcept
{
    game = other.game;
    speed_board = std::move(other.speed_board);
    m_mode = other.m_mode;
    isGameOver = other.isGameOver;
    other.game = nullptr;
}

Speed_Mode& Speed_Mode::operator=(Speed_Mode&& other) noexcept
{
    if (this == &other) return *this;
    delete game;
    game = other.game;
    speed_board = std::move(other.speed_board);
    m_mode = other.m_mode;
    isGameOver = other.isGameOver;
    other.game = nullptr;
    return *this;
}

void Speed_Mode::chooseGame()
{
    switch (m_mode)
    {
    case 't':
        game = new Game();
        break;
    case 'w':
        game = new Wizard_Mode();
        break;
    case 'e':
        game = new Element_Mode();
        break;
    case 'x':
        game = new Combined_Mode();
        break;
    default:
        break;
    }
}

void Speed_Mode::setMode(char mode)
{
    m_mode = mode;
}

bool Speed_Mode::CheckWinner(std::string color)
{
    for (int i = 0; i < 3; i++)
    {
        if ((speed_board[i][0] == color && speed_board[i][1] == color && speed_board[i][2] == color) ||
            (speed_board[0][i] == color && speed_board[1][i] == color && speed_board[2][i] == color)) {
            return true;
        }
    }
    if ((speed_board[0][0] == color && speed_board[1][1] == color && speed_board[2][2] == color) ||
        (speed_board[0][2] == color && speed_board[1][1] == color && speed_board[2][0] == color)) {
        return true;
    }
    return false;
}

void Speed_Mode::PlayGameChosen(std::string name1, std::string name2)
{
    game->InitGame(name1, name2);
    Player* player = nullptr;
    Player* second_player = nullptr;
    int number_of_games = 5;

    while (number_of_games && !isGameOver)
    {
        StartTurnTimer();
        game->PlayGame();

        if (second_player != player)
            second_player = player;

        player = game->CurrentTurn();
        int x = player->getWinnCords().first;
        int y = player->getWinnCords().second;
        speed_board[x][y] = player->getColor();
        isGameOver = CheckWinner(player->getColor());
        game->ResetGame();
        number_of_games--;
    }

    if (isGameOver)
        std::cout << player->getName() << " has won the Speed Mode!\n";
    else
        std::cout << "Game over. No winner.\n";
}

void Speed_Mode::StartTurnTimer()
{
    turnStartTime = std::chrono::steady_clock::now();
}

bool Speed_Mode::CheckTimer()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - turnStartTime).count();
    if (elapsedTime > timeLimit)
    {
        HandleTimeout(currentPlayer);
        return true;
    }
    return false;
}

void Speed_Mode::HandleTimeout(Player* player)
{
    std::cout << player->getName() << " ran out of time and loses the game!\n";
    isGameOver = true;
}

void Speed_Mode::DisplaySpeedBoard()
{
    std::cout << "\nCurrent Speed Board:\n";
    for (const auto& row : speed_board)
    {
        for (const auto& cell : row)
        {
            if (cell.empty())
                std::cout << "   .   ";
            else
                std::cout << "   " << cell << "   ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
