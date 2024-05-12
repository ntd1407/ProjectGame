
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define WIDHT_THREAT 291;
#define HEIGHT_THREAT 264;

class ThreatsObject : public BaseObject
{
public:
  ThreatsObject();
  ~ThreatsObject();

  void set_x_val( int xp) {x_val_ = xp;}
  void set_y_val( int yp) {y_val_ = yp;}
  void set_xpos(const int& xps) {x_pos_ = xps;}
  void set_ypos(const int& yps) {y_pos_ = yps;}
  int get_x_pos() {return x_pos_;}
  int get_y_pos() {return y_pos_;}

    bool CheckToMap();
    void DoPlayer();
    void set_check(const bool& is_end) {is_endmap = is_end;}
    bool get_check() {return is_endmap;}

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);

    std::vector<ThreatsObject*> get_object_list() const {return p_object_list_;}
    void set_object_list(std::vector<ThreatsObject*> object_list)
    {
        p_object_list_ = object_list;
    }
    void Reset();
private:

    std::vector<ThreatsObject*>p_object_list_;
  float x_val_;
  float y_val_;
  float x_pos_;
  float y_pos_;
  bool is_endmap;

};

#endif //
