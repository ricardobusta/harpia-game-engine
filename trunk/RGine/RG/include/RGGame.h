#ifndef RGGAME_H
#define RGGAME_H

#include "RGGraphics.h"
#include "RGInput.h"

class RGGame
{
    public:
        RGGame();
        virtual ~RGGame();

        int run();
    protected:
    private:
};

#endif // RGGAME_H
