#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    GLWidget *glwidget;

    void resizeEvent(QResizeEvent *);

    QString filename;

public slots:
    void buildTree();

    void loadFile();
    void saveFile();

    void addFace();
    void removeFace();

    void addObject();
    void removeObject();

    void selectVertex();

    void changeX(double val);
    void changeY(double val);
    void changeZ(double val);
};

#endif // MAINWINDOW_H
