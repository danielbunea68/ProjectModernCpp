#include "Player.h"

Player::Player(const std::string& playerName, const Card& wizardCard) : 
	m_name(playerName), m_wizard(wizardCard), m_LifePoints(100) {}

std::string Player::getName() const
{
	return m_name;
}

void Player::setName(const std::string& name)
{
	m_name = name;
}


