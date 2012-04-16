#include "texture.h"

#include <iostream>
using namespace std;

Texture::Texture()
{
}

void Texture::set(uint hashcode){
    glBindTexture( GL_TEXTURE_2D, list[hashcode] );
}

void Texture::load(QString filename)
{
    QImage tex;
    if( tex.load(filename) ){
        tex = QGLWidget::convertToGLFormat(tex);
        GLuint texId;
        glGenTextures( 1, &texId );
        glBindTexture( GL_TEXTURE_2D, texId );
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 4, tex.width(), tex.height(), 0, GL_RGBA,GL_UNSIGNED_BYTE, tex.bits());
        list[qHash(filename)] = texId;
    }
}

void Texture::clear()
{
    foreach(GLuint texId,list){
        glDeleteTextures( 1, &texId );
    }
    list.clear();
}
