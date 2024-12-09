#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>   
#include <ctime> 
#include <algorithm>

#include "Card.h"

class Player
{
private:
	std::vector<Card> m_cards;
	//std::vector<Element_Card> m_ElementCards;
	int m_LifePoints;
	std::string m_name;
	std::string m_color;
	bool m_placedCardFaceDown;
	std::pair<int, int> m_last_move;
	std::vector<Card> removedCards;
	std::pair<int, int> m_winncords;
public:
	bool powerUsed= false ;
	

public:

	Player()=default;
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
	void setLastMove(int row , int col);
	std::pair<int, int> getLastMove();
	void setName(const std::string& newName);

	void setWinnCords(const std::pair<int,int> cords);
	std::pair<int, int> getWinnCords() const ;

	void ShowHand();
	Card PlayCard(int cardIndex);/// ii updataeaza vectorul de carti 
	bool HasCardAtIndex(int cardIndex);
	void UseAbilty();
	void AddCard(Card card);

	/// 
	

	void AddToRemovedCards(const Card& card);
	void RemoveFromRemovedCards(const Card& card);
	const std::vector<Card>& GetRemovedCards() const;

	/// 
	void ClearCards();


};

