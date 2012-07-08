#include "RGGame.h"

RGGame::RGGame() {
}

RGGame::~RGGame() {
}

int RGGame::run() {
    RGGraphics::resize(640,480);
    RGGraphics::init();
    RGSound::init();
    init();
    while(!RGInput::quit()) {
        RGInput::input();
        logic();
        RGGraphics::render(&scene);
    }
    RGGraphics::end();

    return 0;
}

