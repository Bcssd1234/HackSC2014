#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

// NULL
#include <cstddef>

// forward declaration of game
class Game;

// The actual game
#include "game.h"

// Qt stuff
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>

class MainWindow : public QWidget
{
	Q_OBJECT

	public:
        MainWindow(QWidget* parent = NULL);
		~MainWindow();
		void gameOver(int score);

	protected:
		void closeEvent(QCloseEvent* event);

	public slots:
		void play();

	private:
		// void writeScoreToFile();

		QVBoxLayout* myLayout;
		QPushButton* myPlayButton;
		Game* myGame;
};

#endif
