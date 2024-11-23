#pragma once
#include <string>
#include <utility>

class Card
{
private:
	int m_value;
	std::string m_type;
	bool m_IsFaceDown;
	std::string m_color;

public:
	Card(int value = 0, const std::string& color = "red", const std::string& type = "normal");
	~Card();
	Card(const Card& other);
	Card& operator=(const Card& other);
	Card(Card&& other)noexcept;
	Card& operator=(Card&& other)noexcept;
	int getValue() const;
	std::string getType() const;
	bool getIsFaceDown() const;
	std::string getColor() const;
	void setValue(int newValue);
	void setType(const std::string& newType);
	void setFaceDown(bool faceDown);
	void setColor(const std::string& color);
	void flip();
	bool isPlayable() const;
	bool operator!=(const Card& other) const;
	bool operator==(const Card& other) const;
};


