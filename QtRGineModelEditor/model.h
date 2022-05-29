#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QString>
#include "material.h"
#include "normal.h"
#include "texture.h"

/**************************************************************************\
    Model Structure Classes
\**************************************************************************/

enum CURRENT_EDIT_MODE{CURRENT_NONE,CURRENT_MODEL,CURRENT_OBJECT,CURRENT_VERTEX,CURRENT_PIVOT,CURRENT_NORMAL,CURRENT_TEXTURE,CURRENT_FACE,CURRENT_MATERIAL};

const uint nullStringHash = qHash("");

class ModelAnimation
{
public:
    ModelAnimation(){
        keyframeStart=keyframeEnd=0;
    }

    int keyframeStart;
    int keyframeEnd;
};

class ModelNormal
{
public:
    ModelNormal(){
        at=0;
    }

    int id;

    int at;
};

class ModelVertex
{
public:
    ModelVertex(){
        x=y=z=0;
    }

    int id;

    float x,y,z;
};

class ModelTexCoord
{
public:
    ModelTexCoord(){
        u=v=0;
    }

    int id;

    float u,v;
};

class ModelFace
{
public:
    ModelFace(){
        for(int i=0;i<3;i++){
            vertex[i]=normal[i]=texcoord[i]=0;
        }
    }

    int id;

    int vertex[3];
    int normal[3];
    int texcoord[3];
};

class ModelPivot{
public:
    ModelPivot(){
        x = y = z = 0;
        at = 0;
    }

    QString name;

    int id;

    float x,y,z;
    int at;
};

class ModelObject
{
public:
    ModelObject(){
        material=0;
        texture=nullStringHash;
        hide=false;
    }

    QString name;

    bool hide; //make per-keyframe option
    int material;
    uint texture;
    QString textureFileName;

    QMap<int, ModelVertex> vertex;
    QMap<int, ModelNormal> normal;
    QMap<int, ModelTexCoord> texcoord;
    QMap<int, ModelFace> face;
    QMap<int, ModelPivot> pivot;
};

/**************************************************************************\
    Main Model Class
\**************************************************************************/

class Model
{
public:
    Model();

    QString name;

    int keyframeCount;

    Texture texture;
    //each separated object on the model. has its own vertexes, normals, material and texture.
    QMap<uint,ModelObject> object;
    //each interval of animation (starting frame and ending frame)
    QMap<uint, ModelAnimation> animation;
    //map each keyframe into it's frame position
    QMap<int,int> keyframe;
    //materials
    QMap<int,Material> material;

    void clear();
    void save(QString filename);
    void load(QString filename);

    CURRENT_EDIT_MODE current_mode;

    uint currentObjectId;
    int maxMaterialId;
    int maxNormalId;
    int maxVertexId;
    int maxFaceId;
    int maxTextureId;
    int maxPivotId;

    int currentMaterialId;
    int currentNormalId;
    int currentVertexId;
    int currentFaceId;
    int currentTextureId;
    int currentPivotId;

    ModelVertex *currentVertex();
    ModelNormal *currentNormal();
    ModelFace *currentFace();
    ModelTexCoord *currentTexture();
    ModelObject *currentObject();
    ModelPivot *currentPivot();

    int currentFaceVNumber;

    /* Object Control */
    bool addObject();
    bool removeObject();

    /* Material Control */
    bool addMaterial();
    bool removeMaterial();

    /* Face Control */
    bool addFace();
    bool removeFace();

    /* Vertex Control */
    bool addVertex();
    bool removeVertex();

    /* Normal Control */
    bool addNormal();
    bool removeNormal();

    /* TextureControl */
    bool addTexture();
    bool removeTexture();

    /* Pivot Control */
    bool addPivot();
    bool removePivot();
};

#endif // MODEL_H
