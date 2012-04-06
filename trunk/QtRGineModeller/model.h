#ifndef MODEL_H
#define MODEL_H

#include "object.h"

class Model
{
public:
    Model();

    QString name;

    QMap<QString,Object> object;

    void load(QString filename);
    void save(QString filename);

    void clear();

    int facecount;
    int vertcount;

    QString currentObject;
    QString currentFace;
    QString currentVertex;
};

#endif // MODEL_H
