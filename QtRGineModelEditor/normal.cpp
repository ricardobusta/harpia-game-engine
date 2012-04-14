#include "normal.h"

#include <qmath.h>

float Normal::normal[181][360][3];
Normal::_init Normal::_normal_initializer;

Normal::_init::_init(){
    for(int a=0;a<181;a++){
        float ra = (M_PI/180.0)*(a-90);
        for(int t=0;t<360;t++){
            float rt = (M_PI/180.0)*(t);
            Normal::normal[a][t][0] = (float)qCos(ra)*qCos(rt);
            Normal::normal[a][t][1] = (float)qSin(ra);
            Normal::normal[a][t][2] = (float)qCos(ra)*qSin(rt);
        }
    }
}
