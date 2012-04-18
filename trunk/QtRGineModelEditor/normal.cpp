#include "normal.h"

#include <qmath.h>

/* 181*360 = 65160 */
double Normal::normal[NORMAL_SIZE][3] =
        #include "normals.txt"
;

Normal::_init Normal::_normal_initializer;

#include <QFile>
#include <QTextStream>

Normal::_init::_init(){
    /*QFile file("normal.txt");
    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out << "normal[][3] = {\r\n";*/
/*

        for(int a=0;a<181;a++){
            float ra = (M_PI/180.0)*(a-90);
            for(int t=0;t<360;t++){
                float rt = (M_PI/180.0)*(t);
                int i = a*360+t;
                Normal::normal[i][0] = (double)(qCos(ra)*qCos(rt));
                Normal::normal[i][1] = (double)(qSin(ra));
                Normal::normal[i][2] = (double)(qCos(ra)*qSin(rt));

                /*if(qAbs(normal[i][0])<0.0000001)normal[i][0]=0;
                if(qAbs(normal[i][1])<0.0000001)normal[i][1]=0;
                if(qAbs(normal[i][2])<0.0000001)normal[i][2]=0;

                //out << "{" << normal[i][0] << ", " << Normal::normal[i][1] << ", " << Normal::normal[i][2] << "},\r\n";
            }
        }
*/

        //out << "};";
        //file.close();
    //}
}
