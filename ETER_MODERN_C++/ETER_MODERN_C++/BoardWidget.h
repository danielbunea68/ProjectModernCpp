#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <vector>
#include "Board.h"
#include "Card.h"
#include "CardsWidget.h"
#include "Game.h"

class BoardWidget : public QWidget {
    Q_OBJECT

public:
    explicit BoardWidget(QWidget* parent = nullptr);

    void setBoard(Board* board);
    void setCardsWidget(CardsWidget* widget);
    void setGame(Game* gameInstance);
signals:
    void cardPlaced(int row, int col, Card card);
    void requestGlobalUpdate();
    void playerWon(const QString& winnerName);
    void isDraw(const QString& massage);
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void DrawBoard(QPainter &painter);
    void DrawCards(QPainter& painter);


private:
    int cellWidth{};
    int cellHeight{};
    int boardSize{};
    Game* game;
    Board board;
    QPoint boardCellFromMouse(const QPoint& pos) const;
    CardsWidget* cardsWidget;
};