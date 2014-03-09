#include "game.h"
#include "definitions.h"
#include <ctime>
#include <cstddef>
#include <QKeyEvent>
#include <QPixmap>
#include <QColor>
#include <QList>

Game::Game(MainWindow* parent) :
	QWidget(parent),
	myView(this),
	myScene(0, 0, VIEW_WIDTH, VIEW_HEIGHT + 2 * EXTRA_SCENE_SPACE),
	myParent(parent)
{
	myView.setScene(&myScene);

	/** Set up the view **/
	myView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	myView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	myView.setCacheMode(QGraphicsView::CacheBackground);
	myView.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	myView.setOptimizationFlags(QGraphicsView::DontClipPainter
								| QGraphicsView::DontSavePainterState
			    				| QGraphicsView::DontAdjustForAntialiasing);
	myView.viewport()->setFocusProxy(this);
	
	QPixmap background(VIEW_WIDTH, VIEW_HEIGHT + 2 * EXTRA_SCENE_SPACE);
	background.fill(Qt::black);
	myScene.setBackgroundBrush(background);
	myView.setSceneRect(0, EXTRA_SCENE_SPACE, VIEW_WIDTH, VIEW_HEIGHT);
	
	/* Set up the initial objects */
	reset();

	/* Set up the timer */
	startTimer(1000.f / 30);
	srand(time(NULL));
}

Game::~Game()
{
	//myScene.clear();
	delete myPlayer;
}

void Game::reset()
{
	/* Set up the adding counters */
	addWallLimit = WALL_HEIGHT / SCROLL_MOVE_DIST;
	addWallCounter = 0;
	addObstLimit = 5 * OBSTACLE_HEIGHT / SCROLL_MOVE_DIST;
	addObstCounter = 0;
	scoreLimit = 10;
	scoreCounter = 0;
	myScene.clear();
	myObjects.clear();
	myScore = 0;

	if (myPlayer == NULL)
	{
		delete myPlayer;
	}
	/** Set up the player and the initial scene **/
	myPlayer = new Player(WALL_WIDTH + 1,
							EXTRA_SCENE_SPACE + VIEW_HEIGHT - 2*PLAYER_HEIGHT,
							true);
	myScene.addItem(myPlayer);
	for (int i = VIEW_HEIGHT + EXTRA_SCENE_SPACE; i >= 0; i -= WALL_HEIGHT)
	{
		Wall* x = new Wall(0, i);
		Wall* y = new Wall(400 - WALL_WIDTH, i);
		myObjects.append(x);
		myScene.addItem(x);
		myObjects.append(y);
		myScene.addItem(y);
		x->setVisible(true);
		y->setVisible(true);
	}
	myScene.addItem(myPlayer);
	myPlayerWantsToJump = false;

	/** Make a bunch of walls **/
	int i = VIEW_HEIGHT + EXTRA_SCENE_SPACE - WALL_HEIGHT - 1;
	for (i = i + 1; i >= 0; i -= WALL_HEIGHT)
	{
		Wall* x = new Wall(0, i);
		Wall* y = new Wall(VIEW_WIDTH - WALL_WIDTH, i);
		myObjects.append(x);
		myScene.addItem(x);
		myObjects.append(y);
		myScene.addItem(y);
		x->setVisible(true);
		y->setVisible(true);
	}
}

void Game::timerEvent(QTimerEvent*)
{
	// check to see if any addition is necessary
	checkAddition();

	// advance the scene
	myScene.advance();

	// check to see if the score should be increased
	checkScore();
	// check to see if he wants to jump (and can)
	checkJump();
	// check to see if he is stuck in a wall
	checkWall();
	// check to see if he has hit an obstacle
	checkLose();
	// check to see if removal of items is necessary
	checkDeath();
}

void Game::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Space)
	{
		myPlayerWantsToJump = true;
	}
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Space)
	{
		myPlayerWantsToJump = false;
	}
}

void Game::checkScore()
{
	if (scoreCounter >= scoreLimit)
	{
		myScore ++;
		scoreCounter = 0;
	}
	else
	{
		scoreCounter ++;
	}
}

