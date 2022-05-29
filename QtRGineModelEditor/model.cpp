#include "model.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>

#include <iostream>
using namespace std;

Model::Model()
{
    clear();
}

/* Support Methods */

ModelVertex *Model::currentVertex()
{
    if(current_mode == CURRENT_VERTEX){
        return &currentObject()->vertex[currentVertexId];
    }else{
        return NULL;
    }
}

ModelNormal *Model::currentNormal()
{
    if(current_mode == CURRENT_NORMAL){
        return &currentObject()->normal[currentNormalId];
    }else{
        return NULL;
    }
}

ModelFace *Model::currentFace()
{
    if(current_mode == CURRENT_FACE){
        return &currentObject()->face[currentFaceId];
    }else{
        return NULL;
    }
}

ModelTexCoord *Model::currentTexture(){
    if(current_mode == CURRENT_TEXTURE){
        return &currentObject()->texcoord[currentTextureId];
    }else{
        return NULL;
    }
}

ModelObject *Model::currentObject(){
    if(currentObjectId!=nullStringHash){
        return &object[currentObjectId];
    }else{
        return NULL;
    }
}

ModelPivot *Model::currentPivot(){
    if(current_mode == CURRENT_PIVOT){
        return &currentObject()->pivot[currentPivotId];
    }else{
        return NULL;
    }
}

/* Model Control Methods */

void Model::clear(){
    keyframeCount = 0;
    currentObjectId = nullStringHash;

    maxMaterialId = -1;
    maxNormalId = -1;
    maxFaceId = -1;
    maxVertexId = -1;
    maxTextureId = -1;
    maxPivotId = -1;

    currentMaterialId = -1;
    currentNormalId = -1;
    currentFaceId = -1;
    currentVertexId = -1;
    currentTextureId = -1;
    currentPivotId = -1;

    foreach(ModelObject o, object){
        o.normal.clear();
        o.texcoord.clear();
        o.face.clear();
        o.vertex.clear();
        o.pivot.clear();
    }
    animation.clear();
    object.clear();
    keyframe.clear();
    material.clear();
}

