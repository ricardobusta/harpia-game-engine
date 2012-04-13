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
    //GLWidget

    //General Control Functions
    void tabChanged(int t);
    void save();
    void load();
    void newModel();

    //Object Control Functions
    void objectAddClicked();
    void objectRemoveClicked();
    void objectSelected();

    //Material Control Functions
    void materialAddClicked();
    void materialRemoveClicked();
    void materialSelected();

    //Face Control Functions
    void faceAddClicked();
    void faceRemoveClicked();
    void faceSelected(QString);

    //Vertex Control Functions
    void vertexAddClicked();
    void vertexRemoveClicked();
    void vertexSelected();
};

#endif // MAINWINDOW_H
