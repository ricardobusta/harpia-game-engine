#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QFileDialog>

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

    //glwidget->model.load("testfile.txt");
    //updateLists();

    //Connects

    connect(ui->editTabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));

    connect(ui->objectAdd,SIGNAL(clicked()),this,SLOT(objectAddClicked()));
    connect(ui->materialAdd,SIGNAL(clicked()),this,SLOT(materialAddClicked()));
    connect(ui->faceAdd,SIGNAL(clicked()),this,SLOT(faceAddClicked()));
    connect(ui->vertexAdd,SIGNAL(clicked()),this,SLOT(vertexAddClicked()));

    connect(ui->objectRemove,SIGNAL(clicked()),this,SLOT(objectRemoveClicked()));
    connect(ui->materialRemove,SIGNAL(clicked()),this,SLOT(materialRemoveClicked()));
    connect(ui->faceRemove,SIGNAL(clicked()),this,SLOT(faceRemoveClicked()));
    connect(ui->vertexRemove,SIGNAL(clicked()),this,SLOT(vertexRemoveClicked()));

    connect(ui->faceList,SIGNAL(currentTextChanged(QString)),this,SLOT(faceSelected(QString)));

    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(load()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));

    connect(ui->splitter,SIGNAL(splitterMoved(int,int)),glwidget,SLOT(hide()));

    this->showMaximized();
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
    ui->materialList->clear();
    ui->vertexList->clear();
    ui->normalList->clear();
    ui->texList->clear();
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

/* Geral Control */

void MainWindow::tabChanged(int t){
    currentTab = t;
}

void MainWindow::newModel(){
    glwidget->model.clear();
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"),
                                                    filename,
                                                    tr("Text Files (*.txt)"));
    if (!fileName.isEmpty()){
        filename = fileName;

        glwidget->model.save(filename);
    }
}

void MainWindow::load()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    filename,
                                                    tr("Text Files (*.txt)"));
    if (!fileName.isEmpty())
    {
        filename = fileName;

        glwidget->model.clear();
        glwidget->model.load(filename);

        updateLists();
    }
}

/* Object Control */
void MainWindow::objectAddClicked(){
    glwidget->model.addObject();
    updateLists();
}

void MainWindow::objectRemoveClicked(){
    glwidget->model.removeObject();
    updateLists();
}

void MainWindow::objectSelected(){

}

/* Material Control */
void MainWindow::materialAddClicked(){
    glwidget->model.addMaterial();
    updateLists();
}

void MainWindow::materialRemoveClicked(){
    glwidget->model.removeMaterial();
    updateLists();
}

void MainWindow::materialSelected(){

}

/* Face Control */

void MainWindow::faceAddClicked(){
    glwidget->model.addFace();
    updateLists();
}

void MainWindow::faceRemoveClicked(){
    glwidget->model.removeFace();
    updateLists();
}

void MainWindow::faceSelected(QString v){
    glwidget->model.currentFaceId = v.toInt();
}

/* Vertex Control */

void MainWindow::vertexAddClicked(){
    glwidget->model.addVertex();
    updateLists();
}

void MainWindow::vertexRemoveClicked(){
    glwidget->model.removeVertex();
    updateLists();
}

void MainWindow::vertexSelected(){

}
