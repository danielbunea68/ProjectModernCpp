#pragma once
#include <vector>
#include <map>
#include <ctime>  

class Bomb
{
public:
	Bomb() {
		std::map<int, std::vector<std::vector<char>>> bombs;
		bombs[0] = { {' ', ' ', 'r'}, {' ', 'u', ' '}, {'r', ' ', ' '} };
		bombs[1] = { {' ','u',' '},{'r',' ',' '},{' ',' ','u'} };
		bombs[2] = { {'r','u',' '},{' ',' ',' '},{' ','r',' '} };
		bombs[3] = { {'u',' ',' '},{' ','r','r'},{' ',' ',' '} };

		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		int randomIndex = std::rand() % 4;
		id = randomIndex;
		board = bombs[randomIndex];
	}

	std::vector<std::vector<char>> board;
	int id = -1;

	int getId() {
		return id;
	}
};

