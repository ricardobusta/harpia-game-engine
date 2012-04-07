#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include "model.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    float xRot,yRot,zRot;
    float zdist;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    int w,h,side;

    void drawScene();
    Model model;

    QPoint lastpos;
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void drawAxis();
    void drawVertex(float x, float y, float z);
    void drawSelectedFace();
};

#endif // GLWIDGET_H

