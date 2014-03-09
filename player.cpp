#include <QPainter>
#include "player.h"
#include "definitions.h"

Player::Player(qreal x, qreal y, bool left): QGraphicsItem(0)
{
	myImage = new QPixmap(PLAYER_WIDTH, PLAYER_HEIGHT);
	myImage->fill(Qt::green); // might change later
	movingLeft = left;
	setPos(x, y);
}

void Player::jump()
{
	movingLeft = !movingLeft;
}

void Player::advance(int phase)
{
	if (phase == 1)
	{
		if (movingLeft)
		{
			moveBy(-PLAYER_MOVE_DIST, 0);
		}
		else
		{
			moveBy(PLAYER_MOVE_DIST, 0);
		}
	}
	return;
}

QRectF Player::boundingRect() const
{
	return myImage->rect();
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	painter->drawPixmap(0, 0, *myImage);
}
