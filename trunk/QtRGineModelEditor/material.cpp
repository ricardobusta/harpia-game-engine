#include "material.h"

#include <QtOpenGL>

Material::Material()
{
    id=0;
    for(int i=0;i<4;i++){
        specular[i]=0;
        diffuse[i]=1;
        emission[i]=0;
    }
    shininess[0]=1;
}

void Material::set(int color){
    switch(color){
    case MAT_RED:
        diffuse[0] = 1;
        diffuse[1] = 0;
        diffuse[2] = 0;
        diffuse[3] = 1;

        specular[0] = 1;
        specular[1] = 0;
        specular[2] = 0;
        specular[3] = 1;
        break;
    case MAT_GREEN:
        diffuse[0] = 0;
        diffuse[1] = 1;
        diffuse[2] = 0;
        diffuse[3] = 1;

        specular[0] = 0;
        specular[1] = 1;
        specular[2] = 0;
        specular[3] = 1;
        break;
    case MAT_BLUE:
        diffuse[0] = 0;
        diffuse[1] = 0;
        diffuse[2] = 1;
        diffuse[3] = 1;

        specular[0] = 0;
        specular[1] = 0;
        specular[2] = 1;
        specular[3] = 1;
        break;
    case MAT_YELLOW:
        diffuse[0] = 1;
        diffuse[1] = 1;
        diffuse[2] = 0;
        diffuse[3] = 1;

        specular[0] = 1;
        specular[1] = 1;
        specular[2] = 0;
        specular[3] = 1;
        break;
    case MAT_CYAN:
        diffuse[0] = 0;
        diffuse[1] = 1;
        diffuse[2] = 1;
        diffuse[3] = 1;

        specular[0] = 0;
        specular[1] = 1;
        specular[2] = 1;
        specular[3] = 1;
        break;
    case MAT_MAGENTA:
        diffuse[0] = 1;
        diffuse[1] = 0;
        diffuse[2] = 1;
        diffuse[3] = 1;

        specular[0] = 1;
        specular[1] = 0;
        specular[2] = 1;
        specular[3] = 1;
        break;
    case MAT_WHITE:
        diffuse[0] = 1;
        diffuse[1] = 1;
        diffuse[2] = 1;
        diffuse[3] = 1;

        specular[0] = 1;
        specular[1] = 1;
        specular[2] = 1;
        specular[3] = 1;
        break;
    case MAT_GRAY_75:
        diffuse[0] = 0.75;
        diffuse[1] = 0.75;
        diffuse[2] = 0.75;
        diffuse[3] = 1;

        specular[0] = 0.75;
        specular[1] = 0.75;
        specular[2] = 0.75;
        specular[3] = 1;
        break;
    case MAT_GRAY_50:
        diffuse[0] = 0.5;
        diffuse[1] = 0.5;
        diffuse[2] = 0.5;
        diffuse[3] = 1;

        specular[0] = 0.5;
        specular[1] = 0.5;
        specular[2] = 0.5;
        specular[3] = 1;
        break;
    case MAT_GRAY_25:
        diffuse[0] = 0.25;
        diffuse[1] = 0.25;
        diffuse[2] = 0.25;
        diffuse[3] = 1;

        specular[0] = 0.25;
        specular[1] = 0.25;
        specular[2] = 0.25;
        specular[3] = 1;
        break;
    default:
        break;
    }
}

void Material::gl(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}
