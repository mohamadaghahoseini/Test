#include "myheader.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>

void wireBoardRGBA(SDL_Renderer* m_renderer, int x, int y, int L, int n, UINT8 r, UINT8 g, UINT8 b, UINT8 a);
void checkerBoardColor(SDL_Renderer* m_renderer, int x, int y, int L, int n, UINT32 c1, UINT32 c2);

int main( int argc, char * argv[] )
{
    int n=10;
    //cout<<"Enter n:";
    //cin>>n;
    //Initialization of SDL windows
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;//SDL_WINDOW_BORDERLESS ;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    SDL_Texture* bkImg = nullptr;
    //Texture for loading image

    int img_w, img_h;
    SDL_Rect img_rect;


    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( 1920, 480, WND_flags, &m_window, &m_renderer );
    //Pass the focus to the drawing window
    SDL_RaiseWindow(m_window);
    //Get screen resolution
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int W = DM.w;
    int H = DM.h;
    cout<<W<<"x"<<H<<endl;


    bkImg = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, W, H);
    SDL_SetRenderTarget(m_renderer, bkImg);

    // Clear the window with a black background
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear( m_renderer );

    // Show the window
    SDL_RenderPresent( m_renderer );
    // Render a new color bar every 0.5 seconds
    for ( int i = 0; i < 256; i++)
    {
        aalineRGBA(m_renderer, i, 50, i, 500, i, 0, 0, 255);
        SDL_RenderPresent( m_renderer );
        SDL_Delay( 1 );
    }
    SDL_RenderPresent( m_renderer );

    //filledEllipseRGBA(m_renderer, 100, 100, 100, 50, 100, 200, 0, 255);
    filledEllipseColor(m_renderer, 100, 100, 100, 50, 0x80FF0000);
    hlineRGBA(m_renderer, 0, W, H/2, 0, 0, 255, 255);
    aalineRGBA(m_renderer, 200, 200, 400, 500, 0, 255, 0, 255);
    lineColor(m_renderer, 220, 220, 420, 520, 0xFF00FF00);

    int L = 500, x0=200, y0=200;
    for(int i = 0; i <= n; i++)
    {
        aalineRGBA(m_renderer, x0, y0 + i * L / n, x0 + i * L / n, y0+L, 255, 255, 255, 255);
        SDL_RenderPresent( m_renderer );
        SDL_Delay(20);
    }


    const char * text ="WELCOME TO SHARIF EE DEPARTMENT!!";
    stringRGBA(m_renderer, 100, 100, text, 255,255,255,255);

// 1 for lazy.ttf , 2 for arial.ttf , 3 for B Roya.ttf
    int font =2;
    int x_position=500;
    int y_position=600;
    int R=255;
    int G =2;
    int B=3;
    int A=0.5;
    SDL_Color text_color = { 250, 250, 250};

