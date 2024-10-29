#pragma once
#include <vector>
#include"Card.h"
class Board 
{
	std::vector < std::vector < Card >> board= {};
	std::vector<std::vector<bool>> marcat ;
public:
	void marcare();/// marcam matricea dupa ce punem o carte ;

};
/////
