#ifndef RGSOUND_H
#define RGSOUND_H

#include <SDL/SDL_mixer.h>
#include <map>
#include <string>
using namespace std;

class RGSound {
private:
    RGSound();

    ///Attributes

    //Sound
    static map<string,Mix_Chunk*> soundMap;

    //Music
    static map<string,Mix_Music*> musicMap;

    ///Methods
public:

    ///Attributes

    ///Methods

    //Initialization
    static void init();

    //Sound
    static void loadSound(string filename, string key);
    static void playSound( string key );

    //Music
    static void loadMusic(string filename, string key);
    static void playMusic( string key );
};

#endif // RGSOUND_H
