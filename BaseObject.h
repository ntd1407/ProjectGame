
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y;}
    void SetRect_w_h(const int& x, const int& y) { rect_.w = x, rect_.h = y;}
    SDL_Rect GetRect() const {return rect_;}
    SDL_Texture* GetObject() const {return p_object_;}
    void Free();

    void SetLife(const int& x) {lives = x;}
    int Getlife() const {return lives;}

    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

protected:
    int lives ;
    SDL_Texture* p_object_;
    SDL_Rect rect_;
};

#endif
