#ifndef SPRITE_H
#define SPRITE_H

#include <RGEntity.h>


class Sprite : public RGEntity
{
    public:
        Sprite();
        virtual ~Sprite();

        void render();

        int x, y;
        int w, h;

        void setGeometry(int x, int y, int w, int h);
    protected:
    private:
};

#endif // SPRITE_H
