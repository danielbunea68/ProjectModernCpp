﻿#pragma once
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
	}
};


