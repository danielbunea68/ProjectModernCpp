#include "Player.h"

Player::Player(const std::string& playerName, const Card& wizardCard) :
	m_name(playerName), m_wizard(wizardCard), m_LifePoints(100), m_placedCardFaceDown(false){}

bool Player::CanPlaceCardFaceDown()
{
	return !m_placedCardFaceDown;
}

void Player::PlayedCardFaceDown()
{
	m_placedCardFaceDown = true;
}

std::string Player::getColor() const
{
	return m_color;
}

void Player::setColor(const std::string& color)
{
	m_color = color;
}

std::string Player::getName() const
{
	return m_name;
}

void Player::ShowHand()
{
	for (const auto& card : m_cards) {
		std::cout << card.getValue() << ' ';
	}
	std::cout << "\n";
}

void Player::setName(const std::string& name)
{
	m_name = name;
}

Card Player::PlayCard(int cardIndex)
{
	Card chosenCard = m_cards[cardIndex];
	m_cards.erase(m_cards.begin() + cardIndex);
	return chosenCard;
}

bool Player::HasCardAtIndex(int cardIndex)
{
	return cardIndex >= 0 && cardIndex < m_cards.size();
}

void Player::AddCard(Card card)
{
	m_cards.push_back(card);
}

void Player::ClearCards()
{
	m_cards.clear();
}


