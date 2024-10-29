#include "Card.h"

Card::Card(int value, const std::string& type) : 
	m_value(value), m_type(type), m_IsFaceDown(false) {}

int Card::getValue() const
{
	return m_value;
}

std::string Card::getType() const
{
	return m_type;
}

bool Card::getIsFaceDown() const
{
	return m_IsFaceDown;
}

void Card::setValue(int value)
{
	m_value = value;
}

void Card::setType(const std::string& type)
{
	m_type = type;
}

void Card::setFaceDown(bool IsFaceDown)
{
	m_IsFaceDown = IsFaceDown;
}

void Card::flip()
{
	m_IsFaceDown = !m_IsFaceDown;
}

bool Card::isPlayable() const
{
	return !m_IsFaceDown;
}











