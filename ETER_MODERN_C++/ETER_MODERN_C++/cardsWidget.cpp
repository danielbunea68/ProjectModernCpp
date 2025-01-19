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
	int row = 2; 
	int y = row * cellHeight; 

	
	painter.drawLine(0, y, width(), y);

}
void CardsWidget::DrawCards(QPainter& painter)
{
	int n = player->getCards().size();
	for (int i = 0; i <= n+1; ++i) {
		if (i == n) {
			DrawPower(painter, i);
		}
		else if (i == n + 1)
		{
			DrawBomb(painter, i);
		}
		else  {
			DrawCard(painter, i);
		}
	}
}

void CardsWidget::DrawCard(QPainter& painter, int i) {
	Card card = player->getCards()[i];

	
	QRect cell(i * cellWidth, 0, cellWidth, cellHeight);

	
	QString imagePath = "./images/" + QString::number(card.getValue()) + "_" + QString::fromStdString(card.getColor()) + ".png";
	QPixmap cardImage(imagePath);

	
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

	painter.setPen(Qt::black);
	painter.drawRect(cell);

	if (i == player->selectedIndex && player->isTurn) {
		painter.setPen(QPen(Qt::green, 3));
		painter.drawRect(cell);
	}
}

void CardsWidget::DrawPower (QPainter& painter, int i) {
	if (!player->hasPower) return;

	auto power = player->getWizardPower();

	QRect cell(i * cellWidth, 0, cellWidth, cellHeight);


	QString imagePath = "./images/power_" + enumToString(power) + ".png";
	QPixmap cardImage(imagePath);


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
		QString cardValue = "power_" + enumToString(power);
		painter.drawText(cell, Qt::AlignCenter, cardValue);
	}


	painter.setPen(Qt::black);
	painter.drawRect(cell);

	if (player->selectedBomb && player->isTurn) {
		painter.setPen(QPen(Qt::green, 3));
		painter.drawRect(cell);
	}
}

void CardsWidget::DrawBomb(QPainter& painter, int i)
{
	if (!player->hasBomb) return;

	auto bomb = player->getBomb();


	QRect cell(i * cellWidth, 0, cellWidth, cellHeight);


	QString imagePath = "./images/bomb_" + QString::number(bomb->getId()) + ".png";
	QPixmap cardImage(imagePath);

	
	if (!cardImage.isNull()) {
		int rotationAngle = bomb->getRotationAngle(); 

		painter.save();

		painter.translate(cell.center());

		painter.rotate(rotationAngle);

		painter.translate(-cell.center());

		painter.drawPixmap(cell, cardImage.scaled(cell.size(), Qt::KeepAspectRatio));

		painter.restore();
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

	painter.setPen(Qt::black);
	painter.drawRect(cell);

	if (player->selectedBomb && player->isTurn) {
		painter.setPen(QPen(Qt::green, 3));
		painter.drawRect(cell);
	}
}

void CardsWidget::mousePressEvent(QMouseEvent* event)
{
	int clickedIndex = event->position().x() / cellWidth;
	int n = player->getCards().size();
	if (clickedIndex >= 0 && clickedIndex < n)
	{
		player->selectedIndex = clickedIndex;
		player->selectedBomb = false;
		update();
	}
	else if (clickedIndex == n + 1 && player->hasBomb) {
		player->selectedIndex = -1;
		player->selectedBomb = true;
		player->selectedPower = false ;
		update();
	}
	else if (clickedIndex == n && player->hasPower)
	{
		player->selectedIndex = -1;
		player->selectedPower = true;
		player->selectedBomb = false;
		update();

	}
}