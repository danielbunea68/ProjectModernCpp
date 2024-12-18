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
public :
    explicit CardsWidget(QWidget* parent = nullptr);

    void setCards(Player*player);


protected:
    void paintEvent(QPaintEvent* event) override;
    void DrawQueue(QPainter& painter);
    void DrawCards(QPainter& painter);
    void mousePressEvent(QMouseEvent* event)override;

    void DrawCard(QPainter& painter, int i);
    void DrawBomb(QPainter& painter, int i);
private :

    int cellWidth{};
    int cellHeight{};
    int boardSize{};

    Player* player;
};

