#include "RGGame.h"

RGGame::RGGame() {
}

RGGame::~RGGame() {
}

int RGGame::run() {
    RGGraphics graphics;
    RGInput in;
    graphics.init();
    while(!in.quit()) {
        in.input();
        graphics.render();
        graphics.delay();
    }
    graphics.end();
    return 0;
}
