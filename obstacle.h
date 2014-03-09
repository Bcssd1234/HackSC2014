#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui/QPainter>
#include <QPixmap>
#include <QColor>
#include "stationary.h"
class Obstacle: public Stationary {
        public:
                Obstacle(qreal x, qreal y);
                ~Obstacle();
                void paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                                QWidget*);
                QRectF boundingRect(void) const;
                bool isObstacle(void);
        protected:
                QPixmap* myImage;        
};
#endif
