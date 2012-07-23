#include "Sprite.h"

#include "RGGraphics.h"

Sprite::Sprite()
{
    w = h = 32;
    x = y = 0;
    current_frame = 0;
    frame[0] = new SpriteTexCoords(0,0,1,1);
}

Sprite::~Sprite()
{
}

void Sprite::render(){
    RGGraphics::useTexture(tex);
    cout << tex << endl;
    glBegin(GL_QUADS);
    //glNormal3f(0,0,1);
    glTexCoord2f(frame[current_frame]->x1,frame[current_frame]->y2);
    glVertex2f(x-w,y);
    glTexCoord2f(frame[current_frame]->x2,frame[current_frame]->y2);
    glVertex2f(x,y);
    glTexCoord2f(frame[current_frame]->x2,frame[current_frame]->y1);
    glVertex2f(x,y+h);
    glTexCoord2f(frame[current_frame]->x1,frame[current_frame]->y1);
    glVertex2f(x-w,y+h);
    glEnd();
}


void Sprite::setGraphics(string tex){
    this->tex = tex;
}

void Sprite::setGeometry(int x, int y, int w, int h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}
