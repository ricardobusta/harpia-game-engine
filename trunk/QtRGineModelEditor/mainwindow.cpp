#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("RGine Model Editor v0.0 - By Ricardo Bustamante");

    glwidget = new GLWidget(ui->glframe);

    //Update Opengl Timer
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),glwidget,SLOT(update()));
    timer->start(10);

    glwidget->model.load("testfile.txt");
    updateLists();

    //Connects

    connect(ui->editTabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));
    connect(ui->face_Add,SIGNAL(clicked()),this,SLOT(faceAddClicked()));
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
    foreach(Material m, glwidget->model.material){
        ui->materialList->addItem( new QListWidgetItem( QString::number(m.id) ) );
    }
}

#include <iostream>
using namespace std;
void MainWindow::tabChanged(int t){
    currentTab = t;
}

void MainWindow::faceAddClicked(){
    glwidget->model.currentObject = "oname";

    glwidget->model.addFace();
    updateLists();
}
