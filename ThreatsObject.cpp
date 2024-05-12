
#include "ThreatsObject.h"


ThreatsObject::ThreatsObject()
{
    rect_.x = x_pos_;
    rect_.y = rand() % (SCREEN_HEIGHT / 5);
    rect_.w = WIDHT_THREAT;
    rect_.h = HEIGHT_THREAT ;
    x_val_ = 0;
    y_val_ = 0;
    y_pos_ = 0;
    is_endmap = false;

}

ThreatsObject::~ThreatsObject()
{
  Free();
}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImg(path, screen);

  return ret;
}


void ThreatsObject::DoPlayer( )
{

           rect_.y += SPEED_OBJECT;
        if( rect_.y > SCREEN_HEIGHT  )
        {
           SetLife(Getlife()- 1);
            set_check(true);
            rect_.y = 0;
          int rand_x=rand()%(SCREEN_WIDTH-50);
 			int rand_y=rand()%60;
 			rect_.y = rand_y;
 			rect_.x = rand_x;
        }
    else if (rect_.x == 0) // Nếu là ThreatsObject đầu tiên và vẫn ở vị trí ban đầu
    {
        // Đặt lại vị trí ngẫu nhiên cho rect_.x
        int rand_x = rand() % (SCREEN_WIDTH - rect_.w);
        rect_.x = rand_x;
    }
}

bool ThreatsObject::CheckToMap( )
{
  return get_check();
}

void ThreatsObject::Show(SDL_Renderer* des)
{
      SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};

      SDL_RenderCopy(des, p_object_, NULL, &renderQuad );
}
void ThreatsObject::Reset()
{
    rect_.y = 0;
          int rand_x=rand()%(SCREEN_WIDTH-50);
 			int rand_y=rand()%60;
 			rect_.y = rand_y;
 			rect_.x = rand_x;
}
