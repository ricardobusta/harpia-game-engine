#include "Game.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::logic(){
    if(in.keyboardstate[SDLK_a].down){
        sound.playSound("scratch");
    }
    if(in.keyboardstate[SDLK_s].down){
        sound.playMusic("beat");
    }
}

void Game::init(){
    graphics.loadTexture( "media/image.bmp" , "tex1");
    graphics.loadTexture( "media/image2.bmp" , "tex2");
    graphics.loadTexture( "media/image3.bmp" , "tex3");
    sound.loadMusic( "media/beat.wav", "beat" );
    sound.loadSound( "media/scratch.wav", "scratch" );
}
