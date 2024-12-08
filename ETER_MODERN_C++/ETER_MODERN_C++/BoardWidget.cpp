#include "BoardWidget.h"
#include <QDebug>

BoardWidget::BoardWidget(QWidget* parent)
    : QWidget(parent), board(nullptr), selectedCardIndex(-1) {}

void BoardWidget::setBoard(Board* board) {
    this->board = board;
    update();
}

void BoardWidget::setPlayerHand(const std::vector<Card>& hand) {
    playerHand = hand;
    update();
}

void BoardWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int rows = 3, cols = 3;
    int cellWidth = width() / cols;
    int cellHeight = height() / rows;

    // Draw the board
    for (int i = 0; i <= rows; ++i) {
        painter.drawLine(0, i * cellHeight, width(), i * cellHeight); // Horizontal
    }
    for (int i = 0; i <= cols; ++i) {
        painter.drawLine(i * cellWidth, 0, i * cellWidth, height()); // Vertical
    }

    // Draw cards on the board
    if (board) {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (!board->IsEmpty(row, col)) {
                    Card card = board->TopCard(row, col);
                    QRect cell(col * cellWidth, row * cellHeight, cellWidth, cellHeight);
                    painter.drawText(cell, Qt::AlignCenter, QString::fromStdString(card.getColor()));
                }
            }
        }
    }

    // Draw the player's hand
    int handY = height() - 100;
    //int cardWidth = width() / playerHand.size();
    int cardWidth = 50;
    for (size_t i = 0; i < playerHand.size(); ++i) {
        QRect cardRect(i * cardWidth, handY, cardWidth, 100);
        painter.drawRect(cardRect);
        painter.drawText(cardRect, Qt::AlignCenter, QString::number(playerHand[i].getValue()));
    }
}

QRect BoardWidget::cardArea(int index) const {
    int cardWidth = width() / playerHand.size();
    int handY = height() - 100;
    return QRect(index * cardWidth, handY, cardWidth, 100);
}

QPoint BoardWidget::boardCellFromMouse(const QPoint& pos) const {
    int cellWidth = width() / 3;
    int cellHeight = (height() - 100) / 3;
    int col = pos.x() / cellWidth;
    int row = pos.y() / cellHeight;
    return QPoint(col, row);
}
void BoardWidget::mousePressEvent(QMouseEvent* event) {
    QPoint pos = event->pos();
    for (size_t i = 0; i < playerHand.size(); ++i) {
        if (cardArea(i).contains(pos)) {
            selectedCardIndex = i;
            dragStartPosition = pos;
            break;
        }
    }
}

void BoardWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (selectedCardIndex == -1)
        return;

    QPoint releasePos = event->pos();
    QPoint cell = boardCellFromMouse(releasePos);

    if (board && board->IsValidPosition(cell.y(), cell.x()) && board->IsEmpty(cell.y(), cell.x())) {
        emit cardPlaced(cell.y(), cell.x(), playerHand[selectedCardIndex]);
        playerHand.erase(playerHand.begin() + selectedCardIndex); // Remove card from hand
        selectedCardIndex = -1;
        update();
    }
    else {
        qDebug() << "Invalid position or cell not empty";
    }
}