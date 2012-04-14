#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

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
    void updateLists();

    QString filename;

    Model *currentmodel;

    /* Control Variables */
    QString previousObject;
private slots:
    //GLWidget
    void normalChanged();

    //General Control Functions
    void save();
    void load();
    void newModel();

    void modelSelect(QTreeWidgetItem *current, QTreeWidgetItem *previous);

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
    void vertexXChanged(double v);
    void vertexYChanged(double v);
    void vertexZChanged(double v);
};

#endif // MAINWINDOW_H
