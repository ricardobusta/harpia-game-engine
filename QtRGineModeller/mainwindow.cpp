#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("RGine Modeller");

    glwidget = new GLWidget(ui->glframe);
    glwidget->resize(ui->glframe->size());

    //ui->objectstructure->setColumnCount(3);
    //ui->objectstructure->;
    QTreeWidgetItem *objitem,*faceitem,*vertexitem;

    ui->objectstructure->addTopLevelItem(objitem = new QTreeWidgetItem(0));
    objitem->setText(1,"O");
    objitem->setText(0,"body");
    objitem->setText(2,"yes");
    objitem->addChild(faceitem = new QTreeWidgetItem(0));
        faceitem->setText(1,"F");
        faceitem->setText(0,"face1");
        faceitem->setText(2,"yes");
        faceitem->addChild(vertexitem = new QTreeWidgetItem(0));
            vertexitem->setText(1,"V");
            vertexitem->setText(0,"vert0");
            vertexitem->setText(2,"yes");
        faceitem->addChild(vertexitem = new QTreeWidgetItem(0));
            vertexitem->setText(1,"V");
            vertexitem->setText(0,"vert1");
            vertexitem->setText(2,"yes");
        faceitem->addChild(vertexitem = new QTreeWidgetItem(0));
            vertexitem->setText(1,"V");
            vertexitem->setText(0,"vert2");
            vertexitem->setText(2,"yes");
    objitem->addChild(faceitem = new QTreeWidgetItem(0));
        faceitem->setText(1,"F");
        faceitem->setText(0,"face2");
        faceitem->setText(2,"yes");
    ui->objectstructure->addTopLevelItem(objitem = new QTreeWidgetItem(0));
    objitem->setText(1,"O");
    objitem->setText(0,"head");
    objitem->setText(2,"yes");


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *){
    glwidget->resize(ui->glframe->size());
}
