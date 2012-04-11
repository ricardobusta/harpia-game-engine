#include "model.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>

Model::Model()
{
    keyframeCount = 0;
}

void Model::load(QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        QString line = in.readLine();
        QString currentObject = "";
        int currentVertex = 0;
        int currentNormal = 0;
        int currentTexCoord = 0;
        int currentFace = 0;
        while (!line.isNull()) {
            QStringList list;
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
                    QString id = list.at(1);
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
                    currentObject = list.at(1);
                    object[currentObject] = ModelObject();
                    object[currentObject].texture = list.at(2);
                    object[currentObject].material = list.at(3).toInt();
                }else{
                    //loadError();
                }
                break;
            case 'v':
                if(list.size()==4){
                    object[currentObject].vertex[currentVertex] = ModelVertex();
                    object[currentObject].vertex[currentVertex].x = list.at(1).toFloat();
                    object[currentObject].vertex[currentVertex].y = list.at(2).toFloat();
                    object[currentObject].vertex[currentVertex].z = list.at(3).toFloat();
                    currentVertex ++;
                }else{
                    //loadError();
                }
                break;
            case 'n':
                if(list.size()==4){
                    object[currentObject].normal[currentNormal] = ModelNormal();
                    object[currentObject].normal[currentNormal].x = list.at(1).toFloat();
                    object[currentObject].normal[currentNormal].y = list.at(2).toFloat();
                    object[currentObject].normal[currentNormal].z = list.at(3).toFloat();
                    currentNormal ++;
                }else{
                    //loadError();
                }
                break;
            case 't':
                if(list.size()==4){
                    object[currentObject].texcoord[currentTexCoord] = ModelTexCoord();
                    object[currentObject].texcoord[currentTexCoord].u = list.at(1).toFloat();
                    object[currentObject].texcoord[currentTexCoord].v = list.at(2).toFloat();
                    currentTexCoord ++;
                }else{
                    //loadError();
                }
                break;
            case 'f':
                QStringList faceVertex;
                object[currentObject].face[currentFace] = ModelFace();
                if(list.size()==4){
                    faceVertex = list.at(1).split("/");
                    object[currentObject].face[currentFace].vertex[0]=faceVertex.at(0).toFloat();
                    object[currentObject].face[currentFace].texcoord[0]=faceVertex.at(1).toFloat();
                    object[currentObject].face[currentFace].normal[0]=faceVertex.at(2).toFloat();
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

#define oendl "\r\n"

void Model::save(QString filename){
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out << "s " << name << oendl;
        asdasdasd
        file.close();
    }
}
