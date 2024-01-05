#ifndef __GUI_H__
#define __GUI_H__
#include "../SDL2/include/SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} WindowManager;

int initiateWM(WindowManager **wm, const char *title, int width, int height);
void destroy();
void resize(WindowManager **wm, int width, int height);
void keepAlive(WindowManager **wm);
#endif