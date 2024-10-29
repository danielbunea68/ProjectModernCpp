#pragma once
#include "Card.h"
#include "Card.h"
#include "Element_Card.h"
#include <string>
#include <vector>

class Player
{
private:
	std::vector<Card> m_cards;
	std::vector<Element_Card> m_ElementCards;
	int m_LifePoints;
	Card  m_wizard;
	std::string m_name;

public:

	Player(const std::string& playerName, const Card& wizardCard);
	std::string getName() const;
	void setName(const std::string& newName);
	void PlayCard();/// ii updataeaza vectorul de carti 
	void UseAbilty();
};

