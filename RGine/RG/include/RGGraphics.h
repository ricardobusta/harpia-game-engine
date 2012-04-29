#ifndef RGGRAPHICS_H
#define RGGRAPHICS_H

/**
 * TODO make this class virtual and reimplement many forms of graphics
 * including pure SDL, SDL+OpenGL etc...
 */

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"

#include <map>
#include <iostream>
using namespace std;

class RGGraphics {
public:

//Main Game Loop
    static void init();
    static void resize(int width, int height);
    static void render(/*scene*/);
    static void delay();
    static void end();

//Texture Management
    static map<string,GLuint> textureMap;
    static void loadTexture(string filename, string key);
    static void useTexture(string key);

protected:
private:
    RGGraphics();

    static int width;
    static int height;
    static int depth;

    //TIMER
    static int timerStartTicks;
    static int timerPausedTicks;
    static bool timerPaused;
    static bool timerStarted;
    static int fps;

    static void timerInit();
    static void timerStart();
    static void timerStop();
    static void timerPause();
    static void timerUnpause();
    static int timerGetTicks();
    static void timerDelay();
};

#endif // RGGRAPHICS_H
