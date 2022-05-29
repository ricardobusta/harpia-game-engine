#ifndef RGSCENE_H
#define RGSCENE_H

#include <map>
#include <RGEntity.h>
using namespace std;

class RGScene
{
    public:
        RGScene();
        virtual ~RGScene();

        int entID;
        map<int,RGEntity*> entities;

        void render();

        void addEntity(RGEntity *entity);
    protected:
    private:
};

#endif // RGSCENE_H
