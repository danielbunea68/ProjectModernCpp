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
		case WizardPower::MoveEdgeRow: return "MoveEdgeRow";
		case WizardPower::RemoveOpponentCard: return "RemoveOpponentCard";
		case WizardPower::RemoveRow: return "RemoveRow";
		case WizardPower::CoverOpponentCard: return "CoverOpponentCard";
		case WizardPower::CreatePit: return "CreatePit";
		case WizardPower::MoveOwnStack: return "MoveOwnStack";
		case WizardPower::ExtraEterCard: return "ExtraEterCard";
		case WizardPower::MoveOpponentStack: return "MoveOpponentStack";
		default: return "Unknown";
		}

	}
private:

	int cellWidth{};
	int cellHeight{};
	int boardSize{};

	Player* player;
};

