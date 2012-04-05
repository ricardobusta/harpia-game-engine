#ifndef RGGAME_H
#define RGGAME_H

#include "RGGraphics.h"
#include "RGInput.h"

class RGGame
{
    public:
        RGGame();
        virtual ~RGGame();

        RGGraphics graphics;
        //RGInput in;

        int run();
    protected:
    private:
};

#endif // RGGAME_H
