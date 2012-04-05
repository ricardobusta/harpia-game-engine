#ifndef RGGAME_H
#define RGGAME_H

#include "RGGraphics.h"
#include "RGInput.h"
#include "RGScene.h"

class RGGame
{
    public:
        RGGame();
        virtual ~RGGame();

        RGGraphics graphics;
        //RGInput in;

        RGScene scene;

        int run();

        virtual void logic();
    protected:
    private:
};

#endif // RGGAME_H
