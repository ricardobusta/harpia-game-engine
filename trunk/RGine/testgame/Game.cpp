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
    RGGraphics::loadTexture( "media/image.bmp" , "tex1");
    RGGraphics::loadTexture( "media/image2.bmp" , "tex2");
    RGGraphics::loadTexture( "media/image3.bmp" , "tex3");
    //RGGraphics::loadTexture( "media/sprite_test.png" , "tex4");
    sound.loadMusic( "media/beat.wav", "beat" );
    sound.loadSound( "media/scratch.wav", "scratch" );
}