void Game::checkJump()
{
	if (myPlayerWantsToJump)
	{
		QList<Stationary*> collisions = getPlayerCollisions();
		for (QList<Stationary*>::iterator i = collisions.begin();
			i != collisions.end(); i++)
		{
			if (!(*i)->isObstacle())
			{
				myPlayer->jump();
				myPlayer->advance(1);
				myPlayerWantsToJump = false;
				return;
			}
		}
	}
}

void Game::checkWall()
{
	QList<Stationary*> collisions = getPlayerCollisions();
	for (QList<Stationary*>::iterator i = collisions.begin();
		i != collisions.end(); i++)
	{
		if (!(*i)->isObstacle())
		{
			if ((*i)->x() == 0)
			{
				myPlayer->setPos(WALL_WIDTH + 1,
								myPlayer->y());
			}
			else
			{
				myPlayer->setPos(VIEW_WIDTH - WALL_WIDTH
								- PLAYER_WIDTH - 1,
								myPlayer->y());
			}
			return;
		}
	}
}

void Game::checkLose()
{
	QList<Stationary*> collisions = getPlayerCollisions();
	for (QList<Stationary*>::iterator i = collisions.begin();
		i != collisions.end(); i++)
	{ 
		if ((*i)->isObstacle())
		{
			myParent->gameOver(myScore);
			return;
		}
	}
}

void Game::checkDeath()
{
	for (QList<Stationary*>::iterator i = myObjects.begin();
		i != myObjects.end(); i++) 
	{
		if ((*i)->expired())
		{
			myScene.removeItem(*i);
			delete (*i);
			i = myObjects.erase(i);
		}
	}
}

void Game::checkAddition()
{
	if (addWallCounter >= addWallLimit)
	{
		addWallCounter = 0;
		int r = rand() % 100;
		if (r < TWO_WALL_PROB)
		{
			// add two walls
			Wall* a = new Wall(0, 0);
			Wall* b = new Wall(VIEW_WIDTH - WALL_WIDTH, 0);
			myObjects.append(a);
			myObjects.append(b);
			myScene.addItem(a);
			myScene.addItem(b);
			a->setVisible(true);
			b->setVisible(true);
		}
		else if (TWO_WALL_PROB <= r
							   && r < TWO_WALL_PROB + LEFT_WALL_ONLY_PROB)
		{
			// add a wall on the left and a gap on the right
			Wall* a = new Wall(0, 0);
			Gap* b = new Gap(VIEW_WIDTH - WALL_WIDTH, 0);
			myObjects.append(a);
			myObjects.append(b);
			myScene.addItem(a);
			myScene.addItem(b);
			a->setVisible(true);
			b->setVisible(true);
		}
		else
		{
			// add a gap on the left and a wall on the right
			Gap* a = new Gap(0, 0);
			Wall* b = new Wall(VIEW_WIDTH - WALL_WIDTH, 0);
			myObjects.append(a);
			myObjects.append(b);
			myScene.addItem(a);
			myScene.addItem(b);
			a->setVisible(true);
			b->setVisible(true);
		}
	}
	else
	{
		addWallCounter ++;
	}

	if (addObstCounter >= addObstLimit)
	{
		addObstCounter = 0;
		int r = rand() % 100;
		if (r < OBSTACLE_PROB)
		{
			// add an obstacle
			int coordinate = rand() % (VIEW_WIDTH - OBSTACLE_WIDTH
										- 2*WALL_WIDTH - 2*PLAYER_WIDTH
										- 6) + WALL_WIDTH + PLAYER_WIDTH + 3;
			Obstacle* a = new Obstacle(coordinate, 0);
			myObjects.append(a);
			myScene.addItem(a);
			a->setVisible(true);
		}
	}
	else
	{
		addObstCounter ++;
	}
}

QList<Stationary*> Game::getPlayerCollisions()
{
	QList<Stationary*> ans;
	for (QList<Stationary*>::iterator i = myObjects.begin();
		i != myObjects.end(); i++)
	{
		if (myPlayer->collidesWithItem(*i))
		{
			ans.append(*i);
		}
	}
	return ans;
}
