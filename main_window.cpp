#include "main_window.h"
#include "definitions.h"

#include <QCloseEvent>
MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    resize(VIEW_WIDTH + 50, VIEW_HEIGHT + 200);
    // make button
	myPlayButton = new QPushButton(QString("Reset"), this);
	// make the actual graphics scene
	myGame = new Game(this);

	/** Connections **/
	// play button
	connect(myPlayButton, SIGNAL(clicked()), this, SLOT(play()));

	// make the layout
	myLayout = new QVBoxLayout;
	myLayout->addWidget(myGame);
	myLayout->addWidget(myPlayButton);

	setLayout(myLayout);
	show();
}

MainWindow::~MainWindow()
{
	delete myPlayButton;
	delete myGame;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	// writeScoreToFile();
	event->accept();
}

void MainWindow::gameOver(int score)
{
	QString message("Score: ");
	QString s;
	s.setNum(score);
	message += s;
	message += "\nTry Again?";
	switch( QMessageBox::question(this, "Game Over", message,
				QMessageBox::Yes | QMessageBox::No) )
	{
		case QMessageBox::Yes :
			play();
			break;
		case QMessageBox::No :
			close();
			break;
		default:
			close();
			break;
	}
}

void MainWindow::play()
{
	myGame->reset();
}
