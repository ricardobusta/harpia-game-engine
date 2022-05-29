#ifndef GAME_H
#define GAME_H

#include "RGGame.h"

class Sprite;

class Game:public RGGame
{
    public:
        Game();
        virtual ~Game();

        Sprite *s;
        Sprite *obj;

        void init();
        void logic();
    protected:
    private:
};

#endif // GAME_H
