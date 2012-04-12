#ifndef MODELOBJECT_H
#define MODELOBJECT_H

#include <QString>
#include <QMap>
#include "modelvertex.h"
#include "modelnormal.h"
#include "modeltexcoord.h"
#include "modelface.h"

class ModelObject
{
public:
    ModelObject();

    QString name;

    QMap<int, ModelVertex> vertex;
    QMap<int, ModelNormal> normal;
    QMap<int, ModelTexCoord> texcoord;

    bool hide;
    int material;
    QString texture;
    QMap<int, ModelFace> face;
};

#endif // MODELOBJECT_H
