/*

#pragma once
#include <iostream>
#include "Game.h"

class Element_Card
{
public:
    // Enum pentru a reprezenta toate puterile elementare
    enum class Power {
        ControlledExplosion,
        Destruction,
        Flames,
        Lava,
        FromAshes,
        Sparks,
        Blizzard,
        Gale,
        Hurricane,
        Gust,
        Mirage,
        Storm,
        Tide,
        Mist,
        Wave,
        WaterSwirl,
        Tsunami,
        Cascade,
        Support,
        Earthquake,
        Shatter,
        Borders,
        Avalanche,
        Boulder
    };

private:
    Power powerType;  // Tipul de putere asociat cu această carte

public:
    // Constructor
    Element_Card(Power power);

    // Getter pentru tipul de putere
    Power GetPowerType() const;

    // Metoda pentru activarea puterii elementare
    void ActivatePower(Game* gameInstance) const;
};
*/