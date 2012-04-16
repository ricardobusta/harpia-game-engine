#ifndef TEXTURE_H
#define TEXTURE_H

#include <QString>
#include <QtOpenGL>
#include <QMap>

class Texture
{
public:
    Texture();

    QMap<uint,GLuint> list;

    void set(uint hashcode);
    void load(QString filename);
    void clear();
};

#endif // TEXTURE_H
