#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QString>
#include "modelobject.h"
#include "modelanimation.h"
#include "material.h"

class Model
{
public:
    Model();

    QString name;

    int keyframeCount;

    //each separated object on the model. has its own vertexes, normals, material and texture.
    QMap<QString,ModelObject> object;
    //each interval of animation (starting frame and ending frame)
    QMap<QString, ModelAnimation> animation;
    //map each keyframe into it's frame position
    QMap<int,int> keyframe;
    //materials
    QMap<int,Material> material;

    void load(QString filename);
    void addFace();

    /*-------------*/
    QString currentObject;

};

#endif // MODEL_H
