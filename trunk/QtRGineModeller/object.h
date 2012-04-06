#ifndef OBJECT_H
#define OBJECT_H

#include <QMap>
#include "vertex.h"
#include <QString>

class Object
{
public:
    Object();

    QString name;

    QMap<QString,Vertex> vertex;
};

#endif // OBJECT_H
