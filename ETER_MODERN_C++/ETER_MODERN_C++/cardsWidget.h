#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Card.h"
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

private :

    int cellWidth{};
    int cellHeight{};
    int boardSize{};

    std::vector<Card> cards_of_player;
    QPoint boardCellFromMouse(const QPoint& pos) const;
};

