#include "normal.h"

#include <qmath.h>

/* 181*360 = 65160 */
float Normal::normal[NORMAL_SIZE][3];
Normal::_init Normal::_normal_initializer;

Normal::_init::_init(){
    for(int a=0;a<181;a++){
        float ra = (M_PI/180.0)*(a-90);
        for(int t=0;t<360;t++){
            float rt = (M_PI/180.0)*(t);
            int i = a*360+t;
            Normal::normal[i][0] = (float)qCos(ra)*qCos(rt);
            Normal::normal[i][1] = (float)qSin(ra);
            Normal::normal[i][2] = (float)qCos(ra)*qSin(rt);
        }
    }
}
