#pragma once
#include "Board.h"
#include "Player.h"
#include "IGame.h"
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

	Player* CurrentTurn() override;
	Player* PreviousTurn() override;

	Player* getPlayer1() {
		return &player1;
	}

	Player* getPlayer2() {
		return &player2;
	}

	void PlayGame()override;
	void ResetGame()override;
	Board getboard();
	void SwitchTurn();
	Board* getBoard() {
		return &board;
	}
};


