#ifndef GAP_H
#define GAP_H
#include "obstacle.h"

class Gap : public Obstacle {
 public:
  Gap(qreal x, qreal y);
  ~Gap();
};

#endif
