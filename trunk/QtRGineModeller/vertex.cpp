#include "vertex.h"

Vertex::Vertex()
{
}

Vertex Vertex::operator =(Vertex v){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->u = v.u;
    this->v = v.v;
    this->r = v.r;
    this->g = v.g;
    this->b = v.b;

    return *this;
}

void Vertex::setXYZ(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vertex::setNXNYNZ(float nx, float ny, float nz){
    this->nx = nx;
    this->ny = ny;
    this->nz = nz;
}


void Vertex::setUV(float u, float v){
    this->u = u;
    this->v = v;
}

void Vertex::setRGB(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}
