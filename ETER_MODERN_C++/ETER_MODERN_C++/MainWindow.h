#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QFrame>

#include "BoardWidget.h"
#include "Game.h"
#include "Card.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    BoardWidget* boardWidget;
    Game game;

private slots:
    void onCardPlaced(int row, int col, Card card);
};