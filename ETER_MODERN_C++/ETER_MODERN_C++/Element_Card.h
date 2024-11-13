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

    Element_Card(Putere putere);
    Putere GetTipPutere() const;
    void ActivatePower() const;
    void ActivateControlledExplosion() const;
};