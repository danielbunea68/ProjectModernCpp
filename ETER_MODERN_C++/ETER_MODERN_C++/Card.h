#pragma once
#include <string>
class Card
{
private:
	int m_value;
	std::string m_type;
	bool m_IsFaceDown;
	std::string m_color;

public:
	Card(int value = 0, const std::string& color = "red", const std::string& type = "normal");
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
};


