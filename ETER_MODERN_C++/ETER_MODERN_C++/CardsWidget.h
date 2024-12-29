#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Card.h"
#include "QMouseEvent"
class CardsWidget :public QWidget
{
	Q_OBJECT
public:
	explicit CardsWidget(QWidget* parent = nullptr);

	void setCards(Player* player);


protected:
	void paintEvent(QPaintEvent* event) override;
	void DrawQueue(QPainter& painter);
	void DrawCards(QPainter& painter);
	void mousePressEvent(QMouseEvent* event) override;

	void DrawCard(QPainter& painter, int i);
	void DrawBomb(QPainter& painter, int i);
	void DrawPower(QPainter& painter, int i);

	QString enumToString(WizardPower value) {
		switch (value) {
		case WizardPower::MoveEdgeRow: return "8";
		case WizardPower::RemoveOpponentCard: return "1";
		case WizardPower::RemoveRow: return "5";
		case WizardPower::CoverOpponentCard: return "2";
		case WizardPower::CreatePit: return "6";
		case WizardPower::MoveOwnStack: return "3";
		case WizardPower::ExtraEterCard: return "7";
		case WizardPower::MoveOpponentStack: return "4";
		default: return "Unknown";
		}

	}
private:

	int cellWidth{};
	int cellHeight{};
	int boardSize{};

	Player* player;
};

