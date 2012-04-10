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
                if(list.size()==20){
                    QString id = list.at(1);
                    material[id] = Material();

                    material[id].emission[0] = list.at(2);
                    material[id].emission[1] = list.at(3);
                    material[id].emission[2] = list.at(4);
                    material[id].emission[3] = list.at(5);

                    material[id].diffuse[0] = list.at(6);
                    material[id].diffuse[1] = list.at(7);
                    material[id].diffuse[2] = list.at(8);
                    material[id].diffuse[3] = list.at(9);

                    material[id].specular[0] = list.at(10);
                    material[id].specular[1] = list.at(11);
                    material[id].specular[2] = list.at(12);
                    material[id].specular[3] = list.at(13);

                    material[i].shininess[0] = list.at(14);
                }else{
                    //loadError();
                }
                break;
            case 'o':
                if(list.size()==2){

                }else{
                    //loadError();
                }
                break;
            case 'v':
                if(list.size()==2){

                }else{
                    //loadError();
                }
                break;
            case 'n':
                if(list.size()==2){

                }else{
                    //loadError();
                }
                break;
            case 't':
                if(list.size()==2){

                }else{
                    //loadError();
                }
                break;
            case 'f':
                if(list.size()==2){

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
    }
}
