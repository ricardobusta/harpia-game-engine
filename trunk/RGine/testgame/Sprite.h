#ifndef SPRITE_H
#define SPRITE_H

#include <RGEntity.h>

#include <string>
#include <map>
using namespace std;

class SpriteTexCoords {
public:
    float x1;
    float y1;
    float x2;
    float y2;

    SpriteTexCoords(float x1, float y1, float x2, float y2){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
};

class Sprite : public RGEntity {
public:
    Sprite();
    virtual ~Sprite();

    void render();

    //body
    int x, y;
    int w, h;

    //visual
    int current_frame;
    string tex;
    map<int,SpriteTexCoords*> frame;

    void setGeometry(int x, int y, int w, int h);
    void setGraphics(string tex);
protected:
private:
};

#endif // SPRITE_H
