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
private:
    ///Attributes

    //Quit event
    static bool quitTriggered;

    //SDL Event
    static SDL_Event event;

    //Keyboard Input
    static KeyStruct keyboardstate[SDLK_LAST];
    static list<int> keyboardMod;

    //Mouse Input
    static MouseStruct mousestate;

    ///Methods
    RGInput();

    //Keyboard Input
    static void keyboardReset();

    //Mouse Input
    static void mouseReset();
public:
    ///Methods

    //Main Loop
    static void input();
    static bool quit();

    //Keyboard
    static KeyStruct key(unsigned int k);
};

#endif // RGINPUT_H
