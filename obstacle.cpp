#include "obstacle.h"
#include "definitions.h"

Obstacle::Obstacle(qreal x, qreal y)
{
    myImage = new QPixmap(OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
	QColor color;
	int red, green, blue;
	red = rand() % 200 + 56;
	green = rand() % 200 + 56;
	blue = rand() % 200 + 56;
	color.setRgb(red, green, blue);
    myImage->fill(color);
    setPos(x, y);
}

Obstacle::~Obstacle()
{
	delete myImage;
}

void Obstacle::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                        QWidget*)
{
        painter->drawPixmap(0, 0, *myImage);
}

QRectF Obstacle::boundingRect(void) const
{
        return myImage->rect();
}

bool Obstacle::isObstacle(void)
{
        return true;
}
