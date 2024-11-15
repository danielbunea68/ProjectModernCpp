#include "Player.h"

Player::Player(const std::string& playerName) :
	m_name(playerName), m_LifePoints(100), m_placedCardFaceDown(false){}

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

void Player::setLastMove(int row , int col)
{
	m_last_move= { row,col };
}

void Player::setRandomWizardPower()
{
	int randomIndex = std::rand() % static_cast<int>(WizardPower::MoveEdgeRow) + 1;
	m_wizard_power = static_cast<WizardPower>(randomIndex);
}

bool Player::getPowerUsed()
{
	return powerUsed;
}

void Player::setPowerUsed()
{
	powerUsed = true;
}

void Player::ShowHand()
{
	for (const auto& card : m_cards) {
		std::cout << card.getValue() << ' ';
	}
	std::cout << "\n";
}

std::pair<int, int> Player::getLastMove()
{
	return m_last_move;
}

void Player::setName(const std::string& name)
{
	m_name = name;
}

WizardPower Player::getWizardPower() const
{
	return m_wizard_power;
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

void Player::AddToRemovedCards(const Card& card)
{
	removedCards.push_back(card);
}

void Player::RemoveFromRemovedCards(const Card& card)
{
	auto it = std::find(removedCards.begin(), removedCards.end(), card);
	if (it != removedCards.end()) 
	{
		removedCards.erase(it);
	}
}

const std::vector<Card>& Player::GetRemovedCards() const
{
	return removedCards;
}

void Player::ClearCards()
{
	m_cards.clear();
}


