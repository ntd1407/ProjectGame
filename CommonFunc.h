
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <iostream>
#include <Windows.h>
#include <math.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

static SDL_Surface* menu_surface = NULL;
static TTF_Font *font = NULL;
static SDL_Surface* menu = NULL;
static SDL_Texture*  menu_tex = NULL;

//screen
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int NUM_THREAT = 5;
const int FRAMES_PER_SECOND = 20;
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 1000;

const int RENDER_DRAW_COLOR = 255;

const int PLAYER_SPEED = 600;
const int SPEED_OBJECT = 3;
const int SPEED_BULLET = 13;

typedef struct Input
{
    int left;
    int right;
    int up;
    int down;
};
namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}


#endif
