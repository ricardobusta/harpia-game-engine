#include "RGGame.h"

RGGame::RGGame() {
}

RGGame::~RGGame() {
}

int RGGame::run() {
    RGGraphics graphics;
    RGInput input;
    graphics.init();
    while(!input.quit()) {
        input.input();
        graphics.render();
        graphics.delay();
    }
    graphics.end();
    return 0;
}
