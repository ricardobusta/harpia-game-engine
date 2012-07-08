#include "Sprite.h"

#include "RGGraphics.h"

Sprite::Sprite()
{
    //ctor
}

Sprite::~Sprite()
{
    //dtor
}

void Sprite::render(){
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0,1);
    glVertex3f(x-w,y,100);
    glTexCoord2f(1,1);
    glVertex3f(x,y,100);
    glTexCoord2f(1,0);
    glVertex3f(x,y+h,100);
    glTexCoord2f(0,0);
    glVertex3f(x-w,y+h,100);
    glEnd();
}

void Sprite::setGeometry(int x, int y, int w, int h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}
