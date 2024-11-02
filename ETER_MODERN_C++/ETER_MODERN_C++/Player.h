#pragma once
#include "Card.h"
#include "Card.h"
#include "Element_Card.h"
#include <string>
#include <vector>
#include <iostream>

class Player
{
private:
	std::vector<Card> m_cards;
	std::vector<Element_Card> m_ElementCards;
	int m_LifePoints;
	Card  m_wizard;
	std::string m_name;
	std::string m_color;

public:
	void AddInitialCards(std::vector<Card>& availableCards);
	Player(const std::string& playerName, const Card& wizardCard);
	std::string getColor() const;
	void setColor(const std::string& color);
	std::string getName() const;
	void ShowHand();
	void setName(const std::string& newName);
	Card PlayCard(int cardIndex);
	bool HasCardAtIndex(int cardIndex);
	void UseAbilty();
	void AddCard(Card card);
	void ClearCards();
};

