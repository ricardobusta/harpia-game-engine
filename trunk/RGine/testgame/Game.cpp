#include "Game.h"

#include "Sprite.h"

#include <cmath>

Game::Game() {
    //ctor
}

Game::~Game() {
    //dtor
}

void Game::logic() {
    static int ang = 0;
/*
    if(RGInput::key(SDLK_a).down) {
        RGSound::playSound("scratch");
    }
    if(RGInput::key(SDLK_s).down) {
        RGSound::playMusic("beat");
    }
    if(RGInput::key(SDLK_LEFT).isDown){
        s->x -=1;
    }
    if(RGInput::key(SDLK_RIGHT).isDown){
        s->x +=1;
    }
    if(RGInput::key(SDLK_UP).isDown){
        s->y +=10;
    }

    if(s->y > 0){
        s->y-=4;
    }else{
        s->y = 0;
    }
    //*/
    ang ++;
    s->x = 300+180*sin(ang*M_PI/180);
    s->y = 200+180*cos(ang*M_PI/180);
//*/
}

void Game::init() {
    RGGraphics::loadTexture( "media/img32.png" , "tex1");
//    RGGraphics::loadTexture( "media/image.bmp" , "tex1");
//    RGGraphics::loadTexture( "media/image2.bmp" , "tex2");
//    RGGraphics::loadTexture( "media/image3.bmp" , "tex3");
    RGGraphics::loadTexture( "media/image4.tga" , "tex4");
    RGSound::loadMusic( "media/beat.wav", "beat" );
    RGSound::loadSound( "media/scratch.wav", "scratch" );

    Sprite *sp = new Sprite();
    sp->setGeometry(640,0,640,480);
    sp->setGraphics("tex1");
    scene.addEntity(sp);

    s = new Sprite();
    s->setGeometry(64,64,64,64);
    s->setGraphics("tex4");

    sp->setGraphics("tex1");


    scene.addEntity(s);
}
