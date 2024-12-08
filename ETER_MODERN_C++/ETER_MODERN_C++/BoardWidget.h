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

signals:
    void cardPlaced(int row, int col, Card card);

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

    Board* board;
    QPoint boardCellFromMouse(const QPoint& pos) const;
};