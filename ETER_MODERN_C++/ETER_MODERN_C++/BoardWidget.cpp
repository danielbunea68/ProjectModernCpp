﻿#include "BoardWidget.h"
#include <QDebug>

BoardWidget::BoardWidget(QWidget* parent)
	: QWidget(parent), board(nullptr) {}

void BoardWidget::setBoard(Board* board) {
	this->board = board;
	boardSize = board->GetSize();
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
	for (int row = 0; row < board->GetSize(); ++row) {
		for (int col = 0; col < board->GetSize(); ++col) {
			if (!board->IsEmpty(row, col)) {
				Card card = board->TopCard(row, col);

				// Definirea dreptunghiului celulei
				QRect cell(col * cellWidth, row * cellHeight, cellWidth, cellHeight);

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

				// Desenează bordura neagră în jurul celulei
				painter.setPen(Qt::black);
				painter.drawRect(cell);

			}
		}
	}
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
	// TODO: Sa ai acces la cartea selectata de utilizator
	// apoi incearca sa o pui
	// poate vei avea nevoie de o referinta sau un pointer catre game
	// va afisa un mesaj scurt daca reuseste sau nu sa puna carte, poti desena oriunde mesajul
}

void BoardWidget::mouseReleaseEvent(QMouseEvent* event) {
	// TODO: Maybe delete this
}

