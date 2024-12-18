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
	int angle = 0;

	int getId() {
		return id;
	}

	int getRotationAngle() {
		return angle;
	}

	void rotateLeft() {
		angle = (angle + 270) % 360;
		int rows = board.size();
		int cols = board[0].size();

		std::vector<std::vector<char>> rotated(cols, std::vector<char>(rows, ' '));

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				rotated[cols - 1 - j][i] = board[i][j];
			}
		}
		board = rotated;

	}

	void rotateRight() {
		angle = (angle + 90) % 360;
		int rows = board.size();
		int cols = board[0].size();

		std::vector<std::vector<char>> rotated(cols, std::vector<char>(rows, ' '));

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				rotated[j][rows - 1 - i] = board[i][j];
			}
		}
		board = rotated;
	}
};