//textColor(m_renderer,x_position,y_position,text,font ,24,text_color);
//    textRGBA(m_renderer,x_position+100,y_position+100,text,font ,24,R,G,B,A);
    textRGBA(m_renderer, 100, 130, text, "Shabnam.ttf", 18, 0, 0 , 255, 255);
    Uint16 textUTF[]= {0xFEB0,0xFEE3,0xFE8E, 0xFEE0, 0xFEB3};
    textUTFRGBA(m_renderer, 100, 160, textUTF, "Shabnam.ttf", 38, 0, 255 , 255, 255);



    //Wait for a key to be pressed
    SDL_Event *e = new SDL_Event();
    while(e->type != SDL_KEYDOWN)
        SDL_PollEvent(e);

    //Loading image
    SDL_Texture* m_img = nullptr;
    m_img = IMG_LoadTexture(m_renderer, "golden.png");
    //Get the width and height of the texture
    SDL_QueryTexture(m_img, NULL, NULL, &img_w, &img_h);
    img_rect.x = 400;
    img_rect.y = 200;
    img_rect.w = img_w * 1.5;
    img_rect.h = img_h * 1.5;
    SDL_Rect img_src;
    img_src.x=0;//img_w/10;
    img_src.y=0;//img_h/10;
    img_src.w=img_w/1;
    img_src.h=img_h/1;
    // copy the texture to the rendering context
    SDL_RenderCopy(m_renderer, m_img, &img_src, &img_rect);
    SDL_RenderPresent( m_renderer );

    filledEllipseRGBA(m_renderer, 1100, 400, 100, 50, 100, 200, 0, 127);
    SDL_RenderPresent( m_renderer );

    SDL_SetRenderTarget(m_renderer, nullptr);
    SDL_RenderCopy(m_renderer, bkImg, nullptr, nullptr);
    SDL_RenderPresent(m_renderer);

    e->type = 0;
    int x=100, y=200, r=50, dx=20, dy=10;
    //Wait for a key to be pressed
    while(e->type != SDL_KEYDOWN)
    {
        SDL_PollEvent(e);
        filledEllipseRGBA(m_renderer, x, y, r,r, 255, 0, 0, 255);
        SDL_RenderPresent(m_renderer);
        SDL_Delay(50);

        SDL_RenderCopy(m_renderer, bkImg, nullptr, nullptr);

//        filledEllipseRGBA(m_renderer, x, y, r,r, 0, 0, 0, 255);
        x+=dx;
        y+=dy;
        if(x<r||x>W-r)
            dx=-dx;
        if(y<r||y>H-r)
            dy=-dy;
    }

    bool flag=true, reDraw=false;
    e->type = 0;
    while(flag)
    {
        SDL_PollEvent(e);
        if(e->type==SDL_KEYDOWN)
        {
            e->type=0;
            SDL_ShowCursor(SDL_ENABLE);
            switch(e->key.keysym.sym)
            {
                case SDLK_DOWN:
                    y+=dy;
                    if(y-r>H)
                        y=-r;
                    reDraw=true;
                    break;
                case SDLK_UP:
                    y-=dy;
                    if(y<-r)
                        y=H+r;
                    reDraw=true;
                    break;
                case SDLK_RIGHT:
                    x+=dx;
                    if(x-r>W)
                        x=-r;
                    reDraw=true;
                    break;
                case SDLK_LEFT:
                    x-=dx;
                    if(x<-r)
                        x=W+r;
                    reDraw=true;
                    break;
                case SDLK_ESCAPE:
                    flag=false;
                    break;

            }
        }
        else if(e->type == SDL_MOUSEMOTION)
        {
            e->type=0;
            x=e->motion.x;
            y=e->motion.y;
            reDraw=true;
            SDL_ShowCursor(SDL_DISABLE);
        }
        else if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            if(e->button.button == SDL_BUTTON_LEFT)
            {
                e->type=0;
                SDL_SetRenderTarget(m_renderer, bkImg);
                //rectangleRGBA(m_renderer, x, y, x+r, y+r, 0, 255, 0, 255);
                checkerBoardColor(m_renderer, x, y, (x+y)/4, 5, 0xFF00FF00, 0xFF0000FF);
                SDL_SetRenderTarget(m_renderer, nullptr);
                reDraw=true;

            }
        }

        if(reDraw)
        {
            SDL_RenderCopy(m_renderer, bkImg, nullptr, nullptr);
            //filledEllipseRGBA(m_renderer, x, y, r,r, 255, 0, 0, 255);
            //wireBoardRGBA(m_renderer, x, y, (x+y)/4, 5, 255,255,255,255);
            checkerBoardColor(m_renderer, x, y, (x+y)/4, 5, 0xFF00FF00, 0xFF0000FF);
            SDL_RenderPresent(m_renderer);
            reDraw=false;
        }
    }

    e->type=0;

    int xSun=300, ySun=300, rSun=20;
    int xEarth, yEarth, rOrbitX=150, rEarth=10, rOrbitY=80;
    double theta=0;

    while(e->type != SDL_KEYDOWN)
    {
        SDL_PollEvent(e);
        // Clear the window with a black background
        SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
        SDL_RenderClear( m_renderer );

        filledEllipseRGBA(m_renderer, xSun, ySun, rSun, rSun, 255, 0, 0, 255);
        xEarth = xSun+rOrbitX*cos(theta);
        yEarth = ySun-rOrbitY*sin(theta);
        theta+=0.05;
        filledEllipseRGBA(m_renderer, xEarth, yEarth, rEarth, rEarth, 0, 255,0, 255);
        SDL_RenderPresent(m_renderer);
        SDL_Delay(30);
    }


    //Finalize and free resources
    SDL_DestroyTexture(m_img);
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    IMG_Quit();
    SDL_Quit();

    return 0;

}

void wireBoardRGBA(SDL_Renderer* m_renderer, int x, int y, int L, int n, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
{
    for(int i=0; i<=n; i++)
        lineRGBA(m_renderer, x, y+i*L/n, x+L, y+i*L/n, r,g,b,a);
    for(int i=0; i<=n; i++)
        lineRGBA(m_renderer, x+i*L/n, y, x+i*L/n, y+L, r,g,b,a);


}

void checkerBoardColor(SDL_Renderer* m_renderer, int x, int y, int L, int n, UINT32 c1, UINT32 c2)
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            if((i+j)%2==0)
                boxColor(m_renderer, x+j*L/n, y+i*L/n, x+(j+1)*L/n, y+(i+1)*L/n, c1);
            else
                boxColor(m_renderer, x+j*L/n, y+i*L/n, x+(j+1)*L/n, y+(i+1)*L/n, c2);
        }

}