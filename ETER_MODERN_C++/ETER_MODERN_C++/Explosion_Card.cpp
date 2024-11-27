
#include "Explosion_Card.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <set>

void Explosion_Card::generateEffects() 
{
    int effectCount = (m_size == 3) ? (rand() % 3 + 2) : (rand() % 4 + 3);
    int pitCount = 0;
    for (int i = 0; i < effectCount; ++i) 
    {
        if (pitCount < 1 && (rand() % 10) == 0) 
        { 
            m_effects.push_back(Effect::CreatePit);
            pitCount++;
        }
        else 
        {
            m_effects.push_back(static_cast<Effect>(rand() % 2)); 
        }
    }
}

void Explosion_Card::displayBoard() const
{
    std::cout << "Current Board State:\n";
    for (int i = 0; i < m_row; ++i) 
    {
        for (int j = 0; j < m_col; ++j) 
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

Explosion_Card::Explosion_Card()
{
}

Explosion_Card::Explosion_Card(int explosionSize):
    m_size(explosionSize), m_row(explosionSize), m_col(explosionSize) 
{
    std::srand(std::time(0));
    generateEffects();
    board.resize(m_row, std::vector<char>(m_col, 'C')); 
}

Explosion_Card::~Explosion_Card()
{
}

Explosion_Card::Explosion_Card(const Explosion_Card& other) : m_size(other.m_size), m_row(other.m_row), m_col(other.m_col),
m_effects(other.m_effects), appliedPositions(other.appliedPositions) 
{
    board = other.board;
}

Explosion_Card& Explosion_Card::operator=(const Explosion_Card& other) 
{
    if (this != &other) 
    {
        m_size = other.m_size;
        m_row = other.m_row;
        m_col = other.m_col;
        m_effects = other.m_effects;
        appliedPositions = other.appliedPositions;
        board = other.board;
    }
    return *this;
}

Explosion_Card::Explosion_Card(Explosion_Card&& other) noexcept
    : m_size(other.m_size), m_row(other.m_row), m_col(other.m_col),
    m_effects(std::move(other.m_effects)), appliedPositions(std::move(other.appliedPositions)),
    board(std::move(other.board)) 
{
 
    other.m_size = 0;
    other.m_row = 0;
    other.m_col = 0;
}

Explosion_Card& Explosion_Card::operator=(Explosion_Card&& other) noexcept {
    if (this != &other) {
        m_size = other.m_size;
        m_row = other.m_row;
        m_col = other.m_col;
        m_effects = std::move(other.m_effects);
        appliedPositions = std::move(other.appliedPositions);
        board = std::move(other.board);

        // Resetăm obiectul sursă
        other.m_size = 0;
        other.m_row = 0;
        other.m_col = 0;
    }
    return *this;
}

void Explosion_Card::storeAppliedPosition(int row, int col) 
{
    appliedPositions.emplace_back(row, col); 
}

void Explosion_Card::activateExplosion() 
{
    std::cout << "Activating explosion:\n";

    std::set<std::pair<int, int>> usedPositions; 
    int effectCount = m_effects.size(); 

    for (int i = 0; i < effectCount; ++i) 
    {
        
        int randomRow = rand() % m_row;
        int randomCol = rand() % m_col;

        
        while (usedPositions.count({ randomRow, randomCol }) > 0) 
        {
            randomRow = rand() % m_row; 
            randomCol = rand() % m_col; 
        }
       
        usedPositions.insert({ randomRow, randomCol });

        int effectIndex = rand() % m_effects.size();
        auto effect = m_effects[effectIndex]; 

        switch (effect) 
        {
        case Effect::RemoveCard:
            std::cout << "Effect: Remove card at (" << randomRow << ", " << randomCol << ")\n";
            board[randomRow][randomCol] = 'r';
            storeAppliedPosition(randomRow, randomCol);
            break;
        case Effect::ReturnCard:
            std::cout << "Effect: Return card to player at (" << randomRow << ", " << randomCol << ")\n";
            board[randomRow][randomCol] = 'u'; 
            storeAppliedPosition(randomRow, randomCol); 
            break;
        case Effect::CreatePit:
            std::cout << "Effect: Create pit at (" << randomRow << ", " << randomCol << ")\n";
            board[randomRow][randomCol] = 'p'; 
            storeAppliedPosition(randomRow, randomCol); 
            break;
        }
    }

    displayBoard(); 
}

// Methoda care returneaza pozitiile si tipul efectelor ce vor fi aplicate de cartea explozie
std::vector<std::pair<char, std::pair<int, int>>> Explosion_Card::AppliedPositions()
{
    std::vector<std::pair<char, std::pair<int, int>>> bombPositions;

    for (const auto& pos : appliedPositions)
    {
        int row = pos.first;
        int col = pos.second;
        char bombType = board[row][col];  

        bombPositions.push_back({ bombType, {row, col} });
    }
    return bombPositions;
}



