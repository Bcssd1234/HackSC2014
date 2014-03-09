#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>

#include "main_window.h"
#include "player.h"
#include "stationary.h"
#include "obstacle.h"
#include "gap.h"
#include "wall.h"

// forward declaration of MainWindow
class MainWindow;

class Game : public QWidget
{
	public:
		Game(MainWindow* parent = 0);
		void reset();
		~Game();

	private slots:
		// Runs each frame
		void timerEvent(QTimerEvent*);
	protected:
		// Sets the "myPlayerWantsToJump" flag to true
		void keyPressEvent(QKeyEvent* event);
		// Sets the "myPlayerWantsToJump" flag to false
		void keyReleaseEvent(QKeyEvent* event);

	private:
		// These are for deciding to add stuff
		int addWallCounter;
		int addWallLimit;
		int addObstCounter;
		int addObstLimit;
		int scoreCounter;
		int scoreLimit;

		// score
		int myScore;
		// The view
		QGraphicsView myView;
		// The scene
		QGraphicsScene myScene;
		// The list of obstacles and walls
		QList<Stationary*> myObjects;
		// The player
		Player* myPlayer;
		// The parent
		MainWindow* myParent;

		bool myPlayerWantsToJump;

		// check for score
		void checkScore();
		// check to see if the player should jump
		void checkJump();
		// check to move the player out of a wall
		void checkWall();
		// check to see if the player is in an Obstacle
		void checkLose();
		// check to see if some items died
		void checkDeath();
		// check to see if we should add some stuff
		void checkAddition();

		QList<Stationary*> getPlayerCollisions();
};

#endif
