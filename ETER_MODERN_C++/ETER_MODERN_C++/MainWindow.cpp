#include "MainWindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), game() {
	QWidget* mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);

	QHBoxLayout* layout = new QHBoxLayout(mainWidget);

	game = new Game();
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

	rightLayout->addWidget(cards_p1, 1); 
	rightLayout->addWidget(cards_p2, 1); 

	rightWidget->setLayout(rightLayout);

	layout->addWidget(boardWidget, 1);
	layout->addWidget(rightWidget, 2);

	mainWidget->setLayout(layout);

	connect(boardWidget, &BoardWidget::requestGlobalUpdate, this, &MainWindow::handleGlobalUpdate);

}

void MainWindow::showWinnerMessage(const QString& winnerName)
{
	QMessageBox messageBox;
	messageBox.setWindowTitle("Game Over");
	messageBox.setText(winnerName + " has won the game!");
	messageBox.setIcon(QMessageBox::Information);

	messageBox.addButton("Reset Game", QMessageBox::AcceptRole);
	messageBox.addButton("Exit Game", QMessageBox::RejectRole);

	int result = messageBox.exec();

	if (result == QMessageBox::AcceptRole) {
		resetGame(); 
	}
	else if (result == QMessageBox::RejectRole) {
		close(); 
	}
}

void MainWindow::resetGame() {
	
}

void MainWindow::handleGlobalUpdate() {
	this->update();
}


void MainWindow::onCardPlaced(int row, int col, Card card) {
	
}