
#include "Player.h"

Player :: Player()
{
    x_pos_ = (SCREEN_WIDTH - 46)/2;
    y_pos_ = (SCREEN_HEIGHT - 48);
    x_val_ = 0;
    y_val_ = 0;
    input_type_.left= 0;
    input_type_.right = 0;
    input_type_.down = 0;
    input_type_.up = 0;

}

Player :: ~Player()
{
    Free();
}

bool Player :: LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);
    return ret;
}

void Player::Show(SDL_Renderer* des)
{
    LoadImg("Images\\player.bmp",des);
    rect_.x = x_pos_;
    rect_.y = y_pos_;

    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(des, p_object_, NULL, &renderquad);

}
void Player::HandleInputAction(SDL_Event event, SDL_Renderer* screen)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.scancode == SDL_SCANCODE_UP)
        {
            input_type_.up = 1;
        }
         else if (event.key.keysym.scancode == SDL_SCANCODE_A || event.key.keysym.scancode == SDL_SCANCODE_LEFT)
        {
            input_type_.left = 1;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_S || event.key.keysym.scancode == SDL_SCANCODE_DOWN)
        {
            input_type_.down = 1;
        }
         else if (event.key.keysym.scancode == SDL_SCANCODE_D || event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            input_type_.right = 1;
        }
         if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && event.key.repeat  == 0)
        {
            BulletObject* p_bullet = new BulletObject();
            p_bullet->LoadImg("Images//bullet.bmp", screen);
            p_bullet->SetRect(this->rect_.x + 46 / 2 - 2, this->rect_.y - 48 / 2);
            p_bullet->set_is_move(true);
            p_bullet_list_.push_back(p_bullet);
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.scancode == SDL_SCANCODE_UP)
        {
            input_type_.up = 0;
        }
         if (event.key.keysym.scancode == SDL_SCANCODE_A || event.key.keysym.scancode == SDL_SCANCODE_LEFT)
        {
            input_type_.left = 0;
        }
         if (event.key.keysym.scancode == SDL_SCANCODE_S || event.key.keysym.scancode == SDL_SCANCODE_DOWN)
        {
            input_type_.down = 0;
        }
         if (event.key.keysym.scancode == SDL_SCANCODE_D || event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            input_type_.right = 0;
        }
    }
}


void Player::DoPlayer()
{
    if (input_type_.left == 1)
    {
      x_val_ -= PLAYER_SPEED;
    }
     if (input_type_.right == 1)
    {
      x_val_+= PLAYER_SPEED;
    }
     if (input_type_.up == 1)
    {
      y_val_-= PLAYER_SPEED;
    }
     if (input_type_.down == 1)
    {
      y_val_ +=PLAYER_SPEED;
    }
    CheckToMap();
    x_val_ = 0;     // reset để sau mỗi lần bắt sự kiện tốc độ không càng ngày càng cao
    y_val_ = 0;

}

void Player::CheckToMap()
{
   x_pos_ += x_val_/60;
   y_pos_ += y_val_/60;  // sao day phai chia 60?
   if( x_pos_ < 0 || x_pos_  + 46> SCREEN_WIDTH ){
    x_pos_ -= x_val_/60;
   }
   if( y_pos_ < 0 || y_pos_  + 48> SCREEN_HEIGHT ){
    y_pos_ -= y_val_/60;
   }
}
void Player::HandleBullet(SDL_Renderer* des)
{
  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    BulletObject* p_bullet = p_bullet_list_.at(i);
    if (p_bullet != NULL)
    {
      if (p_bullet->get_is_move())
      {
        p_bullet->HandelMove(SCREEN_WIDTH, SCREEN_HEIGHT);

        p_bullet->Render(des);
      }
      else
      {
        p_bullet_list_.erase(p_bullet_list_.begin() + i);
        if (p_bullet != NULL)
        {
          delete p_bullet;
          p_bullet = NULL;
        }
      }
    }
  }
}
void Player::RemoveBullet(const int& idx)
{
  if (p_bullet_list_.size() > 0 && idx < p_bullet_list_.size())
  {
    BulletObject* p_bullet = p_bullet_list_.at(idx);
    p_bullet_list_.erase(p_bullet_list_.begin() + idx);

    if (p_bullet)
    {
      delete p_bullet;
      p_bullet = NULL;
    }
  }
}
