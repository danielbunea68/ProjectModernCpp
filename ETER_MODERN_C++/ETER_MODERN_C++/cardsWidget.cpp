#include "CardsWidget.h"

CardsWidget::CardsWidget(QWidget* parent) : QWidget(parent), cards_of_player{}, player(nullptr) {}

void CardsWidget::setCards(Player* player)
{
	this->player = player;
	cards_of_player = player->getCards();
	cellWidth = width() / cards_of_player.size();
	cellHeight = cellWidth + 1;
}

Card CardsWidget::getSelectedCard()
{
	if (highlightedIndex >= 0 && highlightedIndex < cards_of_player.size()) {
		Card selectedCard = cards_of_player[highlightedIndex];
		cards_of_player.erase(cards_of_player.begin() + highlightedIndex); // Elimină cartea selectată
		highlightedIndex = -1; // Resetează selecția
		update(); // Reactualizează desenul
		return selectedCard;
	}
	return Card();
}

void CardsWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);


	//cellWidth = 196;
	//cellHeight = 196;

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
	for (int i = 0; i < player->getCards().size(); ++i) {

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
}


void CardsWidget::highlightCard(int index)
{
	highlightedIndex = index;
	update();
}

void CardsWidget::mousePressEvent(QMouseEvent* event)
{
	int clickedIndex = event->position().x() / cellWidth; // Determină indexul pe baza poziției x a click-ului

	if (clickedIndex >= 0 && clickedIndex < cards_of_player.size())
	{
		//highlightCard(clickedIndex); // Evidențiază cartea apăsată
		player->selectedIndex = clickedIndex;
	}
}



