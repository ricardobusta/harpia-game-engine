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
    
    void resizeEvent(QResizeEvent *);
private:
    Ui::MainWindow *ui;

    GLWidget *glwidget;
    int currentMode();
    void updateLists();

    int currentTab;

    QString filename;
private slots:
    //General Control Functions
    void tabChanged(int t);
    void save();
    void load();
    void newModel();

    //Object Control Functions
    void objectAddClicked();
    void objectRemoveClicked();

    //Material Control Functions
    void materialAddClicked();
    void materialRemoveClicked();

    //Face Control Functions
    void faceAddClicked();
    void faceRemoveClicked();

    //Vertex Control Functions
    void vertexAddClicked();
    void vertexRemoveClicked();
};

#endif // MAINWINDOW_H
