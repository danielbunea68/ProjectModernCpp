#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <vector>
#include "Board.h"
#include "Card.h"

class BoardWidget : public QWidget {
    Q_OBJECT

public:
    explicit BoardWidget(QWidget* parent = nullptr);

    void setBoard(Board* board);
    void setPlayerHand(const std::vector<Card>& hand);

signals:
    void cardPlaced(int row, int col, Card card);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Board* board;
    std::vector<Card> playerHand;

    int selectedCardIndex = -1;
    QPoint dragStartPosition;
    QRect cardArea(int index) const; // Helper to determine card position in hand
    QPoint boardCellFromMouse(const QPoint& pos) const;
};