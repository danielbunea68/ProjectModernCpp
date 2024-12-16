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
    Card getSelectedCard();


protected:
    void paintEvent(QPaintEvent* event) override;
    void DrawQueue(QPainter& painter);
    void DrawCards(QPainter& painter);
    void highlightCard(int index);
    void mousePressEvent(QMouseEvent* event)override;

private :

    int cellWidth{};
    int cellHeight{};
    int boardSize{};
    int highlightedIndex = -1;

    Player* player;
    std::vector<Card> cards_of_player;
    QPoint boardCellFromMouse(const QPoint& pos) const;
};

