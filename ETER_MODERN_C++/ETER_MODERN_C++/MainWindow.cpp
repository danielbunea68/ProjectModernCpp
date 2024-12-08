#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), game() {
    // Creează un widget principal pentru layout
    QWidget* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    // Creează un layout orizontal
    QHBoxLayout* layout = new QHBoxLayout(mainWidget);

    // Creează un widget pentru "board" (partea din stânga)
    BoardWidget* boardWidget = new BoardWidget();
    boardWidget->setStyleSheet("background-color: lightblue;");

    // Creează un alt widget pentru partea din dreapta
    QFrame* rightWidget = new QFrame();
    rightWidget->setStyleSheet("background-color: lightgray;");

    // Adaugă widget-urile în layout cu proporții (1:1 pentru jumătate/jumătate)
    layout->addWidget(boardWidget, 1);   // Ocupă jumătatea din stânga
    layout->addWidget(rightWidget, 1);   // Ocupă jumătatea din dreapta

    // Setează layout-ul principal
    mainWidget->setLayout(layout);


    //connect(boardWidget, &BoardWidget::cardPlaced, this, &MainWindow::onCardPlaced);
}

void MainWindow::onCardPlaced(int row, int col, Card card) {
      // if (game.getBoard().MakeMove(row, col, card)) {
        //boardWidget->setPlayerHand(game.CurrentTurn()->getHand());
        //game.SwitchTurn();
        //boardWidget->update();
    //}
}