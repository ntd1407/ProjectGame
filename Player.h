

#ifndef Player_H_
#define Player_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

class Player : public BaseObject
{
public :
    Player();
    ~Player();

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event event,SDL_Renderer* screen);
    void DoPlayer( );
    void CheckToMap();

    std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list_;}
    void set_bullet_list(std::vector<BulletObject*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }
    void HandleBullet(SDL_Renderer* des);
    void RemoveBullet(const int& idx);

private:
    std::vector<BulletObject*>p_bullet_list_;
    float x_val_;
    float y_val_;
    float x_pos_;
    float y_pos_;
    Input input_type_;
};


#endif
