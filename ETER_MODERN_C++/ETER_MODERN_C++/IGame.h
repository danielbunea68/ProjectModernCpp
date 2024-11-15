#pragma once
#include <string>

class IGame {
public:
    virtual ~IGame() = default;

    virtual void InitGame(std::string name1, std::string name2) = 0;
    virtual void PlayGame() = 0;
    virtual void ResetGame() = 0;

    virtual void RemoveCard(int row, int col) = 0;
    virtual void ReturnCardToPlayer(int row, int col) = 0;
    virtual void CreatePit(int row, int col) = 0;
};
    