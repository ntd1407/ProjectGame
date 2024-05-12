
#include "BulletObject.h"

BulletObject::BulletObject()
{
  x_val_ = 0;
  y_val_ = 0;
  rect_.h = 0;
  rect_.w = 0;
  rect_.y = 0;
  is_move_ = false;
}

BulletObject::~BulletObject()
{
  Free();
}


void BulletObject::HandelMove(const int& x_border, const int& y_border)
{
    rect_.y -= SPEED_BULLET;
    if(rect_.y < 46)
    {
        is_move_ = false;
    }
}

