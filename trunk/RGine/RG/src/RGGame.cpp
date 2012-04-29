#include "RGGame.h"

RGGame::RGGame() {
}

RGGame::~RGGame() {
}

int RGGame::run() {
    RGGraphics::init();
    sound.init();
    init();
    while(!in.quit()) {
        in.input();
        logic();
        RGGraphics::render();
        RGGraphics::delay();
    }
    RGGraphics::end();

    return 0;
}

