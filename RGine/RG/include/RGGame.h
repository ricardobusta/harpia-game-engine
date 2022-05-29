#ifndef RGGAME_H
#define RGGAME_H

#include "RGGraphics.h"
#include "RGInput.h"
#include "RGScene.h"
#include "RGSound.h"

class RGGame {
public:
    RGGame();
    virtual ~RGGame();

    RGScene scene;

    int run();

    virtual void init()=0;
    virtual void logic()=0;
protected:
private:
};

#endif // RGGAME_H
