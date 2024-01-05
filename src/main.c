/**
 * Windows Manager coded in SDL using C.
 * Methods:
 * - initiateWM();
 * - destroy();
 * - resize();
*/
#include "../include/gui.h"


int initiateWM(WindowManager **wm, const char *title, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("(-) SDL Initialization failed. Error: %s\n", SDL_GetError());
        return -1;
    }

    //DOC:- https://wiki.libsdl.org/SDL2/SDL_CreateWindow
    (*wm)->window = SDL_CreateWindow(title, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                height, 
                                width, 
                                SDL_WINDOW_SHOWN
                    );

    if(!(*wm)->window){
        printf("(-) SDL Window Creation Failed. Error: %s\n", SDL_GetError());
        destroy(&wm);
        return -1;
    }

    //DOC:- https://wiki.libsdl.org/SDL2/SDL_CreateRenderer
    (*wm)->renderer = SDL_CreateRenderer((*wm)->window, 
                                    -1, 
                                    SDL_RENDERER_ACCELERATED
                    
                    );

    if(!(*wm)->renderer){
        printf("(-) SDL Renderer Creation Failed. Error: %s\n", SDL_GetError());
        destroy(&wm);
        return -1;
    }

    //DOC:- https://wiki.libsdl.org/SDL2/SDL_LoadBMP
    SDL_Surface *icon = SDL_LoadBMP("C://Coding stuff//WindowManager//src//gigachad2.bmp");
    
    if(!icon){
        printf("(-) Failed to load icon: %s\n", SDL_GetError());
        destroy(&wm);
        return -1;
    }

    //DOC:- https://wiki.libsdl.org/SDL2/SDL_LoadBMP
    SDL_SetWindowIcon((*wm)->window, icon);
    return 0;
}

void resize(WindowManager **wm, int width, int height){
    SDL_SetWindowSize((*wm)->window, width, height);
}

void destroy(WindowManager **wm){
    SDL_DestroyRenderer((*wm)->renderer);
    SDL_DestroyWindow((*wm)->window);
    SDL_Quit();
    puts("(-) Destroyed The SDL Instances. :)");
}

void keepAlive(WindowManager **wm){
    int isRunning = 1;
    while(isRunning){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                isRunning = 0; // Closed.
                puts("(-) Application Closed.");
            }

            if(e.window.event == SDL_WINDOWEVENT_RESIZED){
                printf("(-) Window Resized to: %dx%d\n", e.window.data1, e.window.data2);
            }
        }
        SDL_RenderPresent((*wm)->renderer);
    }
}

int main(int argc, char *argv[]){
    WindowManager *wm = malloc(sizeof(wm));
    int isRunning = 1;
    initiateWM(&wm, "Hello World!", 400, 400);
    keepAlive(&wm);
    return 0;
}