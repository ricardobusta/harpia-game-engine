#include "RGGame.h"

RGGame::RGGame() {
}

RGGame::~RGGame() {
}

int RGGame::run() {
    graphics.init();
    sound.init();
    init();
    while(!in.quit()) {
        in.input();
        logic();
        graphics.render();
        graphics.delay();
    }
    graphics.end();

    return 0;
}

