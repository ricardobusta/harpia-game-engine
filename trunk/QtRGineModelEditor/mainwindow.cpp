#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    glwidget = new GLWidget(ui->glframe);

    QTimer *timer = new QTimer();

    connect(timer,SIGNAL(timeout()),glwidget,SLOT(update()));
    timer->start(10);

    glwidget->model.load("testfile.txt");
    updateLists();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *){
    glwidget->resize(ui->glframe->size());
}

void MainWindow::updateLists(){
    ui->objectList->clear();
    ui->faceList->clear();
    foreach(ModelObject o, glwidget->model.object){
        ui->objectList->addItem( new QListWidgetItem(o.name) );
        foreach(ModelFace f, o.face){
            ui->faceList->addItem( new QListWidgetItem( QString::number(f.id) ) );
        }
        foreach(ModelVertex v, o.vertex){
            ui->vertexList->addItem( new QListWidgetItem( QString::number(v.id) ) );
        }
        foreach(ModelNormal n, o.normal){
            ui->normalList->addItem( new QListWidgetItem( QString::number(n.id) ) );
        }
        foreach(ModelTexCoord t, o.texcoord){
            ui->texList->addItem( new QListWidgetItem( QString::number(t.id) ) );
        }
    }
}
