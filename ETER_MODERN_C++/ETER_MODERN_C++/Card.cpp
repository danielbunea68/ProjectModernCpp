#include "Card.h"


Card::Card(int value, const std::string& color, const std::string& type) :
	m_value(value), m_color(color), m_type(type), m_IsFaceDown(false) {}

Card::~Card()
{
}

Card::Card(const Card& other) : 
m_value(other.m_value),
m_type(other.m_type),
m_IsFaceDown(other.m_IsFaceDown),
m_color(other.m_color) {}

Card& Card::operator=(const Card& other)
{
	if (this != &other) 
	{
		m_value = other.m_value;
		m_type = other.m_type;
		m_IsFaceDown = other.m_IsFaceDown;
		m_color = other.m_color;
	}
	return *this;
}

Card::Card(Card&& other) noexcept :
m_value(other.m_value),
m_type(std::move(other.m_type)),
m_IsFaceDown(other.m_IsFaceDown),
m_color(std::move(other.m_color)) 
{
	other.m_value = 0;
	other.m_IsFaceDown = false;
}

Card& Card::operator=(Card&& other) noexcept
{
	if (this != &other) 
	{
		m_value = other.m_value;
		m_type = std::move(other.m_type);
		m_IsFaceDown = other.m_IsFaceDown;
		m_color = std::move(other.m_color);

		other.m_value = 0;
		other.m_IsFaceDown = false;
	}
	return *this;
}



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

std::string Card::getColor() const
{
	return m_color;
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

void Card::setColor(const std::string& color)
{
	m_color = color;
}

void Card::flip()
{
	m_IsFaceDown = !m_IsFaceDown;
}

bool Card::isPlayable() const
{
	return !m_IsFaceDown;
}

bool Card::operator!=(const Card& other) const
{
	return !(*this == other);
}

bool Card::operator==(const Card& other) const
{
	return m_color == other.getColor() && m_value == other.getValue();
}