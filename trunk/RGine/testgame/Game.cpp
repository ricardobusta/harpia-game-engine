#include "Game.h"

#include "Sprite.h"

Game::Game() {
    //ctor
}

Game::~Game() {
    //dtor
}

void Game::logic() {
    if(RGInput::key(SDLK_a).down) {
        RGSound::playSound("scratch");
    }
    if(RGInput::key(SDLK_s).down) {
        RGSound::playMusic("beat");
    }
}

void Game::init() {
    RGGraphics::loadTexture( "media/image.bmp" , "tex1");
    RGGraphics::loadTexture( "media/image2.bmp" , "tex2");
    RGGraphics::loadTexture( "media/image3.bmp" , "tex3");
    RGGraphics::loadTexture( "media/image4.tga" , "tex4");
    RGSound::loadMusic( "media/beat.wav", "beat" );
    RGSound::loadSound( "media/scratch.wav", "scratch" );

    Sprite *s = new Sprite();
    s->setGeometry(100,100,100,100);

    scene.addEntity(s);

}
