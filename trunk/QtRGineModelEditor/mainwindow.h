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
private slots:
    //General Control Functions
    void tabChanged(int t);

    //Face Control Functions
    void faceAddClicked();
};

#endif // MAINWINDOW_H
