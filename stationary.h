#ifndef STATIONARY_H
#define STATIONARY_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui/QPainter>
class Stationary: public QGraphicsItem {
        public:
                void advance(int);
                virtual bool isObstacle() = 0;
                virtual void paint(QPainter*, 
                                const QStyleOptionGraphicsItem*,
                                QWidget*) = 0;
                virtual bool expired();
};

#endif
