#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <set>

enum class Effect 
{
    RemoveCard,
    ReturnCard,
    CreatePit
};


class Explosion_Card
{
private:
    int m_size;
    std::vector<Effect> m_effects;
    std::vector<std::vector<char>> board;
    int m_row, m_col;
    std::vector<std::pair<int, int>> appliedPositions;
    void generateEffects();
    void displayBoard() const;
    void storeAppliedPosition(int row, int col);

public:
    Explosion_Card();
    Explosion_Card(int explosionSize);

    ~Explosion_Card();

    Explosion_Card(const Explosion_Card& other);

    Explosion_Card& operator=(const Explosion_Card& other);

    Explosion_Card(Explosion_Card&& other) noexcept;

    Explosion_Card& operator=(Explosion_Card&& other) noexcept;

     void activateExplosion();
    std::vector<std::pair<char, std::pair<int, int>>> AppliedPositions();
};

