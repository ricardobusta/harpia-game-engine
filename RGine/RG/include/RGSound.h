#ifndef RGSOUND_H
#define RGSOUND_H

#include <SDL/SDL_mixer.h>
#include <map>
#include <string>
using namespace std;

class RGSound
{
    public:
        RGSound();
        virtual ~RGSound();

        void init();

        void loadSound(string filename, string key);
        map<string,Mix_Chunk*> soundMap;
        void playSound( string key );

        void loadMusic(string filename, string key);
        map<string,Mix_Music*> musicMap;
        void playMusic( string key );
    protected:
    private:
};

#endif // RGSOUND_H
