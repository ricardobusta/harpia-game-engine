#include "RGGame.h"

RGGame::RGGame() {
}

RGGame::~RGGame() {
}

int RGGame::run() {
    RGInput in;

    graphics.init();
    sound.init();
    while(!in.quit()) {
        in.input();
        graphics.render();
        graphics.delay();
    }
    graphics.end();

    return 0;
}

