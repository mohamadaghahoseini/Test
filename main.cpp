#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <c++/iostream>


//   Tab names
constexpr int CLOSE_BUTTON=1;
constexpr int WINDOW_BUTTON=2;
constexpr int MINIMIZED_BUTTON=3;

// Button names
constexpr int TAB_GENERAL=1;

// structs
struct AppState{
    bool endProgram=false;
    bool fullScreen=false;
    int W,H,X,Y;
    int LastW,LastH;

    int FULL_SCREEN_W,FULL_SCREEN_H;
    SDL_Rect AVAILABLE_SCREEN;

    SDL_Renderer *renderer;
    SDL_Window *window;
};
struct MouseState{
    int x=0,y=0;

    bool rightDown=false;          // right click down in x0,y0
    bool rightPressed=false;       // right click hold from click down in x0,y0 until click up (can be in x0,y0 or not)
    bool rightUp=false;            // right click up

    bool leftDown=false;
    bool leftPressed=false;
    bool leftUp=false;
};
struct ButtonRect{
    int ID;
    SDL_Rect rect;

    bool onButton=false;
    bool rightClick=false;
    bool leftClick=false;
    bool rightPressed=false;
    bool leftPressed=false;

    bool active=true;

};
struct AllTabButtons{
    int ID;
    bool active;
    std::vector<ButtonRect> buttons;
};
struct KeyboardButton{
    bool keyUp[SDL_NUM_SCANCODES]={};       // this frame keyup ?
    bool pressed[SDL_NUM_SCANCODES]={};     // press right now ?
    bool keyDown[SDL_NUM_SCANCODES]={};     // this frame keydown ?
};
struct ThemeGeneralTab{
    SDL_Color mainBackground;

    SDL_Color closeButton;
    SDL_Color closeButtonMouse;
    SDL_Color windowButton;
    SDL_Color windowButtonMouse;
    SDL_Color minimizeButton;
    SDL_Color minimizeButtonMouse;
};

// bool function
bool isMouseInRect(MouseState &mouse,SDL_Rect &rect);

// reset function
// در ابتدای هر فریم bool های لازم را ریست میدهد به دیفالت
void resetKeyboardButtons(KeyboardButton &key);
void resetButtonRect(std:: vector<AllTabButtons> &tab);
void resetMouseState(MouseState &mouse);

// update function
// با گرفتن هر ایونت اپدیت میکند
void updateKeyboardButtons(KeyboardButton &key,SDL_Event &e);
void updateMouseState(MouseState &mouse, SDL_Event &e);
void updateButtonRectAndMouseState(MouseState &mouse,std:: vector<AllTabButtons> &tab,SDL_Event &e);

// Action function
// عملیات مربوط را در هر فریم انجام میدهد با توجه به توابع مربوط به دکمه ها
void keyboardButtonActions(KeyboardButton &key, AppState &app);
void AllTabButtonActions(std::vector<AllTabButtons> &tab,AppState &app,ThemeGeneralTab &colorGeneral);
void RenderGeneralTap(std::vector<ButtonRect> buttons, AppState &app, ThemeGeneralTab &color);      // need to fix











int main( int argc, char* argv[])
{
    AppState app;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
    TTF_Init();

    SDL_DisplayMode full_Screen;
    SDL_GetCurrentDisplayMode(0,&full_Screen);
    app.FULL_SCREEN_W=full_Screen.w;
    app.FULL_SCREEN_H=full_Screen.h;
    SDL_GetDisplayUsableBounds(0,&app.AVAILABLE_SCREEN);
    app.W=app.LastW=app.AVAILABLE_SCREEN.w;
    app.H=app.LastH=app.AVAILABLE_SCREEN.h;
    app.X=app.AVAILABLE_SCREEN.x;
    app.Y=app.AVAILABLE_SCREEN.y;

    SDL_Window* window;
    Uint32 WND_flags =  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE ;
    window=SDL_CreateWindow("Scratch",app.X,app.Y,app.W,app.H,WND_flags);
    SDL_SetWindowBordered(window,SDL_FALSE);
    SDL_RaiseWindow(window);
    app.window=window;


    SDL_Renderer *renderer;
    renderer= SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);   //SDL_RENDERER_ACCELERATED or SDL_RENDERER_SOFTWARE
    app.renderer=renderer;
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


    // Variable declaration

    std:: vector<AllTabButtons> tabButtons= {
            {TAB_GENERAL,true ,  {     {CLOSE_BUTTON, SDL_Rect{app.W-app.W/30,0,app.W/30,app.H/25}},
                                       {WINDOW_BUTTON, SDL_Rect{app.W-app.W*2/30,0,app.W/30,app.H/25}},
                                       {MINIMIZED_BUTTON, SDL_Rect{app.W-app.W*3/30,0,app.W/30,app.H/25}}
            }
            }
    };

    KeyboardButton keyboardButton;
    MouseState mouse;
    SDL_GetMouseState(&mouse.x,&mouse.y);

    ThemeGeneralTab ColorGeneral={

    };

    SDL_Event e;
    SDL_PollEvent(&e);
    while(!app.endProgram)
    {
        resetKeyboardButtons(keyboardButton);
        resetButtonRect(tabButtons);
        resetMouseState(mouse);
        while(SDL_PollEvent(&e))
        {
            updateKeyboardButtons(keyboardButton,e);
            updateButtonRectAndMouseState(mouse,tabButtons,e);
        }
        keyboardButtonActions(keyboardButton,app);
        AllTabButtonActions(tabButtons,app,ColorGeneral);
        SDL_RenderPresent(renderer);
        SDL_Delay(5);

    }










    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

