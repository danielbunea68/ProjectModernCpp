﻿#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <random>
#include <memory>
#include "IGame.h"
#include "Board.h"
#include "Player.h"



class Element_Mode :public IGame
{
public:
	enum class Putere
	{
		ExplozieControlata,
		Distrugere,
		Flacari,
		Lava,
		DinCenusa,
		Scantei,
		Viscol,
		Vijelie,
		Uragan,
		Rafala,
		Miraj,
		Furtuna,
		Maree,
		Ceata,
		Val,
		VartejDeApa,
		Tsunami,
		Cascada,
		Sprijin,
		Cutremur,
		Sfaramare,
		Granite,
		Avalansa,
		Bolovan
	};

private:
	Putere tipPutere;

	std::unique_ptr<Player> player1;
	std::unique_ptr<Player> player2;
	Player* currentPlayer = nullptr;
	std::unordered_set<Putere> usedPowers;
	std::vector<Putere> availablePowers;
	Board board;

	int blockedRowForNextTurn = -1;
	bool gameWithIllusions;
	bool player1UsedAnyPower = false;
	bool player2UsedAnyPower = false;
	int player1Wins = 0, player2Wins = 0;

public:

	std::string GetPowerName(Putere power);
	std::string GetPowerDescription(Putere power);
	void InitializePowers();
	bool CanUsePower(Putere power);
	void UsePower(Putere power);
	std::vector<Putere> GetAvailablePowers();

	void SwitchTurn();
	Element_Mode();
	Element_Mode(Putere putere);

	~Element_Mode();
	Element_Mode(const Element_Mode& other) = delete;
	Element_Mode& operator=(const Element_Mode& other) = delete;
	Element_Mode(Element_Mode&& other) noexcept;
	Element_Mode& operator=(Element_Mode&& other) noexcept;


	void InitGame(std::string name1, std::string name2) override;
	void PlayGame() override;
	void ResetGame() override;

	void RemoveCard(int row, int col) override;
	void ReturnCardToPlayer(int row, int col) override;
	void CreatePit(int row, int col);

	Player* CurrentTurn() override;
	Player* PreviousTurn() override;

	Putere GetTipPutere();
	void ActivatePower(Putere power);
	void ActivateControlledExplosion();
	void  DestroyLastOpponentCard();
	void Flacari();
	void Lava();
	void DinCenusa();
	void Scantei();
	void Viscol();
	void Vijelie();
	void ActivateRafala(int row, int col, int targetRow, int targetCol);
	void ActivateMiraj(int cardIndex);
	void ActivateFurtuna();
	void Uragan(int row);
	void SwapStacks();
	void Ceata();
	void Val();
	void VartejDeApa();
	void ActivateTsunami();
	void Cutremur();
	void Cascada();
	void Sprijin();
	void Sfaramare();
	void Granita();
	void Avalansa(int row1, int col1, int row2, int col2);
	void Bolovan(int row, int col, int cardIndex);
};