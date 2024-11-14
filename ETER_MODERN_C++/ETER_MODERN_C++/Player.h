#pragma once
#include "Card.h"
#include "Card.h"
#include "Element_Mode.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>   
#include <ctime> 
enum class WizardPower {
	RemoveOpponentCard,
	RemoveRow,
	CoverOpponentCard,
	CreatePit,
	MoveOwnStack,
	ExtraEterCard,
	MoveOpponentStack,
	MoveEdgeRow
};


class Player
{
private:
	std::vector<Card> m_cards;
	//std::vector<Element_Card> m_ElementCards;
	int m_LifePoints;
	WizardPower  m_wizard_power;
	std::string m_name;
	std::string m_color;
	bool m_placedCardFaceDown;
	std::pair<int, int> m_last_move;
public:
	bool powerUsed;
	// TODO 2: bool daca playerul are o bomba

public:
	Player()=default;
	Player(const std::string& playerName);

	bool CanPlaceCardFaceDown();
	void PlayedCardFaceDown();
	std::string getColor() const;
	void setColor(const std::string& color);
	std::string getName() const;
	void setLastMove(int row , int col);
	std::pair<int, int> getLastMove();
	void setName(const std::string& newName);
	WizardPower getWizardPower() const;
	void setRandomWizardPower();
	void ShowHand();
	Card PlayCard(int cardIndex);/// ii updataeaza vectorul de carti 
	bool HasCardAtIndex(int cardIndex);
	void UseAbilty();
	void AddCard(Card card);
	void ClearCards();
};

