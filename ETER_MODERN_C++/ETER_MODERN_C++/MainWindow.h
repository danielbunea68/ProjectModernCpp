#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QFrame>
#include "CardsWidget.h"
#include "BoardWidget.h"
#include "Game.h"
#include "Card.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);

private:
	BoardWidget* boardWidget;
	CardsWidget* cardsWidget;

	Game* game;

	void resetGame();

	void keyPressEvent(QKeyEvent* event) override
	{
		switch (event->key()) {
		case Qt::Key_Left:
			game->CurrentTurn()->rotateBomb("left");
			break;
		case Qt::Key_Right:
			game->CurrentTurn()->rotateBomb("right");
			break;
		default:
			QWidget::keyPressEvent(event);
			break;
		}
		update();
	}

private slots:
	void onCardPlaced(int row, int col, Card card);
	void showWinnerMessage(const QString& winnerName);
public slots:
	void handleGlobalUpdate();
};