bool isMouseInRect(MouseState &mouse,SDL_Rect &rect)
{
    return mouse.x>rect.x && mouse.x<rect.x+rect.w && mouse.y>rect.y && mouse.y<rect.y+rect.h;
}

void resetKeyboardButtons(KeyboardButton &key)
{
    memset(key.keyDown,false,sizeof(key.keyDown));  // can use sizeof(key.keyDown)=512
    memset(key.keyUp,false,sizeof(key.keyUp));     // sizeof(bool)=1
}
void resetButtonRect(std:: vector<AllTabButtons> &tab)
{
    for(auto &it1:tab)
        for(auto &it2:it1.buttons)
        {
            it2.leftClick=false;
            it2.rightClick=false;
        }

}
void resetMouseState(MouseState &mouse)
{
    mouse.rightUp=false;
    mouse.rightDown=false;
    mouse.leftUp=false;
    mouse.leftDown=false;
}

void updateKeyboardButtons(KeyboardButton &key,SDL_Event &e)
{
    if(e.type==SDL_KEYDOWN && e.key.repeat==0)
    {
        key.keyDown[e.key.keysym.scancode]=true;    //e.key.keysym.scancode or e.key.keysym.sym ?
        key.pressed[e.key.keysym.scancode]=true;
    }
    else if(e.type==SDL_KEYUP)
    {
        key.keyUp[e.key.keysym.scancode]=true;
        key.pressed[e.key.keysym.scancode]=false;
    }

}
void updateButtonRectAndMouseState(MouseState &mouse,std:: vector<AllTabButtons> &tab,SDL_Event &e)
{
    // چت جی بی تی میگفت اگر همرو if بزاری امن تر هست !
    // و میگه که مختصات موس رو در هر سه اپدیت کن که به مشکل نخوری
    if(e.type==SDL_MOUSEMOTION)
    {
        mouse.x=e.motion.x;
        mouse.y=e.motion.y;
        for(auto &it1:tab)
            if(it1.active)
                for(auto &it2:it1.buttons)
                {
                    if(isMouseInRect(mouse,it2.rect))
                        it2.onButton= true;
                    else
                        it2.onButton=false;
                }
    }
    else if(e.type==SDL_MOUSEBUTTONDOWN)
    {
        //  SDL_GetMouseState(&mouse.x,&mouse.y);
        // Update mouse state
        if(e.button.button==SDL_BUTTON_LEFT)
        {
            mouse.leftPressed= true;
            mouse.leftDown=true;
        }
        else if(e.button.button==SDL_BUTTON_RIGHT)
        {
            mouse.rightPressed=true;
            mouse.rightDown= true;
        }

        // Update Buttons
        for(auto &it1:tab)
            if(it1.active)
                for(auto &it2:it1.buttons)
                    if(isMouseInRect(mouse,it2.rect))
                    {
                        if(e.button.button==SDL_BUTTON_LEFT)
                            it2.leftPressed=true;
                        else if(e.button.button==SDL_BUTTON_RIGHT)
                            it2.rightPressed=true;
                    }
    }
    else if(e.type==SDL_MOUSEBUTTONUP)
    {
        //    SDL_GetMouseState(&mouse.x,&mouse.y);
        // Update mouse state
        if(e.button.button==SDL_BUTTON_LEFT)
        {
            mouse.leftPressed=false;
            mouse.leftUp=true;
        }
        else if(e.button.button==SDL_BUTTON_RIGHT)
        {
            mouse.rightPressed= false;
            mouse.rightUp= true;
        }

        // Update Buttons
        for(auto &it1:tab)
        {
            for(auto &it2:it1.buttons)
            {
                if(it1.active)
                {
                    if(isMouseInRect(mouse,it2.rect))
                    {
                        if(e.button.button==SDL_BUTTON_LEFT && it2.leftPressed)
                            it2.leftClick=true;
                        else if(e.button.button==SDL_BUTTON_RIGHT && it2.rightPressed)
                            it2.rightClick=true;
                    }
                }

                it2.leftPressed=false;
                it2.rightPressed=false;
            }
        }
    }

}

