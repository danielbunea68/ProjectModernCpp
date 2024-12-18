#include "CardsWidget.h"

CardsWidget::CardsWidget(QWidget* parent) : QWidget(parent), player(nullptr) {}

void CardsWidget::setCards(Player* player)
{
	this->player = player;
	cellWidth = width() / (player->getCards().size() - 1);
	cellHeight = cellWidth + 1;
}

void CardsWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	DrawQueue(painter);
	DrawCards(painter);

}

void CardsWidget::DrawQueue(QPainter& painter)
{
	int row = 2; // Poziția rândului (0-indexat)
	int y = row * cellHeight; // Calculăm poziția verticală

	// Desenăm linia orizontală pe poziția 'y'
	painter.drawLine(0, y, width(), y); // Linia orizontală de-a lungul întregii lățimi

}
void CardsWidget::DrawCards(QPainter& painter)
{
	int n = player->getCards().size();
	for (int i = 0; i <= n; ++i) {
		if (i == n) {
			DrawBomb(painter, i);
		}
		else {
			DrawCard(painter, i);
		}
	}
}

void CardsWidget::DrawCard(QPainter& painter, int i) {
	Card card = player->getCards()[i];

	// Definirea dreptunghiului celulei
	QRect cell(i * cellWidth, 0, cellWidth, cellHeight);

	// Încarcă imaginea corespunzătoare valorii și culorii
	QString imagePath = "./images/" + QString::number(card.getValue()) + "_" + QString::fromStdString(card.getColor()) + ".png";
	QPixmap cardImage(imagePath);

	// Desenează imaginea dacă există, altfel desenează fundalul și valoarea
	if (!cardImage.isNull()) {
		painter.drawPixmap(cell, cardImage.scaled(cell.size(), Qt::KeepAspectRatio));
	}
	else {
		QColor backgroundColor(QString::fromStdString(card.getColor()));
		painter.fillRect(cell, backgroundColor);
		painter.setPen(Qt::white);

		QFont font = painter.font();
		font.setPointSize(16);
		painter.setFont(font);

		QString cardValue = QString::number(card.getValue());
		painter.drawText(cell, Qt::AlignCenter, cardValue);
	}

	// Desenează bordura neagră în jurul celulei
	painter.setPen(Qt::black);
	painter.drawRect(cell);

	if (i == player->selectedIndex && player->isTurn) {
		painter.setPen(QPen(Qt::green, 3));
		painter.drawRect(cell);
	}
}

void CardsWidget::DrawBomb(QPainter& painter, int i) {
	if (!player->hasBomb) return;

	auto bomb = player->getBomb();

	// Definirea dreptunghiului celulei
	QRect cell(i * cellWidth, 0, cellWidth, cellHeight);

	// Încarcă imaginea corespunzătoare valorii și culorii
	QString imagePath = "./images/bomb_" + QString::number(bomb->getId()) + ".png";
	QPixmap cardImage(imagePath);

	// Desenează imaginea dacă există, altfel desenează fundalul și valoarea
	if (!cardImage.isNull()) {
		painter.drawPixmap(cell, cardImage.scaled(cell.size(), Qt::KeepAspectRatio));
	}
	else {
		QColor backgroundColor(QString::fromStdString("white"));
		painter.fillRect(cell, backgroundColor);
		painter.setPen(Qt::white);

		QFont font = painter.font();
		font.setPointSize(16);
		painter.setFont(font);

		painter.setPen(Qt::black);
		QString cardValue = QString::fromStdString("bomb_" + std::to_string(bomb->getId()));
		painter.drawText(cell, Qt::AlignCenter, cardValue);
	}

	// Desenează bordura neagră în jurul celulei
	painter.setPen(Qt::black);
	painter.drawRect(cell);

	if (player->selectedBomb && player->isTurn) {
		painter.setPen(QPen(Qt::green, 3));
		painter.drawRect(cell);
	}
}

void CardsWidget::mousePressEvent(QMouseEvent* event)
{
	int clickedIndex = event->position().x() / cellWidth; // Determină indexul pe baza poziției x a click-ului
	int n = player->getCards().size();
	if (clickedIndex >= 0 && clickedIndex < n)
	{
		player->selectedIndex = clickedIndex;
		player->selectedBomb = false;
		update();
	}
	else if (clickedIndex == n && player->hasBomb) {
		player->selectedIndex = -1;
		player->selectedBomb = true;
		update();
	}
}



