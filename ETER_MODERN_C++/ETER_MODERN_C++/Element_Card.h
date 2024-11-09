#pragma once
#include"Element_Card.h";
#include<iostream>

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
    Element_Card(Power power) : powerType(power) {}

    // Getter pentru tipul de putere
    Power GetPowerType() const {
        return powerType;
    }

    // Metoda pentru activarea puterii elementare
    void ActivatePower() const {
        switch (powerType) {
        case Power::ControlledExplosion:
            std::cout << "Activated: Controlled Explosion - The board explodes!\n";
            // Logica specifica pentru Explozie controlata
            break;
        case Power::Destruction:
            std::cout << "Activated: Destruction - Removes the last card played by the opponent.\n";
            // Logica pentru Distrugere
            break;
        case Power::Flames:
            std::cout << "Activated: Flames - Reveals the opponent's illusion and allows an extra play.\n";
            // Logica pentru Flacari
            break;
        case Power::Lava:
            std::cout << "Activated: Lava - Returns visible cards of a chosen number to their owners.\n";
            // Logica pentru Lava
            break;
        case Power::FromAshes:
            std::cout << "Activated: From Ashes - Plays a previously removed card.\n";
            // Logica pentru Din cenusa
            break;
        case Power::Sparks:
            std::cout << "Activated: Sparks - Plays a covered card on a different position.\n";
            // Logica pentru Scantei
            break;
        case Power::Blizzard:
            std::cout << "Activated: Blizzard - Returns an opponent's visible card to their hand.\n";
            // Logica pentru Vifor
            break;
        case Power::Gale:
            std::cout << "Activated: Gale - Uncovers all cards beneath other cards.\n";
            // Logica pentru Vijelie
            break;
        case Power::Hurricane:
            std::cout << "Activated: Hurricane - Shifts a full row by one position.\n";
            // Logica pentru Uragan
            break;
        case Power::Gust:
            std::cout << "Activated: Gust - Moves a visible card to an adjacent position with a smaller card.\n";
            // Logica pentru Rafala
            break;
        case Power::Mirage:
            std::cout << "Activated: Mirage - Replaces the illusion with another.\n";
            // Logica pentru Miraj
            break;
        case Power::Storm:
            std::cout << "Activated: Storm - Removes any stack of cards with 2 or more cards.\n";
            // Logica pentru Furtuna
            break;
        case Power::Tide:
            std::cout << "Activated: Tide - Swaps two stacks of cards.\n";
            // Logica pentru Maree
            break;
        case Power::Mist:
            std::cout << "Activated: Mist - Allows another illusion.\n";
            // Logica pentru Ceata
            break;
        case Power::Wave:
            std::cout << "Activated: Wave - Moves a stack to an empty adjacent position.\n";
            // Logica pentru Val
            break;
        case Power::WaterSwirl:
            std::cout << "Activated: Water Swirl - Moves two cards across an empty space.\n";
            // Logica pentru Vartej de apa
            break;
        case Power::Tsunami:
            std::cout << "Activated: Tsunami - Restricts the opponent from playing on a chosen row.\n";
            // Logica pentru Tsunami
            break;
        case Power::Cascade:
            std::cout << "Activated: Cascade - Causes stacks to fall toward the edge, forming a new stack.\n";
            // Logica pentru Cascada
            break;
        case Power::Support:
            std::cout << "Activated: Support - Increases a card's value by 1.\n";
            // Logica pentru Sprijin
            break;
        case Power::Earthquake:
            std::cout << "Activated: Earthquake - Removes all visible cards with the number 1.\n";
            // Logica pentru Cutremur
            break;
        case Power::Shatter:
            std::cout << "Activated: Shatter - Decreases an opponent card's value by 1.\n";
            // Logica pentru Sfarama
            break;
        case Power::Borders:
            std::cout << "Activated: Borders - Places a neutral card on the board as a boundary.\n";
            // Logica pentru Granite
            break;
        case Power::Avalanche:
            std::cout << "Activated: Avalanche - Shifts two adjacent stacks.\n";
            // Logica pentru Avalansa
            break;
        case Power::Boulder:
            std::cout << "Activated: Boulder - Covers an illusion without revealing it.\n";
            // Logica pentru Bolovan
            break;
        }
    }
};