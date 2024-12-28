#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>   
#include <ctime> 
#include <algorithm>

#include "Card.h"
#include "Bomb.h"
#include "Element_Mode.h"

enum class WizardPower
{
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
	WizardPower  m_wizard_power;
	int m_LifePoints;
	std::string m_name;
	std::string m_color;
	bool m_placedCardFaceDown;
	std::pair<int, int> m_last_move;
	std::vector<Card> removedCards;
	std::pair<int, int> m_winncords;
	static std::vector<WizardPower> assignedPowers;
	bool elementPowerUsed = false;  
	Element_Mode::Putere elementPower;

	Bomb* bomb = nullptr;

public:
	bool powerUsed = false;
	bool selectedBomb = false;
	bool hasBomb = false;

	void rotateBomb(std::string direction) {
		if (!hasBomb) return;

		if (direction == "left")
			bomb->rotateLeft();
		else
			bomb->rotateRight();
	}

	void setBomb(Bomb* bomb) {
		this->bomb = bomb;
		hasBomb = true;
	}

	Bomb* getBomb() {
		return bomb;
	}

public:

	Player() = default;
	~Player() = default;
	Player(const Player& other);
	Player(const std::string& playerName);
	Player& operator=(const Player& other);
	Player(Player&& other) noexcept;
	Player& operator=(Player&& other) noexcept;

	bool CanPlaceCardFaceDown();
	void PlayedCardFaceDown();
	std::string getColor() const;
	void setColor(const std::string& color);
	std::string getName() const;
	void setLastMove(int row, int col);
	std::pair<int, int> getLastMove();
	void setName(const std::string& newName);
	WizardPower getWizardPower() const;
	void setRandomWizardPower();
	bool getPowerUsed();
	void setPowerUsed();

	void setWinnCords(const std::pair<int, int> cords);
	std::pair<int, int> getWinnCords() const;

	void ShowHand();
	Card PlayCard(int cardIndex);/// ii updataeaza vectorul de carti 
	bool HasCardAtIndex(int cardIndex);
	void UseAbilty();
	void AddCard(Card card);
	std::vector<Card>getCards() const;;
	/// 


	void AddToRemovedCards(const Card& card);
	void RemoveFromRemovedCards(const Card& card);
	const std::vector<Card>& GetRemovedCards() const;

	/// 
	void ClearCards();

	void setElementPowerUsed();
	bool getElementPowerUsed();
	Element_Mode::Putere getElementPower();


	bool isTurn = false;

	int selectedIndex = 0;

};

