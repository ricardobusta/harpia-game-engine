#include "model.h"

#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QFileDialog>
#include <iostream>
using namespace std;

Model::Model()
{
    facecount = 0;
    vertcount = 0;

    currentObject = "";
    currentFace = "";
    currentVertex = "";
}

void Model::load(QString filename)
{
    QString lastObject,lastFace,lastVertex;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            QStringList list;
            switch(line[0].toAscii()){
            case '#':
                break;
            case 'm':
                list = line.split(' ');
                name = list.at(1);
                break;
            case 'p':
                list = line.split(' ');
                lastObject = list.at(1);
                object[lastObject] = Object();
                object[lastObject].name = lastObject;
                break;
            case 'v':
                list = line.split(' ');
                lastVertex = QString("vertex").append(QString::number(vertcount));
                lastFace = QString("face").append(QString::number(facecount));
                object[lastObject].vertex[lastVertex] = Vertex();
                object[lastObject].vertex[lastVertex].x = list.at(1).toFloat();
                object[lastObject].vertex[lastVertex].y = list.at(2).toFloat();
                object[lastObject].vertex[lastVertex].z = list.at(3).toFloat();
                if(list.size()==9){
                    object[lastObject].vertex[lastVertex].u = list.at(4).toFloat();
                    object[lastObject].vertex[lastVertex].v = list.at(5).toFloat();
                    object[lastObject].vertex[lastVertex].r = list.at(6).toFloat();
                    object[lastObject].vertex[lastVertex].g = list.at(7).toFloat();
                    object[lastObject].vertex[lastVertex].b = list.at(8).toFloat();
                }
                object[lastObject].vertex[lastVertex].name = lastVertex;
                object[lastObject].vertex[lastVertex].facename = lastFace;
                object[lastObject].vertex[lastVertex].objectname = lastObject;
                vertcount++;
                if(vertcount%3==0){
                    facecount++;
                }
                break;
            default:
                break;
            }
            line = in.readLine();
        }
    }else{ cout << "fail!" << endl; }
    file.close();
}

void Model::save(QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out << "m " << name << "\r\n";

        foreach(Object obj, object){
            out << "p " << obj.name << "\r\n";
            foreach(Vertex ver, obj.vertex){
                out << "v " << ver.x << " " << ver.y << " " << ver.z;
                out << " " << ver.u << " " << ver.v;
                out << " " << ver.r << " " << ver.g << " " << ver.b << "\r\n";
            }
        }
    }
    file.close();
}

void Model::clear(){
    foreach(Object obj, object){
        obj.vertex.clear();
    }
    object.clear();
    facecount = 0;
    vertcount = 0;
}
