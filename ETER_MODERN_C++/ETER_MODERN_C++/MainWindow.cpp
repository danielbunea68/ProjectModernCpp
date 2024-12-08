#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), game() {
    // Creeaz? un widget principal pentru layout
    QWidget* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    // Creeaz? un layout orizontal
    QHBoxLayout* layout = new QHBoxLayout(mainWidget);

    // Creeaz? un widget pentru "board" (partea din stânga)
    BoardWidget* boardWidget = new BoardWidget();
    boardWidget->setStyleSheet("background-color: lightblue;");

    // Creeaz? un alt widget pentru partea din dreapta
    QFrame* rightWidget = new QFrame();
    rightWidget->setStyleSheet("background-color: lightgray;");

    // Adaug? widget-urile în layout cu propor?ii (1:1 pentru jum?tate/jum?tate)
    layout->addWidget(boardWidget, 1);   // Ocup? jum?tatea din stânga
    layout->addWidget(rightWidget, 1);   // Ocup? jum?tatea din dreapta

    // Seteaz? layout-ul principal
    mainWidget->setLayout(layout);


    //connect(boardWidget, &BoardWidget::cardPlaced, this, &MainWindow::onCardPlaced);
}

void MainWindow::onCardPlaced(int row, int col, Card card) {
    if (game.getBoard().MakeMove(row, col, card)) {
        //game.SwitchTurn();
        //boardWidget->setPlayerHand(game.CurrentTurn()->getHand());
        boardWidget->update();
    }
}