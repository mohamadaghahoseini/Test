#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <c++/iostream>
using namespace std; //estefade konim ?

int main( int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
//    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS)!=0){
//        cerr<<SDL_GetError();
//        return -1;
//    }
    TTF_Init();
//    if(TTF_Init()!=0){
//        cerr<<SDL_GetError();
//        return -1;
//    }

    SDL_Rect Available_Screen;
    SDL_GetDisplayUsableBounds(0,&Available_Screen);
    const int W=Available_Screen.w;
    const int H=Available_Screen.h;
    SDL_Window* window;
    Uint32 WND_flags =  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE ;
    window=SDL_CreateWindow("Scratch",Available_Screen.x,Available_Screen.y,W,H,WND_flags);
//    if(!window){
//        cerr<<SDL_GetError();
//        return -1;
//    }

    SDL_Renderer *renderer;
    renderer= SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    if(!renderer){
//        cerr<<SDL_GetError();
//        return -1;
//    }

    SDL_RaiseWindow(window);
    Uint8 x=255;
    int rmainBackgroundColor ,gmainBackgroundColor;
    int bmainBackgroundColor;
    int amainBackgroundColor;
    int rtitleBarColor;
    int gtitleBarColor;
    int btitleBarColor;
    int atitleBarColor;
    int rmenuBarColor;
    int gmenuBarColor;
    int bmenuBarColor;
    int amenuBarColor;
    SDL_Color mainBackgroundColor={255,255,x,255};
    SDL_Color titleBarColor={0,0,x,255};
    SDL_Color menuBarColor={0,0,255,255};

    SDL_SetRenderDrawColor(renderer,mainBackgroundColor.r,mainBackgroundColor.g,mainBackgroundColor.b,mainBackgroundColor.a);
    SDL_SetRE
    SDL_RenderClear(renderer);
    aalineRGBA(renderer,0,H,W,H,255,255,255,255);
    aalineRGBA(renderer,0,H-1,W,H-1,255,0,0,255);
    SDL_RenderPresent(renderer);


    SDL_Event* e=new SDL_Event();
    SDL_PollEvent(e);
    while(e->key.keysym.sym!=SDLK_ESCAPE)
    {
        SDL_PollEvent(e);
    }


    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
