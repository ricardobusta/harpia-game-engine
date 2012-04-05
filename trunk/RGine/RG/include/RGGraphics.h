#ifndef RGGRAPHICS_H
#define RGGRAPHICS_H

/**
 * TODO make this class virtual and reimplement many forms of graphics
 * including pure SDL, SDL+OpenGL etc...
 */

 #include "SDL/SDL.h"
 #include "SDL/SDL_opengl.h"
 #include "SDL/SDL_image.h"

 #include <iostream>
 using namespace std;

class RGGraphics
{
    public:
        RGGraphics();
        virtual ~RGGraphics();

        void init();
        void resize(int width, int height);
        void render(/*scene*/);
        void delay();
        void end();

//Texture tests
        GLuint loadTexture(string filename);
        GLuint texture1;
        GLuint texture2;
    protected:
    private:
        int width;
        int height;
        int depth;

    //TIMER
        int timerStartTicks;
        int timerPausedTicks;
        bool timerPaused;
        bool timerStarted;
        int fps;

        void timerInit();
        void timerStart();
        void timerStop();
        void timerPause();
        void timerUnpause();
        int timerGetTicks();
        void timerDelay();
};

#endif // RGGRAPHICS_H
