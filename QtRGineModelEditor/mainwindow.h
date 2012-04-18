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


    //General Control Functions
    void save();
    void load();
    void newModel();

    void modelSelect(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    //Object Control Functions
    void objectAddClicked();
    void objectRemoveClicked();
    void objectNameChanged();
    void objectTextureChanged();

    //Material Control Functions
    void materialAddClicked();
    void materialRemoveClicked();
    void materialSetType();
    void materialSlider1Changed();
    void materialSlider2Changed();
    void materialSlider3Changed();
    void materialSlider4Changed();

    //Face Control Functions
    void faceAddClicked();
    void faceRemoveClicked();
    void faceVertexChanged();
    void faceNormalChanged();
    void faceTextureChanged();
    void faceVNumberChanged();

    //Vertex Control Functions
    void vertexAddClicked();
    void vertexRemoveClicked();
    void vertexXChanged(double v);
    void vertexYChanged(double v);
    void vertexZChanged(double v);

    //Texture Control Functions
    void textureAddClicked();
    void textureRemoveClicked();
    void textureUChanged(double v);
    void textureVChanged(double v);

    //Normal Control Functions
    void normalAddClicked();
    void normalRemoveClicked();
    void normalATChanged();
};

#endif // MAINWINDOW_H
