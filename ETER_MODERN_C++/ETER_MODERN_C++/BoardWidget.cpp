﻿#include "BoardWidget.h"
#include <QDebug>

BoardWidget::BoardWidget(QWidget* parent)
	: QWidget(parent) {}

void BoardWidget::setBoard(Board* board) {
}

void BoardWidget::setCardsWidget(CardsWidget* widget)
{
	this->cardsWidget = widget;
}

void BoardWidget::setGame(Game* gameInstance)
{
	this->game = gameInstance;
	this->board = gameInstance->getboard();
	boardSize = board.GetSize();
	update();
}

void BoardWidget::DrawBoard(QPainter& painter)
{
	for (int i = 0; i <= boardSize; ++i) {
		painter.drawLine(0, i * cellHeight, width(), i * cellHeight); // Horizontal
	}
	for (int i = 0; i <= boardSize; ++i) {
		painter.drawLine(i * cellWidth, 0, i * cellWidth, height()); // Vertical
	}
}

void BoardWidget::DrawCards(QPainter& painter)
{
	for (int row = 0; row < boardSize; ++row) {
		for (int col = 0; col < boardSize; ++col) {
			if (!game->getboard().IsEmpty(row, col)) {
				Card card = game->getboard().TopCard(row, col);

				QString imagePath = "./images/" + QString::number(card.getValue()) + "_" + QString::fromStdString(card.getColor()) + ".png";
				QPixmap cardImage(imagePath);

				// Definirea dreptunghiului celulei
				QRect cell(col * cellWidth, row * cellHeight, cellWidth, cellHeight);

				if (!cardImage.isNull()) {
					painter.drawPixmap(cell, cardImage.scaled(cell.size(), Qt::KeepAspectRatio));
				}
				else {
					// Setează culoarea de fundal la culoarea cărții
					QColor backgroundColor(QString::fromStdString(card.getColor()));
					painter.fillRect(cell, backgroundColor);

					// Setează culoarea textului la alb
					painter.setPen(Qt::white);

					// Setează fontul mai mare
					QFont font = painter.font();
					font.setPointSize(16); // Ajustează mărimea fontului după necesități
					painter.setFont(font);

					// Desenează valoarea cărții în centrul celulei
					QString cardValue = QString::number(card.getValue());
					painter.drawText(cell, Qt::AlignCenter, cardValue);
				}

				// Desenează bordura neagră în jurul celulei
				painter.setPen(Qt::black);
				painter.drawRect(cell);
			}
		}
	}
}

char  BoardWidget::isCoordInVector(int row, int col, const std::vector<std::pair<char, std::pair<int, int>>>& coords)
{
	for (const auto& item : coords) {
		int coordRow = item.second.first;  // Extragem coordonata x
		int coordCol = item.second.second; // Extragem coordonata y

		if (coordRow == row && coordCol == col) {
			return item.first; // Găsit
		}
	}
	return 'C'; // Nu a fost găsit
}

void BoardWidget::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	cellWidth = width() / boardSize;
	cellHeight = height() / boardSize;

	DrawBoard(painter);
	DrawCards(painter);
}


QPoint BoardWidget::boardCellFromMouse(const QPoint& pos) const {
	int cellWidth = width() / boardSize;
	int cellHeight = height() / boardSize;
	int col = pos.y() / cellWidth;
	int row = pos.x() / cellHeight;
	return QPoint(col, row);
}
void BoardWidget::mousePressEvent(QMouseEvent* event) {
	QPoint mousePos = event->pos();
	auto cellPosition = boardCellFromMouse(mousePos);

	int row = cellPosition.x();
	int col = cellPosition.y();

	int selectedIndex = game->CurrentTurn()->selectedIndex;
	int handSize = game->CurrentTurn()->getCards().size();
	auto player = game->CurrentTurn();

	if (player->hasBomb && player->selectedBomb) {
		game->useBomb(player);
		player->hasBomb = false;
	}
	else if (player->hasPower && player->selectedPower)
	{
		game->usePower(player, row , col );
		player->hasPower = false;
	}

	else {
		if (selectedIndex < 0 || selectedIndex > handSize) return;
		Card selectedCard = game->CurrentTurn()->PlayCard(selectedIndex);

		if (!game->getBoard()->CanMakeMove(row, col, selectedCard)) return;
		game->getBoard()->MakeMove(row, col, selectedCard);
	}

	emit requestGlobalUpdate();


	if (!game->hasGivenBomb && game->getBoard()->CheckIsBomb())
	{
		game->giveBomb(player);
	}

	emit requestGlobalUpdate();

	if (game->getBoard()->CheckWinner(game->CurrentTurn()->getColor())) {
		emit playerWon(QString::fromStdString(game->CurrentTurn()->getName()));
	}
	else if (game->IsDraw()) {
		int score1 = game->GetScore(game->CurrentTurn()->getColor());
		int score2 = game->GetScore(game->PreviousTurn()->getColor());
		if (score1 > score2) {
			emit playerWon(QString::fromStdString(game->CurrentTurn()->getName()));
		}
		else if (score2 > score1) {
			emit playerWon(QString::fromStdString(game->PreviousTurn()->getName()));
		}
		else {
			emit playerWon(QString::fromStdString("It's a draw!"));
		}
	}
	else {
		game->SwitchTurn();
	}

}

void BoardWidget::mouseReleaseEvent(QMouseEvent* event) {
	// TODO: Maybe delete this
}

