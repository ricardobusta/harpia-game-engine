#include "RGGraphics.h"

RGGraphics::RGGraphics()
{
    width = 320;
    height = 240;
    depth = 32;
}

RGGraphics::~RGGraphics()
{
    //dtor
}

void RGGraphics::init()
{
    //sdl
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(width,height,depth,SDL_OPENGL|SDL_RESIZABLE);
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_WM_SetCaption( "RGine Game" , NULL);
    atexit(SDL_Quit);

    //opengl
    glClearColor(0,0,0,1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    resize(width,height);

    //fps control timer
    timerInit();
    timerStart();
}

void RGGraphics::resize(int w, int h)
{
    width = w;
    height = h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glViewport(0,0,width, height);
    glOrtho( 0.0,width, 0.0,height , -2000,1000);
    //glFrustum (-width/20,width/20, -height/20,height/20, 50,6000);
    //glMatrixMode(GL_TEXTURE);
    //texture
    glMatrixMode(GL_MODELVIEW);
}

void RGGraphics::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_LINE_STRIP);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);
    glVertex3f(100,100,0);
    glEnd();

    SDL_GL_SwapBuffers();
}

void RGGraphics::delay(){
    timerDelay();
}

void RGGraphics::end()
{
    SDL_Quit();
}

void RGGraphics::timerInit()
{
    timerStartTicks = 0;
    timerPausedTicks = 0;
    timerPaused = false;
    timerStarted = false;
}
void RGGraphics::timerStart()
{
    timerStarted = true;
    timerPaused = false;
    timerStartTicks = SDL_GetTicks();
}
void RGGraphics::timerStop()
{
    timerStarted = false;
    timerPaused = false;
}
void RGGraphics::timerPause()
{
    if ( ( timerStarted == true ) && ( timerPaused == false ) )
    {
        timerPaused = true;
        timerPausedTicks = SDL_GetTicks() - timerStartTicks;
    }
}
void RGGraphics::timerUnpause()
{
    if ( timerPaused == true )
    {
        timerPaused = false;
        timerStartTicks = SDL_GetTicks() - timerPausedTicks;
        timerPausedTicks = 0;
    }
}
int RGGraphics::timerGetTicks()
{
        if ( timerStarted == true ){
        if ( timerPaused == true ){
            return timerPausedTicks;
        }else{
            return SDL_GetTicks() - timerStartTicks;
        }
    }
    return 0;
}
void RGGraphics::timerDelay()
{
        if ( timerGetTicks() < 1000 / fps ) {
        SDL_Delay( ( 1000 / fps ) - timerGetTicks() );
    }
}
