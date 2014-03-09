#include "gap.h"
#include "definitions.h"

Gap::Gap(qreal x, qreal y) : Obstacle (x, y)
{
  myImage = new QPixmap (WALL_WIDTH, WALL_HEIGHT);
  myImage->fill(Qt::black);
}

Gap::~Gap()
{

}
