#include "RGSound.h"

RGSound::RGSound()
{
    //ctor
}

RGSound::~RGSound()
{
    //dtor

    //TODO clean sounds.
}

void RGSound::init(){
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

    loadMusic( "media\\beat.wav", "beat" );
    loadSound( "media\\scratch.wav", "scratch" );

    playMusic("beat");
    playSound("scratch");
}

void RGSound::loadMusic( string filename, string key ){
    musicMap[key] =  Mix_LoadMUS( filename.c_str() );
    if(musicMap[key]==NULL){
    }
}

void RGSound::playMusic( string key ){
    Mix_PlayMusic( musicMap[key] , -1 );
}

void RGSound::loadSound( string filename, string key ){
    soundMap[key] =  Mix_LoadWAV( filename.c_str() );
    if(soundMap[key]==NULL){
    }
}

void RGSound::playSound( string key ){
    Mix_PlayChannel( -1, soundMap[key], 0 );
}
