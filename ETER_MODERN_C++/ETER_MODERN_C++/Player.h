#pragma once
#include "Card.h"
#include "Card.h"
#include "Element_Card.h"
class Player
{
	std::vector<Card> cards;
	std::vector<Element_Card > element_cards;
	int life_points;
	Card  wizard;/// enum 
	void PlayCard();/// ii updataeaza vectorul de carti 
	void UseAbilty();


};

