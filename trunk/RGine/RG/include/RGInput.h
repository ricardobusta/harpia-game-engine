#ifndef RGINPUT_H
#define RGINPUT_H

/**
 *  Currently using SDL keyboard input. Make this class virtual.
 */

#include "SDL/SDL.h"
#include <list>
using namespace std;

struct KeyStruct {
public:
    /*TODO make private*/
    bool up; //Key was lifted during that frame
    bool down; //Key was pressed during that frame
    bool isDown; //Key is down
    KeyStruct() {
        up = false;
        down = false;
        isDown = false;
    }
};

struct IntXY {
    int x;
    int y;
    IntXY() {
        x=0;
        y=0;
    }
};

struct MouseStruct {
public:
    /*TODO make private*/
    KeyStruct left,right,middle;
    IntXY position, speed;
};

class RGInput {
public:
    RGInput();
    virtual ~RGInput();

    void input();
    bool quit();
protected:
public:
    SDL_Event event;

    //Quit event
    bool quitTriggered;

    //Keyboard Input
    KeyStruct keyboardstate[SDLK_LAST];
    list<int> keyboardMod;
    void keyboardReset();

    //Mouse Input
    MouseStruct mousestate;
    void mouseReset();
};

#endif // RGINPUT_H
