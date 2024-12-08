#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), game() {
    // Creează un widget principal pentru layout
    QWidget* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    // Creează un layout orizontal
    QHBoxLayout* layout = new QHBoxLayout(mainWidget);

    // Creează un widget pentru "board" (partea din stânga)
    BoardWidget* boardWidget = new BoardWidget();
    Board* board = new Board();
    board->SetSize(3);
    // Delete below
    board->AddCard(0, 0, Card(1));
    board->AddCard(0, 1, Card(2, "blue"));
    board->AddCard(1, 0, Card(3));
    board->AddCard(1, 1, Card(1, "blue"));
    // Delete above
    boardWidget->setBoard(board);

    // Creează un alt widget pentru partea din dreapta
    // TODO: Aici trebuie sa creezi din nou o divisiune
    // Vei face split la partea din dreapta pe verticala
    // Acolo vei pune 2 widgeturi pentru player unde vei afisa cartile curente
    // PlayersHandWidget care are metoda de a selecta o carte, vei desena o bordura in jurul cartii selectate
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