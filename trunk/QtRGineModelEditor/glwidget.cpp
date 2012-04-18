#include "glwidget.h"
#include "material.h"

#include <QMouseEvent>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    xRot = yRot = zRot = 0;
    zdist = 500;

    drawAxisEnabled = false;
}

GLWidget::~GLWidget()
{
}

void GLWidget::mousePressEvent(QMouseEvent * event){
    lastpos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent * event){
    int speedx = event->pos().x() - lastpos.x();
    int speedy = event->pos().y() - lastpos.y();

    //if(event->button() & Qt::RightButton){
    xRot += speedy;
    yRot += speedx;
    //}

    lastpos = event->pos();
}

void GLWidget::initializeGL(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    float lspecular[] = {0.3,0.3,0.3,1.0};
    float lambient[] = {0.5,0.5,0.5,1.0};
    float ldiffuse[] = {0.5,0.5,0.5,1.0};
    float lposition[] = {0,0,1,1.0};

    glLightfv(GL_LIGHT0, GL_SPECULAR, lspecular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ldiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lposition);

    Material mat;
    mat.set(MAT_WHITE);
    mat.gl();

    //glColor3f(1,0,0);

    //glDisable(GL_LIGHTING);
    /* Texture Test */
    /*
    QImage texture;
    texture.load("assets/image.bmp");

    QImage *tex1 = new QImage( QGLWidget::convertToGLFormat(texture) );

    GLuint *texid = new GLuint;
    glEnable(GL_TEXTURE_2D);
    glGenTextures( 1, texid );
    glBindTexture( GL_TEXTURE_2D, *texid );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tex1->width(), tex1->height(), 0, GL_RGBA,GL_UNSIGNED_BYTE, tex1->bits());*/
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,0,-zdist);
    glRotated(xRot, 1.0, 0.0, 0.0);
    glRotated(yRot, 0.0, 1.0, 0.0);
    glRotated(zRot, 0.0, 0.0, 1.0);

    glViewport((w - side) / 2, (h - side) / 2, side, side);
    drawScene();
}

void GLWidget::resizeGL(int w, int h){
    side = qMax(w, h);
    this->w = w;
    this->h = h;
    //glViewport((w - side) / 2, (h - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //int zoom = 1;
    //glOrtho(-500,500,-500,500,-1000,1000);
    glFrustum(-1,1,-1,1,1,1000);
    glMatrixMode(GL_MODELVIEW);
}

#include <iostream>
using namespace std;

void GLWidget::drawAxis(){
    if(drawAxisEnabled){
        glBegin(GL_LINES);
        //x
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(30,0,0);
        //y
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,30,0);
        //z
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,30);
    }

    //normal
    glColor3f(1,1,1);
    glVertex3f(0,0,0);
    if(model.current_mode == CURRENT_NORMAL){
        glVertex3f( Normal::x(model.object[model.currentObjectId].normal[model.currentNormalId].at)*110
                    ,Normal::y(model.object[model.currentObjectId].normal[model.currentNormalId].at)*110
                    ,Normal::z(model.object[model.currentObjectId].normal[model.currentNormalId].at)*110
                    );
    }
    glEnd();
}

void GLWidget::drawCurrentFace(){
    if(model.currentFace()!=NULL){
        glColor3f(1,1,1);
        ModelVertex *v0 = &model.object[model.currentObjectId].vertex[model.currentFace()->vertex[0]];
        ModelVertex *v1 = &model.object[model.currentObjectId].vertex[model.currentFace()->vertex[1]];
        ModelVertex *v2 = &model.object[model.currentObjectId].vertex[model.currentFace()->vertex[2]];
        glBegin(GL_LINE_LOOP);
        glVertex3f(v0->x,v0->y,v0->z);
        glVertex3f(v1->x,v1->y,v1->z);
        glVertex3f(v2->x,v2->y,v2->z);
        glEnd();
    }
}

void GLWidget::drawCurrentVertex(){
    if(model.currentVertex()!=NULL){
        float scale=4;
        float x = model.currentVertex()->x;
        float y = model.currentVertex()->y;
        float z = model.currentVertex()->z;

        glBegin(GL_QUADS);
        glColor3f(1,1,0);

        glVertex3f(x-scale,y-scale,z+scale);
        glVertex3f(x+scale,y-scale,z+scale);
        glVertex3f(x+scale,y+scale,z+scale);
        glVertex3f(x-scale,y+scale,z+scale);

        glVertex3f(x+scale,y-scale,z+scale);
        glVertex3f(x+scale,y-scale,z-scale);
        glVertex3f(x+scale,y+scale,z-scale);
        glVertex3f(x+scale,y+scale,z+scale);

        glVertex3f(x-scale,y-scale,z-scale);
        glVertex3f(x-scale,y-scale,z+scale);
        glVertex3f(x-scale,y+scale,z+scale);
        glVertex3f(x-scale,y+scale,z-scale);

        glVertex3f(x+scale,y-scale,z-scale);
        glVertex3f(x-scale,y-scale,z-scale);
        glVertex3f(x-scale,y+scale,z-scale);
        glVertex3f(x+scale,y+scale,z-scale);

        glVertex3f(x-scale,y+scale,z+scale);
        glVertex3f(x+scale,y+scale,z+scale);
        glVertex3f(x+scale,y+scale,z-scale);
        glVertex3f(x-scale,y+scale,z-scale);

        glVertex3f(x+scale,y-scale,z-scale);
        glVertex3f(x+scale,y-scale,z+scale);
        glVertex3f(x-scale,y-scale,z+scale);
        glVertex3f(x-scale,y-scale,z-scale);

        glEnd();
    }
}

void GLWidget::drawScene(){
    glLineWidth(2);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    drawAxis();
    drawCurrentFace();
    drawCurrentVertex();
    glLineWidth(1);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    //glColor3f(1,1,1);


    foreach(ModelObject o, model.object){
        model.texture.set(o.texture);
        //model.material[o.material].set(MAT_GRAY_50);
        //model.material[o.material].gl();
        glBegin(GL_TRIANGLES);
        foreach(ModelFace f, o.face){
            for(int i=0;i<3;i++){
                int at=o.normal[f.normal[i]].at;
                glNormal3f(Normal::x(at),Normal::y(at),Normal::z(at));
                //glNormal3f(0,0,1);
                glTexCoord2f(o.texcoord[f.texcoord[i]].u,o.texcoord[f.texcoord[i]].v);
                glVertex3f(o.vertex[f.vertex[i]].x,o.vertex[f.vertex[i]].y,o.vertex[f.vertex[i]].z);
            }
        }
        glEnd();
    }
}

void GLWidget::toggleDrawAxis(bool enable)
{
    drawAxisEnabled = enable;
}

