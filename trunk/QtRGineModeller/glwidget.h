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

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void drawScene();

    Model model;

    int w,h,side;
};

#endif // GLWIDGET_H

