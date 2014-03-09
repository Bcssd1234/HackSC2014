#include "wall.h"
#include "definitions.h"

Wall::Wall(qreal x, qreal y)
{
  myImage = new QPixmap (WALL_WIDTH, WALL_HEIGHT);
  myImage->fill(Qt::white);  //change color?
  setPos(x, y);
}

Wall::~Wall()
{
	delete myImage;
}

void Wall::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
  painter->drawPixmap(0, 0, *myImage);
}

QRectF Wall::boundingRect() const
{
  return myImage->rect();
}

bool Wall::isObstacle()
{
	return false;
}
