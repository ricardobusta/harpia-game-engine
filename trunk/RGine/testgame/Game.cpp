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
    if(RGInput::key(SDLK_LEFT).isDown){
        s->x -=4;
    }
    if(RGInput::key(SDLK_RIGHT).isDown){
        s->x +=4;
    }
    if(RGInput::key(SDLK_UP).isDown){
        s->y +=10;
    }

    if(s->y > 0){
        s->y-=4;
    }else{
        s->y = 0;
    }

}

void Game::init() {
    RGGraphics::loadTexture( "media/image.bmp" , "tex1");
    RGGraphics::loadTexture( "media/image2.bmp" , "tex2");
    RGGraphics::loadTexture( "media/image3.bmp" , "tex3");
    RGGraphics::loadTexture( "media/image4.tga" , "tex4");
    RGSound::loadMusic( "media/beat.wav", "beat" );
    RGSound::loadSound( "media/scratch.wav", "scratch" );

    s = new Sprite();
    s->setGeometry(100,100,100,100);
    s->setGraphics("tex1");

    scene.addEntity(s);
}
