#ifndef OBJECT_H
#define OBJECT_H

#include <QList>
#include "vertex.h"
#include <QString>

class Object
{
public:
    Object();

    QString name;

    QList<Vertex> vertex;
};

#endif // OBJECT_H
