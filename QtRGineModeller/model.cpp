#include "model.h"

#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <iostream>
using namespace std;

Model::Model()
{
}

void Model::load(QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        QString line = in.readLine();
        int vcont = 0;
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

                object.append(Object());
                object.last().name = list.at(1);
                break;
            case 'v':
                list = line.split(' ');
                vcont++;
                object.last().vertex.append(Vertex());
                object.last().vertex.last().x = list.at(1).toFloat();
                object.last().vertex.last().y = list.at(2).toFloat();
                object.last().vertex.last().z = list.at(3).toFloat();
                break;
            default:
                break;
            }
            line = in.readLine();
        }
    }else{ cout << "fail!" << endl; }
}
