#include "Element_Card.h"
#include "Explosion_Card.h"

Element_Card::Element_Card(Putere putere) : tipPutere(putere){}

Element_Card::Putere Element_Card::GetTipPutere() const 
{
    return tipPutere;
}

void Element_Card::ActivatePower() const
{
    switch (tipPutere) {
    case Putere::ExplozieControlata:
        std::cout << "Activating Explozie Controlata: Tabla explodează!" << std::endl;
        ActivateControlledExplosion();
        break;
    case Putere::Distrugere:
        std::cout << "Activating Distrugere: Elimină ultima carte jucată de adversar." << std::endl;
        // Logic for Distrugere goes here
        break;
    case Putere::Flacari:
        std::cout << "Activating Flacari: Întoarce iluzia adversarului și joacă o carte." << std::endl;
        // Logic for Flacari goes here
        break;
    case Putere::Lava:
        std::cout << "Activating Lava: Toate cărțile vizibile cu un anumit număr se întorc la proprietari." << std::endl;
        // Logic for Lava goes here
        break;
    case Putere::DinCenusa:
        std::cout << "Activating Din Cenusa: Joacă imediat o carte eliminată." << std::endl;
        // Logic for Din Cenusa goes here
        break;
    case Putere::Scantei:
        std::cout << "Activating Scantei: Joacă o carte acoperită de adversar pe o altă poziție." << std::endl;
        // Logic for Scantei goes here
        break;
    case Putere::Viscol:
        std::cout << "Activating Viscol: Întoarce o carte vizibilă a oponentului în mâna sa." << std::endl;
        // Logic for Viscol goes here
        break;
    case Putere::Vijelie:
        std::cout << "Activating Vijelie: Toate cărțile acoperite se întorc la proprietari." << std::endl;
        // Logic for Vijelie goes here
        break;
    case Putere::Uragan:
        std::cout << "Activating Uragan: Shiftează un rând complet ocupat." << std::endl;
        // Logic for Uragan goes here
        break;
    case Putere::Rafala:
        std::cout << "Activating Rafala: Mută o carte vizibilă adiacent unei cărți cu număr mai mic." << std::endl;
        // Logic for Rafala goes here
        break;
    case Putere::Miraj:
        std::cout << "Activating Miraj: Înlocuiește propria iluzie plasată cu o altă iluzie." << std::endl;
        // Logic for Miraj goes here
        break;
    case Putere::Furtuna:
        std::cout << "Activating Furtuna: Elimină din joc un teanc de cărți cu 2 sau mai multe cărți." << std::endl;
        // Logic for Furtuna goes here
        break;
    case Putere::Maree:
        std::cout << "Activating Maree: Interschimbă pozițiile a două teancuri de cărți." << std::endl;
        // Logic for Maree goes here
        break;
    case Putere::Ceata:
        std::cout << "Activating Ceata: Joacă încă o iluzie." << std::endl;
        // Logic for Ceata goes here
        break;
    case Putere::Val:
        std::cout << "Activating Val: Mută un teanc pe o poziție adiacentă goală și joacă o carte pe noua poziție goală." << std::endl;
        // Logic for Val goes here
        break;
    case Putere::VartejDeApa:
        std::cout << "Activating Vartej De Apa: Mută 2 cărți despărțite de un spațiu gol pe acel spațiu." << std::endl;
        // Logic for Vartej De Apa goes here
        break;
    case Putere::Tsunami:
        std::cout << "Activating Tsunami: Blochează un rând pentru adversar în următoarea tură." << std::endl;
        // Logic for Tsunami goes here
        break;
    case Putere::Cascada:
        std::cout << "Activating Cascade: Teancurile de pe un rând cad spre o margine și formează un nou teanc." << std::endl;
        // Logic for Cascade goes here
        break;
    case Putere::Sprijin:
        std::cout << "Activating Sprijin: Valoarea unei cărți proprii 1/2/3 crește cu 1." << std::endl;
        // Logic for Sprijin goes here
        break;
    case Putere::Cutremur:
        std::cout << "Activating Cutremur: Elimină de pe tablă toate cărțile vizibile cu numărul 1." << std::endl;
        // Logic for Cutremur goes here
        break;
    case Putere::Sfaramare:
        std::cout << "Activating Sfaramare: Valoarea unei cărți a adversarului 2/3/4 scade cu 1." << std::endl;
        // Logic for Sfaramare goes here
        break;
    case Putere::Granite:
        std::cout << "Activating Granite: Plasează o carte neutră care definește o graniță." << std::endl;
        // Logic for Granite goes here
        break;
    case Putere::Avalansa:
        std::cout << "Activating Avalansa: Shiftează două teancuri adiacente pe o poziție goală." << std::endl;
        // Logic for Avalansa goes here
        break;
    case Putere::Bolovan:
        std::cout << "Activating Bolovan: Acoperă o iluzie cu o carte fără a o întoarce." << std::endl;
        // Logic for Bolovan goes here
        break;
    default:
        std::cout << "Unknown power!" << std::endl;
        break;
    }
}

void Element_Card::ActivateControlledExplosion() const
{
    Explosion_Card explosionCard(4); 
    explosionCard.activateExplosion();
}
