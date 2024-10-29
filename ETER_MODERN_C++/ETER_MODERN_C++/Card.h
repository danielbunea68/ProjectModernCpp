#pragma once
#include <string>
class Card
{
private:
	int m_value;
	std::string m_type;
	bool m_IsFaceDown; 

public:

	Card(int value = 0, const std::string& type = "normal");

	int getValue() const;
	std::string getType() const;
	bool getIsFaceDown() const;

	void setValue(int newValue);
	void setType(const std::string& newType);
	void setFaceDown(bool faceDown);

	void flip();              
	bool isPlayable() const;  
};

