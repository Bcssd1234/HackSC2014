#ifndef WALL_H
#define WALL_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include "stationary.h"
class Wall : public Stationary
{
 public:
  Wall(qreal x, qreal y);
  ~Wall();
  void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
  QRectF boundingRect(void) const;
  bool isObstacle();
 private:
  QPixmap* myImage;
};
#endif
