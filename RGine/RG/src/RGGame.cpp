#include "RGGame.h"

RGGame::RGGame() {
}

RGGame::~RGGame() {
}

int RGGame::run() {
    RGGraphics::init();
    RGSound::init();
    init();
    while(!RGInput::quit()) {
        RGInput::input();
        logic();
        RGGraphics::render();
        RGGraphics::delay();
    }
    RGGraphics::end();

    return 0;
}