void Model::load(QString filename)
{
    clear();
    texture.clear();

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        QString line = in.readLine();
        uint currentObject = nullStringHash;
        int currentId;
        while (!line.isNull()) {
            QStringList list;
            QStringList listassist;
            list = line.split(" ");
            if(list.at(0).length()!=1){
                //loadError();
            }

            switch(list.first().toAscii().at(0)){
            case '#':
                break;
            case 's':
                if(list.size()==2){
                    name = list.at(1);
                }else{
                    //loadError();
                }
                break;
            case 'k':
                if(list.size()==2){
                    keyframe[keyframeCount++] = list.at(1).toInt();
                }else{
                    //loadError();
                }
                break;
            case 'a':
                if(list.size()==2){
                    uint id = qHash(list.at(1));
                    animation[id] = ModelAnimation();
                    animation[id].keyframeStart = list.at(2).toInt();
                    animation[id].keyframeEnd = list.at(3).toInt();
                }else{
                    //loadError();
                }
                break;
            case 'm':
                if(list.size()==15){
                    int id = list.at(1).toInt();
                    material[id] = Material();

                    material[id].id = id;

                    material[id].emission[0] = list.at(2).toFloat();
                    material[id].emission[1] = list.at(3).toFloat();
                    material[id].emission[2] = list.at(4).toFloat();
                    material[id].emission[3] = list.at(5).toFloat();

                    material[id].diffuse[0] = list.at(6).toFloat();
                    material[id].diffuse[1] = list.at(7).toFloat();
                    material[id].diffuse[2] = list.at(8).toFloat();
                    material[id].diffuse[3] = list.at(9).toFloat();

                    material[id].specular[0] = list.at(10).toFloat();
                    material[id].specular[1] = list.at(11).toFloat();
                    material[id].specular[2] = list.at(12).toFloat();
                    material[id].specular[3] = list.at(13).toFloat();

                    material[id].shininess[0] = list.at(14).toFloat();
                }else{
                    //loadError();
                }
                break;
            case 'o':
                if(list.size()==4){
                    currentObject = qHash(list.at(1));
                    object[currentObject] = ModelObject();
                    object[currentObject].name = list.at(1);
                    object[currentObject].material = list.at(2).toInt();
                    object[currentObject].textureFileName = list.at(3);
                    object[currentObject].texture = qHash(list.at(3));
                    texture.load(list.at(3));
                }else{
                    //loadError();
                }
                break;
            case 'v':
                if(list.size()==5){
                    currentId = list.at(1).toInt();
                    if(currentId > maxVertexId){
                        maxVertexId = currentId;
                    }
                    object[currentObject].vertex[currentId] = ModelVertex();
                    object[currentObject].vertex[currentId].id = currentId;
                    object[currentObject].vertex[currentId].x = list.at(2).toFloat();
                    object[currentObject].vertex[currentId].y = list.at(3).toFloat();
                    object[currentObject].vertex[currentId].z = list.at(4).toFloat();
                }else{
                    //loadError();
                }
                break;
            case 'n':
                if(list.size()==3){
                    currentId = list.at(1).toInt();
                    if(currentId > maxNormalId){
                        maxNormalId = currentId;
                    }
                    object[currentObject].normal[currentId] = ModelNormal();
                    object[currentObject].normal[currentId].id = currentId;
                    object[currentObject].normal[currentId].at = list.at(2).toInt();
                }else{
                    //loadError();
                }
                break;
            case 't':
                if(list.size()==4){
                    currentId = list.at(1).toInt();
                    if(currentId > maxTextureId){
                        maxTextureId = currentId;
                    }
                    object[currentObject].texcoord[currentId] = ModelTexCoord();
                    object[currentObject].texcoord[currentId].id = currentId;
                    object[currentObject].texcoord[currentId].u = list.at(2).toFloat();
                    object[currentObject].texcoord[currentId].v = list.at(3).toFloat();
                }else{
                    //loadError();
                }
                break;
            case 'f':
                currentId = list.at(1).toInt();
                if(currentId > maxFaceId){
                    maxFaceId = currentId;
                }
                object[currentObject].face[currentId] = ModelFace();
                if(list.size()==5){
                    for(int i=0;i<3;i++){
                        listassist = list.at(i+2).split("/");
                        object[currentObject].face[currentId].id = currentId;
                        object[currentObject].face[currentId].vertex[i]=listassist.at(0).toFloat();
                        object[currentObject].face[currentId].texcoord[i]=listassist.at(1).toFloat();
                        object[currentObject].face[currentId].normal[i]=listassist.at(2).toFloat();
                    }
                }else{
                    //loadError();
                }
                break;
            case 'p':
                if(list.size()==6){
                    currentId = qHash(list.at(1));
                    object[currentObject].pivot[currentId] = ModelPivot();
                    object[currentObject].pivot[currentId].id = currentId;
                    object[currentObject].pivot[currentId].name = list.at(1);
                    object[currentObject].pivot[currentId].x = list.at(2).toFloat();
                    object[currentObject].pivot[currentId].y = list.at(3).toFloat();
                    object[currentObject].pivot[currentId].z = list.at(4).toFloat();
                    object[currentObject].pivot[currentId].at = list.at(5).toFloat();
                }else{
                    //loadError();
                }
                break;
            default:
                //loadError();
                break;
            }
            line = in.readLine();
        }
        file.close();
    }
}

void Model::save(QString filename){
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out << "s " << name << "\r\n";
        /*foreach(ModelAnimation a,this->animation){

        }*/
        foreach(Material m,this->material){
            out << "m "<< m.id;
            out << " " << m.emission[0] << " " << m.emission[1] << " " << m.emission[2] << " " << m.emission[3];
            out << " " << m.diffuse[0] << " " << m.diffuse[1] << " " << m.diffuse[2] << " " << m.diffuse[3];
            out << " " << m.specular[0] << " " << m.specular[1] << " " << m.specular[2] << " " << m.specular[3];
            out << " " << m.shininess[0] << "\r\n";
        }
        /*foreach(int k,this->keyframe){

        }*/
        foreach(ModelObject o, this->object){
            out << "o " << o.name << " " << o.material << " " << o.textureFileName << "\r\n";
            foreach(ModelVertex v, o.vertex){
                out << "v " << v.id << " "<< v.x << " " << v.y << " " << v.z << "\r\n";
            }
            foreach(ModelNormal n, o.normal){
                out << "n " << n.id << " "<< n.at << "\r\n";
            }
            foreach(ModelTexCoord t, o.texcoord){
                out << "t " << t.id << " " << t.u << " " << t.v << "\r\n";
            }
            foreach(ModelFace f, o.face){
                out << "f " << f.id ;
                for(int i=0;i<3;i++){
                    out << " " << f.vertex[i] << "/" << f.texcoord[i] << "/" << f.normal[i];
                }
                out << "\r\n";
            }
            foreach(ModelPivot p, o.pivot){
                out << "p " << p.name << " " << p.x << " " << p.y << " " << p.z << " " << p.at << "\r\n";
            }
        }
        file.close();
    }
}

