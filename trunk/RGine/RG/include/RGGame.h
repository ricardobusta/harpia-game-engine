#ifndef RGGAME_H
#define RGGAME_H

#include "RGGraphics.h"
#include "RGInput.h"
#include "RGScene.h"
#include "RGSound.h"

class RGGame
{
    public:
        RGGame();
        virtual ~RGGame();

        RGGraphics graphics;
        RGSound sound;
        //RGInput in;

        RGScene scene;

        int run();

        virtual void logic()=0;
    protected:
    private:
};

#endif // RGGAME_H
