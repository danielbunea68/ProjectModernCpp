#pragma once
#include "Board.h"
#include "Player.h"
#include "IGame.h"
#include "Bomb.h"

class Game :public IGame
{

private:
	Board board;
	Player player1, player2;
	Player* currentPlayer;



public:
	Game();
	~Game() {}
	Game(const Game& other);
	Game& operator=(const Game& other);
	Game(Game&& other) noexcept;
	Game& operator=(Game&& other) noexcept;

	void RemoveCard(int row, int col) override;

	void ReturnCardToPlayer(int row, int col)override;

	void CreatePit(int row, int col)override;

	void InitGame(std::string name1, std::string name2)override;

	int GetScore(std::string color);

	Player* CurrentTurn() override;
	Player* PreviousTurn() override;

	Player* getPlayer1() {
		return &player1;
	}

	Player* getPlayer2() {
		return &player2;
	}

	bool IsDraw();

	void PlayGame()override;
	void ResetGame()override;
	Board getboard();
	void SwitchTurn();
	Board* getBoard() {
		return &board;
	}


	bool hasGivenBomb = false;

	void giveBomb(Player* player) {
		hasGivenBomb = true;
		Bomb* bomb = new Bomb();
		player->setBomb(bomb);
	}

	void useBomb(Player* player) {
		auto bomb = player->getBomb();
		player->hasBomb = false;
		player->selectedBomb = false;

		for (int i = 0; i < bomb->board.size(); i++) {
			for (int j = 0; j < bomb->board.size(); j++) {
				char action = bomb->board[i][j];
				switch (action)
				{
				case 'r':
					RemoveCard(i, j);
					break;
				case 'u':
					ReturnCardToPlayer(i, j);
					break;
				default:
					break;
				}
			}
		}

		/*Explosion_Card explosion_card(board.GetSize());

		explosion_card.activateExplosion();
		std::vector<std::pair<char, std::pair<int, int>>> coords;
		std::vector<std::pair<char, std::pair<int, int>>> left_coords;
		std::vector<std::pair<char, std::pair<int, int>>> right_coords;

		coords = explosion_card.AppliedPositions();

		for (const auto& pos : coords)
		{
			char bombType = pos.first;
			int row = pos.second.first;
			int col = pos.second.second;

			int right_r = col;
			int right_c = board.GetSize() - 1 - row;
			int left_r = board.GetSize() - 1 - col;
			int left_c = row;

			right_coords.push_back({ bombType, {right_r, right_c} });
			left_coords.push_back({ bombType, {left_r, left_c} });
		}
		QPoint mousePosb = event->pos();
		auto cellPositionb = boardCellFromMouse(mousePos);

		int rowb = cellPositionb.x();
		int colb = cellPositionb.y();

		char power;

		if (isCoordInVector(rowb, colb, coords) != 'C')
			power = isCoordInVector(rowb, colb, coords);
		else if (isCoordInVector(rowb, colb, right_coords))
			power = isCoordInVector(rowb, colb, right_coords);
		else
			power = isCoordInVector(rowb, colb, left_coords);


		switch (power)
		{
		case 'r':
			game->RemoveCard(rowb, colb);
			break;
		case 'u':
			game->ReturnCardToPlayer(rowb, colb);
			break;
		case 'p':
			game->CreatePit(rowb, colb);
			break;
		default:
			break;
		}*/
	}
};