void keyboardButtonActions(KeyboardButton &key, AppState &app)
{
    if(key.keyDown[SDL_SCANCODE_ESCAPE])
    {
        app.endProgram=true;
    }
    if((key.pressed[SDL_SCANCODE_LALT] || key.pressed[SDL_SCANCODE_RALT]) && key.pressed[SDL_SCANCODE_F4])
    {
        app.endProgram=true;
    }
    if(key.keyDown[SDL_SCANCODE_F11])
    {
        if(app.fullScreen)
        {
            app.fullScreen=false;
            app.W=app.LastW;
            app.H=app.LastH;
            SDL_SetWindowFullscreen(app.window,0);
            // need to countinu ...
        }
        else
        {
            app.fullScreen=true;
            app.W=app.FULL_SCREEN_W;
            app.H=app.FULL_SCREEN_H;
            SDL_SetWindowFullscreen(app.window,SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
    }   // have to finish ...
}
void AllTabButtonActions(std::vector<AllTabButtons> &tab,AppState &app,ThemeGeneralTab &colorGeneral)
{
    for(auto &it:tab)
        if(it.active)
            switch (it.ID) {
                case TAB_GENERAL:
                    RenderGeneralTap(it.buttons,app,colorGeneral);
                    break;

            }
}
void RenderGeneralTap(std::vector<ButtonRect> buttons, AppState &app, ThemeGeneralTab &color)
{
    SDL_SetRenderDrawColor(app.renderer,60,63,63,255);
    SDL_RenderClear(app.renderer);
    int L=6;

    for(auto &it:buttons)
    {

        if(it.ID==CLOSE_BUTTON)
        {
            if(it.onButton)
            {
                SDL_SetRenderDrawColor(app.renderer,232,17,35,255);
                SDL_RenderFillRect(app.renderer,&it.rect);
            }
            if(it.leftClick)
                app.endProgram=true;
            aalineRGBA(app.renderer,it.rect.x+it.rect.w/2-L/ sqrt(2),it.rect.y+it.rect.h/2-L/sqrt(2),it.rect.x+it.rect.w/2+L/sqrt(2),it.rect.y+it.rect.h/2+L/sqrt(2),214,214,214,255);
            aalineRGBA(app.renderer,(it.rect.x+it.rect.w/2-L/ sqrt(2)),(it.rect.y+it.rect.h/2+L/sqrt(2)),(it.rect.x+it.rect.w/2+L/sqrt(2)),(it.rect.y+it.rect.h/2-L/sqrt(2)),214,214,214,255);
            aalineRGBA(app.renderer,it.rect.x+it.rect.w/2-L/ sqrt(2),it.rect.y+it.rect.h/2-L/sqrt(2)-1,it.rect.x+it.rect.w/2+L/sqrt(2),it.rect.y+it.rect.h/2+L/sqrt(2)-1,214,214,214,255);
            aalineRGBA(app.renderer,(it.rect.x+it.rect.w/2-L/ sqrt(2)),(it.rect.y+it.rect.h/2+L/sqrt(2))-1,(it.rect.x+it.rect.w/2+L/sqrt(2)),(it.rect.y+it.rect.h/2-L/sqrt(2))-1,214,214,214,255);
        }
        else if(it.ID==WINDOW_BUTTON)
        {
            if(it.onButton)
            {
                SDL_SetRenderDrawColor(app.renderer,79,82,84,255);
                SDL_RenderFillRect(app.renderer,&it.rect);
            }
            SDL_SetRenderDrawColor(app.renderer,214,214,214,255);
            SDL_Rect rectwindow={it.rect.x+it.rect.w/2-it.rect.w/10,it.rect.y+it.rect.h/2-it.rect.h/7,it.rect.w*2/10,it.rect.w*2/10};
            SDL_RenderDrawRect(app.renderer,&rectwindow);

        }
        else if(it.ID==MINIMIZED_BUTTON)
        {
            if(it.onButton)
            {
                SDL_SetRenderDrawColor(app.renderer,79,82,84,255);
                SDL_RenderFillRect(app.renderer,&it.rect);
            }
            int s=6;
            aalineRGBA(app.renderer,it.rect.x+it.rect.w/2-s,it.rect.y+it.rect.h/2,it.rect.x+it.rect.w/2+s,it.rect.y+it.rect.h/2,214,214,214,255);
            if(it.leftClick )
            {
                SDL_MinimizeWindow(app.window);
                it.onButton=false;
            }

        }

    }
}



//    {
//        SDL_Rect closeButton={W-W/30-0,0,W/30,H/25};
//        bool endProgram=false;
//        bool onCloseButton=false;
//        SDL_Event* e=new SDL_Event();
//
//        SDL_PollEvent(e);
//        while(!endProgram)
//        {
//            while(SDL_PollEvent(e))
//            {
//                if( e->type==SDL_KEYDOWN)
//                {
//                    if(e->key.keysym.sym==SDLK_F11 && e->key.repeat==0)
//                    {
//                        if(windowState.fullScreen==false)
//                        {
//                            SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
//                            windowState.fullScreen=true;
//                            W=full_Screen.w;
//                            H=full_Screen.h;
//                        }
//
//                        else
//                        {
//                            SDL_SetWindowFullscreen(window,0);
//                            windowState.fullScreen= false;
//                            W=Available_Screen.w;
//                            H=Available_Screen.h;
//                        }
//                    }
//                    else if(e->key.keysym.sym==SDLK_ESCAPE)
//                    {
//                        endProgram= true;
//                    }
//                }
//                else if(e->type==SDL_MOUSEMOTION || e->type==SDL_MOUSEBUTTONUP)
//                {
//                    int x=e->motion.x;
//                    int y=e->motion.y;
//                    if(x<W && x>(W-W/20) && y>0 && y<H/20)
//                    {
//                        onCloseButton=true;
//
//                        if(e->type==SDL_MOUSEBUTTONUP)
//                        {
//                            if(e->button.button==SDL_BUTTON_LEFT)
//                                endProgram= true;
//                        }
//
//                    }
//                    else
//                    {
//                        onCloseButton= false;
//                    }
//
//                }
//            }
//
//
//            SDL_SetRenderDrawColor(renderer,0,0,0,255);
//            SDL_RenderClear(renderer);
//
//            double L=8;
//            if(onCloseButton)
//            {
//                SDL_SetRenderDrawColor(renderer,232,17,35,255);
//                SDL_RenderFillRect(renderer,&closeButton);
//                aalineRGBA(renderer,closeButton.x+closeButton.w/2-L/ sqrt(2),closeButton.y+closeButton.h/2-L/sqrt(2),closeButton.x+closeButton.w/2+L/sqrt(2),closeButton.y+closeButton.h/2+L/sqrt(2),214,214,214,255);
//                aalineRGBA(renderer,(closeButton.x+closeButton.w/2-L/ sqrt(2)),(closeButton.y+closeButton.h/2+L/sqrt(2)),(closeButton.x+closeButton.w/2+L/sqrt(2)),(closeButton.y+closeButton.h/2-L/sqrt(2)),214,214,214,255);
//                aalineRGBA(renderer,closeButton.x+closeButton.w/2-L/ sqrt(2),closeButton.y+closeButton.h/2-L/sqrt(2)-1,closeButton.x+closeButton.w/2+L/sqrt(2),closeButton.y+closeButton.h/2+L/sqrt(2)-1,214,214,214,255);
//                aalineRGBA(renderer,(closeButton.x+closeButton.w/2-L/ sqrt(2)),(closeButton.y+closeButton.h/2+L/sqrt(2))-1,(closeButton.x+closeButton.w/2+L/sqrt(2)),(closeButton.y+closeButton.h/2-L/sqrt(2))-1,214,214,214,255);
//
//            }
//            else if(!onCloseButton)
//            {
//                aalineRGBA(renderer,closeButton.x+closeButton.w/2-L/ sqrt(2),closeButton.y+closeButton.h/2-L/sqrt(2),closeButton.x+closeButton.w/2+L/sqrt(2),closeButton.y+closeButton.h/2+L/sqrt(2),214,214,214,255);
//                aalineRGBA(renderer,(closeButton.x+closeButton.w/2-L/ sqrt(2)),(closeButton.y+closeButton.h/2+L/sqrt(2)),(closeButton.x+closeButton.w/2+L/sqrt(2)),(closeButton.y+closeButton.h/2-L/sqrt(2)),214,214,214,255);
//                aalineRGBA(renderer,closeButton.x+closeButton.w/2-L/ sqrt(2),closeButton.y+closeButton.h/2-L/sqrt(2)-1,closeButton.x+closeButton.w/2+L/sqrt(2),closeButton.y+closeButton.h/2+L/sqrt(2)-1,214,214,214,255);
//                aalineRGBA(renderer,(closeButton.x+closeButton.w/2-L/ sqrt(2)),(closeButton.y+closeButton.h/2+L/sqrt(2))-1,(closeButton.x+closeButton.w/2+L/sqrt(2)),(closeButton.y+closeButton.h/2-L/sqrt(2))-1,214,214,214,255);
//            }
//
//
//
//
//            SDL_RenderPresent(renderer);
//
//
//
//        }
//    }