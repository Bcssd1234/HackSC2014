#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPixmap>

class Player: public QGraphicsItem {
	public:
		Player(qreal x, qreal y, bool left);
		void jump(void);
		void advance(int phase);
		void paint(QPainter* painter, 
                        const QStyleOptionGraphicsItem*,
                                QWidget*);
		QRectF boundingRect(void) const;
	private:
		bool movingLeft;
		QPixmap* myImage;
};

#endif
