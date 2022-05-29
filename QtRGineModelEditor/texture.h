#ifndef TEXTURE_H
#define TEXTURE_H

#include <QString>
#include <QtOpenGL>
#include <QMap>
#include <QPixmap>

class Texture
{
public:
    Texture();

    QMap<uint,GLuint> list;
    QMap<uint,QPixmap> imgList;

    void set(uint hashcode);
    void load(QString filename);
    void clear();
};

#endif // TEXTURE_H