/*
  Edit Methods
 */


/* Object Control */
bool Model::addObject(){
    int i=0;
    while(object.contains(qHash(QString("New Object ").append(QString::number(i))))){
        i++;
    }
    QString oname = QString("New Object ").append(QString::number(i));
    currentObjectId = qHash(oname);
    object[currentObjectId] = ModelObject();
    object[currentObjectId].name = oname;
    return true;
}

bool Model::removeObject(){
    if(currentObjectId!=nullStringHash){
        object.remove(currentObjectId);
        return true;
    }
    return false;
}

/* Material Control */

bool Model::addMaterial(){
    if(currentObjectId!=nullStringHash){
        maxMaterialId++;
        material[maxMaterialId] = Material();
        material[maxMaterialId].id = maxMaterialId;
        return true;
    }
    return false;
}

bool Model::removeMaterial(){
    if(currentObjectId!=nullStringHash and currentMaterialId!=-1){
        material.remove(currentMaterialId);
        return true;
    }
    return false;
}

/* Face Control */

bool Model::addFace()
{
    if(currentObjectId!=nullStringHash){
        maxFaceId++;
        currentObject()->face[maxFaceId] = ModelFace();
        currentObject()->face[maxFaceId].id = maxFaceId;
        return true;
    }
    return false;
}

bool Model::removeFace(){
    if(currentObjectId!=nullStringHash and currentFaceId !=-1){
        currentObject()->face.remove(currentFaceId);
        currentFaceId = -1;
        return true;
    }
    return false;
}

/* Vertex Control */

bool Model::addVertex()
{
    if(currentObjectId!=nullStringHash){
        maxVertexId++;
        currentObject()->vertex[maxVertexId] = ModelVertex();
        currentObject()->vertex[maxVertexId].id = maxVertexId;
        return true;
    }
    return false;
}

bool Model::removeVertex(){
    if(currentObjectId!=nullStringHash and currentVertexId !=-1){
        currentObject()->vertex.remove(currentVertexId);
        return true;
    }
    return false;
}

/* Normal Control */
bool Model::addNormal(){
    if(currentObjectId!=nullStringHash){
        maxNormalId++;
        currentObject()->normal[maxNormalId] = ModelNormal();
        currentObject()->normal[maxNormalId].id = maxNormalId;
        return true;
    }
    return false;
}

bool Model::removeNormal(){
    if(currentObjectId!=nullStringHash and currentNormalId!=-1){
        currentObject()->normal.remove(currentNormalId);
        return true;
    }
    return false;
}

/* Texture Control */
bool Model::addTexture(){
    if(currentObjectId!=nullStringHash){
        maxTextureId++;
        currentObject()->texcoord[maxTextureId] = ModelTexCoord();
        currentObject()->texcoord[maxTextureId].id = maxTextureId;
        return true;
    }
    return false;
}

bool Model::removeTexture(){
    if(currentObjectId!=nullStringHash){
        currentObject()->texcoord.remove(currentTextureId);
        return true;
    }
    return false;
}

/* Pivot Control */
bool Model::addPivot(){
    if(currentObjectId!=nullStringHash){
        maxPivotId++;
        cout << maxPivotId << endl;
        currentObject()->pivot[maxPivotId] = ModelPivot();
        currentObject()->pivot[maxPivotId].id = maxPivotId;
        currentObject()->pivot[maxPivotId].name = QString("pivot").append(QString::number(maxPivotId));
        return true;
    }
    return false;
}

bool Model::removePivot(){
    if(currentObjectId!=nullStringHash and currentPivotId!=-1){
        currentObject()->pivot.remove(currentPivotId);
        return true;
    }
    return false;
}
