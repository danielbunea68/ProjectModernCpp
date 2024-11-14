#pragma once
#include <iostream>

class Element_Card 
{
public:
    enum class Putere 
    {
        ExplozieControlata,
        Distrugere,
        Flacari,
        Lava,
        DinCenusa,
        Scantei,
        Viscol,
        Vijelie,
        Uragan,
        Rafala,
        Miraj,
        Furtuna,
        Maree,
        Ceata,
        Val,
        VartejDeApa,
        Tsunami,
        Cascada,
        Sprijin,
        Cutremur,
        Sfaramare,
        Granite,
        Avalansa,
        Bolovan
    };

private:
    Putere tipPutere;

public:


    Element_Mode();
    void InitGame(std::string name1, std::string name2) = 0;
    void PlayGame() = 0;
    void ResetGame() = 0;

    void RemoveCard(int row, int col) = 0;
    void ReturnCardToPlayer(int row, int col) = 0;
    void CreatePit(int row, int col) = 0;


    Element_Mode(Putere putere);
    Putere GetTipPutere() const;
    void ActivatePower();
    void ActivateControlledExplosion() const;
};