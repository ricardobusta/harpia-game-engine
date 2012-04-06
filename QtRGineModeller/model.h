#ifndef MODEL_H
#define MODEL_H

#include "object.h"

class Model
{
public:
    Model();

    QString name;

    QList<Object> object;

    void load(QString filename);
};

#endif // MODEL_H
