#include "CardsWidget.h"

CardsWidget::CardsWidget(QWidget* parent) : QWidget(parent), cards_of_player{} {}

void CardsWidget::setCards(Player* player)
{
	cards_of_player = player->getCards();

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

	cellWidth = width() / cards_of_player.size() ;
	cellHeight = cellWidth + 1;
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
	for (int i = 0; i < cards_of_player.size(); ++i) {

		Card card = cards_of_player[i];

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

		if (i == highlightedIndex) {
			painter.setPen(QPen(Qt::green, 3));
			painter.drawRect(cell);
		}
	}
}

/*
void CardsWidget::DrawCards(QPainter& painter)
{
	for (int i = 0; i < cards_of_player.size(); ++i) {

		Card card = cards_of_player[i];

		// Definirea dreptunghiului celulei
		QRect cell(i* cellWidth,0 * cellHeight, cellWidth, cellHeight);

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

		if (i == highlightedIndex)
		{
			painter.setPen(QPen(Qt::green, 3)); // Chenar roșu cu grosime de 3 pixeli
			painter.drawRect(cell);
		}

	}
}
*/
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
		highlightCard(clickedIndex); // Evidențiază cartea apăsată
	}
}
	


