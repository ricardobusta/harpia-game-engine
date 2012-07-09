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
    int delta_time_ticks;
    while(!RGInput::quit()) {
        //delta_time_ticks = SDL_GetTicks();
        RGInput::input();
        logic();
        RGGraphics::render(&scene);
        delta_time_ticks = SDL_GetTicks() - delta_time_ticks;
        //cout << delta_time_ticks << endl;
    }
    RGGraphics::end();

    return 0;
}

