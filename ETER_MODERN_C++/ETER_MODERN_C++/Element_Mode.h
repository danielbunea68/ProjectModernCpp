﻿#pragma once

#include <iostream>
#include <unordered_map>
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
	Board board;
	Player player1, player2;
	Player* currentPlayer;
	int blockedRowForNextTurn = -1;

	void SwitchTurn();

public:

	Element_Mode();
	Element_Mode(Putere putere);
	//Rule of Five 
	~Element_Mode();
	Element_Mode(const Element_Mode& other);
	Element_Mode& operator=(const Element_Mode& other);
	Element_Mode(Element_Mode&& other) noexcept;
	Element_Mode& operator=(Element_Mode&& other) noexcept;
	//Rule of Five ^^^
	void InitGame(std::string name1, std::string name2) = 0;
	void PlayGame() = 0;
	void ResetGame() = 0;

	void RemoveCard(int row, int col) = 0;
	void ReturnCardToPlayer(int row, int col) = 0;
	void CreatePit(int row, int col) = 0;


	Element_Mode(Putere putere);
	Putere GetTipPutere();
	void ActivatePower();
	void ActivateControlledExplosion();
	void  DestroyLastOpponentCard();
	void Flacari();
	void Lava();
	void DinCenusa();
	void Scantei();
	void Viscol();
	void Vijelie();
	void ActivateRafala(int row, int col, int targetRow, int targetCol);
	void ActivateMiraj(int row, int col, int cardIndex);
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
	void Avalansa(int row1, int col1, int row2, int col2);
};
