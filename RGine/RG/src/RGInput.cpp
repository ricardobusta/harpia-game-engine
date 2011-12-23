#include "RGInput.h"

RGInput::RGInput() {
    quitTriggered = false;
}

RGInput::~RGInput() {
    //dtor
}

bool RGInput::quit(){
    return quitTriggered;
}

void RGInput::keyboardReset() {
    list<int>::iterator it;
    for (it = keyboardMod.begin(); it != keyboardMod.end(); it++) {
        keyboardstate[(*it)].up = false;
        keyboardstate[(*it)].down = false;
    }
    keyboardMod.clear();
}

void RGInput::mouseReset() {
    mousestate.left.up = false;
    mousestate.left.down = false;

    mousestate.right.up = false;
    mousestate.right.down = false;

    mousestate.middle.up = false;
    mousestate.middle.down = false;

    mousestate.speed.x = 0;
    mousestate.speed.y = 0;
}

void RGInput::input() {
    keyboardReset();
    //resetar estado do mouse
    mouseReset();
    //agora detecta possiveis teclas
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            quitTriggered = true;
            break;
        case SDL_MOUSEMOTION:
            mousestate.speed.x = event.button.x-mousestate.position.x;
            mousestate.speed.y = event.button.y-mousestate.position.y;

            mousestate.position.x = event.motion.x;
            mousestate.position.y = event.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button==SDL_BUTTON_LEFT) {
                mousestate.left.isDown=true;
                mousestate.left.down=true;
            }
            if (event.button.button==SDL_BUTTON_RIGHT) {
                mousestate.right.isDown=true;
                mousestate.right.down=true;
            }
            if (event.button.button==SDL_BUTTON_MIDDLE) {
                mousestate.middle.isDown=true;
                mousestate.middle.down=true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button==SDL_BUTTON_LEFT) {
                mousestate.left.isDown=false;
                mousestate.left.up=true;
            }
            if (event.button.button==SDL_BUTTON_RIGHT) {
                mousestate.right.isDown=false;
                mousestate.right.up=true;
            }
            if (event.button.button==SDL_BUTTON_MIDDLE) {
                mousestate.middle.isDown=false;
                mousestate.middle.up=true;
            }
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
            default:
                keyboardstate[event.key.keysym.sym].down=true;
                keyboardstate[event.key.keysym.sym].isDown=true;
                keyboardMod.push_back(event.key.keysym.sym);
                break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym) {
            default:
                keyboardstate[event.key.keysym.sym].up=true;
                keyboardstate[event.key.keysym.sym].isDown=false;
                keyboardMod.push_back(event.key.keysym.sym);
                break;
            }
            break;
        default:
            break;
        }
    }
}
