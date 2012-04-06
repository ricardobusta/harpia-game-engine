#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

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
    QTreeWidgetItem *modelitem,*objitem,*faceitem,*vertexitem;

    QTimer *timer = new QTimer();

    connect(timer,SIGNAL(timeout()),glwidget,SLOT(update()));
    timer->start(10);
/*
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
*/

    ui->objectstructure->addTopLevelItem(modelitem = new QTreeWidgetItem(0));
    modelitem->setText(0,glwidget->model.name);
    modelitem->setText(1,"M");
    modelitem->setText(2,"yes");
    int totfacecount = 0;
    int totvertcount =0;
    for(int i=0;i<glwidget->model.object.size();i++){
        modelitem->addChild(objitem = new QTreeWidgetItem(0));
        objitem->setText(0,glwidget->model.object[i].name);
        objitem->setText(1,"O");
        objitem->setText(2,"yes");
        int vertcount = 0;
        for(int j=0;j<glwidget->model.object[i].vertex.size();j++){
            if(vertcount==0){
                objitem->addChild(faceitem = new QTreeWidgetItem(0));
                faceitem->setText(0,QString("face").append(QString::number(totfacecount++)));
                faceitem->setText(1,"F");
                faceitem->setText(2,"yes");
            }
            faceitem->addChild(vertexitem = new QTreeWidgetItem(0));
            vertexitem->setText(0,QString("vertex").append(QString::number(totvertcount++)));
            vertexitem->setText(1,"V");
            vertexitem->setText(2,"yes");
            vertcount++;
            vertcount = vertcount%3;
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *){
    glwidget->resize(ui->glframe->size());
}

/*    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Confirma"),
                                    tr("Tem certeza que deseja deletar?"),
                                    QMessageBox::Yes | QMessageBox::No );
    if (reply == QMessageBox::Yes){*/

/*    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Abrir Projeto com Octrees"),
                                filename,
                                tr("All Files (*);;Text Files (*.txt)"));
    if (!fileName.isEmpty())
    {
        filename = fileName;
        getData( filename );
    }*/

/*
   QString fileName = QFileDialog::getSaveFileName(this,
                                tr("Salvar Projeto com Octrees"),
                                filename,
                                tr("All Files (*);;Text Files (*.txt)"));
   if (!fileName.isEmpty()){
       filename = fileName;
       putData( filename );
   }
*/
