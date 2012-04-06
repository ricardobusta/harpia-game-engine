#ifndef VERTEX_H
#define VERTEX_H

#include <QString>

class Vertex
{
public:
    Vertex();

    QString name;
    QString facename;
    QString objectname;

    float x,y,z;
    float nx,ny,nz;
    float u,v;
    float r,g,b;

    void setXYZ(float x, float y, float z);
    void setNXNYNZ(float nx, float ny, float nz);
    void setUV(float u, float v);
    void setRGB(float r, float g, float b);

    Vertex operator=(Vertex v);
};

#endif // VERTEX_H
