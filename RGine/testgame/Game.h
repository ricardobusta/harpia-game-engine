#ifndef GAME_H
#define GAME_H

#include "RGGame.h"

class Game:public RGGame
{
    public:
        Game();
        virtual ~Game();

        void init();
        void logic();
    protected:
    private:
};

#endif // GAME_H
