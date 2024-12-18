#include "MainWindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), game() {
	QWidget* mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);

	QHBoxLayout* layout = new QHBoxLayout(mainWidget);

	Game* game = new Game();
	game->InitGame("Player1", "Player2");

	BoardWidget* boardWidget = new BoardWidget();
	boardWidget->setGame(game);


	connect(boardWidget, &BoardWidget::playerWon, this, &MainWindow::showWinnerMessage);




	QFrame* rightWidget = new QFrame();
	QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);

	CardsWidget* cards_p1 = new CardsWidget();
	cards_p1->setCards(game->getPlayer1());

	CardsWidget* cards_p2 = new CardsWidget();
	cards_p2->setCards(game->getPlayer2());

	rightLayout->addWidget(cards_p1, 1); // Jumătatea de sus
	rightLayout->addWidget(cards_p2, 1); // Jumătatea de jos

	rightWidget->setLayout(rightLayout);

	layout->addWidget(boardWidget, 1);   // Ocupă jumătatea din stânga
	layout->addWidget(rightWidget, 2);   // Ocupă jumătatea din dreapta

	mainWidget->setLayout(layout);

	connect(boardWidget, &BoardWidget::requestGlobalUpdate, this, &MainWindow::handleGlobalUpdate);

	//connect(boardWidget, &BoardWidget::cardPlaced, this, &MainWindow::onCardPlaced);
}

void MainWindow::showWinnerMessage(const QString& winnerName)
{
	QMessageBox::information(this, "Game Over", winnerName + " has won the game!");
}

void MainWindow::handleGlobalUpdate() {
	this->update();
}


void MainWindow::onCardPlaced(int row, int col, Card card) {
	// if (game.getBoard().MakeMove(row, col, card)) {
	  //boardWidget->setPlayerHand(game.CurrentTurn()->getHand());
	  //game.SwitchTurn();
	  //boardWidget->update();
  //}
}