#include "RGSound.h"

///Static Declaration

//Sound
map<string,Mix_Chunk*> RGSound::soundMap;

//Music
map<string,Mix_Music*> RGSound::musicMap;


///Methods

RGSound::RGSound() {
}

void RGSound::init() {
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
}

void RGSound::loadMusic( string filename, string key ) {
    musicMap[key] =  Mix_LoadMUS( filename.c_str() );
    if(musicMap[key]==NULL) {
    }
}

void RGSound::playMusic( string key ) {
    Mix_PlayMusic( musicMap[key] , -1 );
}

void RGSound::loadSound( string filename, string key ) {
    soundMap[key] =  Mix_LoadWAV( filename.c_str() );
    if(soundMap[key]==NULL) {
    }
}

void RGSound::playSound( string key ) {
    Mix_PlayChannel( -1, soundMap[key], 0 );
}
