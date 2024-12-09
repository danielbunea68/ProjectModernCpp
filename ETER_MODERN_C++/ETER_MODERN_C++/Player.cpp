#include "Player.h"

Player::Player(const Player& other)
{
	m_cards = other.m_cards;
	m_wizard_power = other.m_wizard_power;
	m_LifePoints = other.m_LifePoints;
	m_name=other.m_name;
	m_color=other.m_color;
	m_placedCardFaceDown = other.m_placedCardFaceDown;
	m_last_move = other.m_last_move;
	m_winncords = other.m_winncords;
	removedCards = other.removedCards;
	powerUsed = other.powerUsed;
}

Player::Player(const std::string& playerName) :
	m_name(playerName), m_LifePoints(100), m_placedCardFaceDown(false){}

Player& Player::operator=(const Player& other)
{
	if (this != &other) // Self-assignment check
	{
		m_cards = other.m_cards;
		m_wizard_power = other.m_wizard_power;
		m_LifePoints = other.m_LifePoints;
		m_name = other.m_name;
		m_color = other.m_color;
		m_placedCardFaceDown = other.m_placedCardFaceDown;
		m_last_move = other.m_last_move;
		m_winncords = other.m_winncords;
		removedCards = other.removedCards;
		powerUsed = other.powerUsed;
	}
	return *this;
}

Player::Player(Player&& other) noexcept
{
	m_cards = std::move(other.m_cards);
	m_wizard_power = std::move(other.m_wizard_power);
	m_LifePoints= other.m_LifePoints;
	m_name = std::move(other.m_name);
	m_color=std::move(other.m_color);
	m_placedCardFaceDown = other.m_placedCardFaceDown;
	m_last_move = std::move(other.m_last_move);
	m_winncords = std::move(other.m_winncords);
	removedCards = std::move(other.removedCards);
	powerUsed = other.powerUsed;
	other.m_LifePoints = 0;
	other.m_placedCardFaceDown = false;
	other.powerUsed = false;
}

Player& Player::operator=(Player&& other) noexcept
{
	if (this != &other) // Self-assignment check
	{
		m_cards = std::move(other.m_cards);
		m_LifePoints = other.m_LifePoints;
		m_wizard_power = std::move(other.m_wizard_power);
		m_name = std::move(other.m_name);
		m_color = std::move(other.m_color);
		m_placedCardFaceDown = other.m_placedCardFaceDown;
		m_last_move = std::move(other.m_last_move);
		m_winncords = std::move(other.m_winncords);
		removedCards = std::move(other.removedCards);
		powerUsed = other.powerUsed;

		// Reset the moved-from object to a valid state
		other.m_LifePoints = 0;
		other.m_placedCardFaceDown = false;
		other.powerUsed = false;
	}
	return *this;
}

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

void Player::setWinnCords(const std::pair<int, int> cords)
{
	m_winncords = cords;
}

std::pair<int, int> Player::getWinnCords() const
{
	return m_winncords;
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

std::vector<WizardPower> Player::assignedPowers;

void Player::setRandomWizardPower()
{
	static bool seeded = false;
	if (!seeded)
	{
		std::srand(static_cast<unsigned int>(std::time(0)));
		seeded = true;
	}

	int numPowers = static_cast<int>(WizardPower::MoveEdgeRow) + 1;

	WizardPower power;
	do
	{
		int randomIndex = std::rand() % numPowers;
		power = static_cast<WizardPower>(randomIndex);
	} while (std::find(assignedPowers.begin(), assignedPowers.end(), power) != assignedPowers.end());

	m_wizard_power = power;
	assignedPowers.push_back(power);
}

bool Player::getPowerUsed()
{
	return powerUsed;
}

void Player::setPowerUsed()
{
	powerUsed = true;
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

std::vector<Card> Player::getCards() const
{
	return m_cards;
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


