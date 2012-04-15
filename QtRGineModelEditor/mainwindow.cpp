#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QFileDialog>

//just for debugging
#define TRACE(x) ui->statusBar->showMessage(x)

#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Interface Options */
    this->setWindowTitle("RGine Model Editor v0.0 - By Ricardo Bustamante");
    glwidget = new GLWidget(ui->glframe);
    ui->modelEditWidgets->setCurrentWidget(ui->emptyPage);

    currentmodel = &glwidget->model;

    currentmodel->load("assets/testfile.txt");

    updateLists();
    this->showMaximized();

    /* Update Opengl Timer */
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),glwidget,SLOT(update()));
    timer->start(10);

    /* Control Variables */
    filename = "assets";

    /* Connects */

    /* object */
    connect(ui->objectAdd,SIGNAL(clicked()),this,SLOT(objectAddClicked()));
    connect(ui->objectRemove,SIGNAL(clicked()),this,SLOT(objectRemoveClicked()));
    connect(ui->objectName,SIGNAL(editingFinished()),this,SLOT(objectNameChanged()));
    connect(ui->objectTexture,SIGNAL(editingFinished()),this,SLOT(objectTextureChanged()));

    /* material */
    connect(ui->materialAdd,SIGNAL(clicked()),this,SLOT(materialAddClicked()));
    connect(ui->materialRemove,SIGNAL(clicked()),this,SLOT(materialRemoveClicked()));
    connect(ui->materialType,SIGNAL(currentIndexChanged(QString)),this,SLOT(materialSetType()));
    connect(ui->materialRed,SIGNAL(valueChanged(int)),this,SLOT(materialSlider1Changed()));
    connect(ui->materialGreen,SIGNAL(valueChanged(int)),this,SLOT(materialSlider2Changed()));
    connect(ui->materialBlue,SIGNAL(valueChanged(int)),this,SLOT(materialSlider3Changed()));
    connect(ui->materialAlpha,SIGNAL(valueChanged(int)),this,SLOT(materialSlider4Changed()));

    /* face */
    connect(ui->faceAdd,SIGNAL(clicked()),this,SLOT(faceAddClicked()));
    connect(ui->faceRemove,SIGNAL(clicked()),this,SLOT(faceRemoveClicked()));
    connect(ui->faceVertex1,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceVertex1Changed()));
    connect(ui->faceVertex2,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceVertex2Changed()));
    connect(ui->faceVertex3,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceVertex3Changed()));
    connect(ui->faceNormal1,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceNormal1Changed()));
    connect(ui->faceNormal2,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceNormal2Changed()));
    connect(ui->faceNormal3,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceNormal3Changed()));
    connect(ui->faceTexture1,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceTexture1Changed()));
    connect(ui->faceTexture2,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceTexture2Changed()));
    connect(ui->faceTexture3,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceTexture3Changed()));

    /* vertex */
    connect(ui->vertexAdd,SIGNAL(clicked()),this,SLOT(vertexAddClicked()));
    connect(ui->vertexRemove,SIGNAL(clicked()),this,SLOT(vertexRemoveClicked()));
    connect(ui->vertexX,SIGNAL(valueChanged(double)),this,SLOT(vertexXChanged(double)));
    connect(ui->vertexY,SIGNAL(valueChanged(double)),this,SLOT(vertexYChanged(double)));
    connect(ui->vertexZ,SIGNAL(valueChanged(double)),this,SLOT(vertexZChanged(double)));

    /* model */
    connect(ui->modelList,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),this,SLOT(modelSelect(QTreeWidgetItem*,QTreeWidgetItem*)));

    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(load()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newModel()));

    connect(ui->normalAlpha,SIGNAL(valueChanged(int)),this,SLOT(normalAChanged()));
    connect(ui->normalTheta,SIGNAL(valueChanged(int)),this,SLOT(normalTChanged()));

    TRACE("asd");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *){
    glwidget->resize(ui->glframe->size());
}

void MainWindow::updateLists(){
    //Clear current tree
    ui->modelList->clear();

    //Every level of widget items
    QTreeWidgetItem *firstitem, *seconditemtype,*seconditem, *thirditemtype, *thirditem;

    //Tree Root is a model. Might have more models if more than one is loaded in the future.
    ui->modelList->addTopLevelItem(firstitem = new QTreeWidgetItem(0));
    firstitem->setText(0,"Model");

    //Add material type node
    firstitem->addChild(seconditemtype = new QTreeWidgetItem(0));
    seconditemtype->setText(0,"Material");

    //Add materials
    foreach(Material m, currentmodel->material){
        seconditemtype->addChild(seconditem = new QTreeWidgetItem(0));
        seconditem->setText(0,QString::number(m.id));
    }

    //Add object type node
    firstitem->addChild(seconditemtype = new QTreeWidgetItem(0));
    seconditemtype->setText(0,"Object");

    //Add objects
    foreach(ModelObject o, currentmodel->object){
        seconditemtype->addChild(seconditem = new QTreeWidgetItem(0));
        seconditem->setText(0,o.name);

        //Add face type node
        seconditem->addChild(thirditemtype = new QTreeWidgetItem(0));
        thirditemtype->setText(0,"Face");

        //Add faces
        foreach(ModelFace f, o.face){
            thirditemtype->addChild(thirditem = new QTreeWidgetItem(0));
            thirditem->setText(0,QString::number(f.id));
            // ui->faceList->addItem( new QListWidgetItem( QString::number(f.id) ) );
        }

        //Add vertex type node
        seconditem->addChild(thirditemtype = new QTreeWidgetItem(0));
        thirditemtype->setText(0,"Vertex");

        //Add vertexes
        foreach(ModelVertex v, o.vertex){
            thirditemtype->addChild(thirditem = new QTreeWidgetItem(0));
            thirditem->setText(0,QString::number(v.id));
            //ui->vertexList->addItem( new QListWidgetItem( QString::number(v.id) ) );
        }

        //Add normal type node
        seconditem->addChild(thirditemtype = new QTreeWidgetItem(0));
        thirditemtype->setText(0,"Normal");

        //Add normals
        foreach(ModelNormal n, o.normal){
            thirditemtype->addChild(thirditem = new QTreeWidgetItem(0));
            thirditem->setText(0,QString::number(n.id));
            //ui->normalList->addItem( new QListWidgetItem( QString::number(n.id) ) );
        }

        //Add texture coordinates type node
        seconditem->addChild(thirditemtype = new QTreeWidgetItem(0));
        thirditemtype->setText(0,"Texture");

        //Add texture coordinates
        foreach(ModelTexCoord t, o.texcoord){
            thirditemtype->addChild(thirditem = new QTreeWidgetItem(0));
            thirditem->setText(0,QString::number(t.id));
            //ui->texList->addItem( new QListWidgetItem( QString::number(t.id) ) );
        }
    }

    ui->modelList->expandAll();
}

/* Geral Control */

void MainWindow::newModel(){
    currentmodel->clear();
    updateLists();
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"),
                                                    filename,
                                                    tr("Text Files (*.txt)"));
    if (!fileName.isEmpty()){
        filename = fileName;

        currentmodel->save(filename);
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

        currentmodel->clear();
        currentmodel->load(filename);

        updateLists();
    }
}

/* Model Control */
void MainWindow::modelSelect(QTreeWidgetItem* current,QTreeWidgetItem* previous){
    if(current!=NULL and current->parent()!=NULL){
        currentmodel->current_mode = CURRENT_NONE;
        ui->modelEditWidgets->setCurrentWidget(ui->emptyPage);
        if(current->parent()->text(0)=="Model"){
            currentmodel->current_mode = CURRENT_MODEL;
            ui->modelEditWidgets->setCurrentWidget(ui->emptyPage);
        }
        if(current->parent()->text(0)=="Object"){
            currentmodel->current_mode = CURRENT_OBJECT;
            ui->modelEditWidgets->setCurrentWidget(ui->objectPage);
            ui->objectName->setText(current->text(0));
            ui->objectTexture->setText(currentmodel->object[current->text(0)].texture);
        }
        if(current->parent()->text(0)=="Material"){
            currentmodel->current_mode = CURRENT_MATERIAL;
            ui->modelEditWidgets->setCurrentWidget(ui->materialPage);
            currentmodel->currentMaterialId = current->text(0).toInt();
        }
        if(current->parent()->text(0)=="Vertex"){
            currentmodel->current_mode = CURRENT_VERTEX;
            ui->modelEditWidgets->setCurrentWidget(ui->vertexPage);
            currentmodel->currentObjectId = current->parent()->parent()->text(0);
            currentmodel->currentVertexId = current->text(0).toInt();
            if(currentmodel->currentVertex()!=NULL){
                ui->vertexX->setValue(currentmodel->currentVertex()->x);
                ui->vertexY->setValue(currentmodel->currentVertex()->y);
                ui->vertexZ->setValue(currentmodel->currentVertex()->z);
            }
        }
        if(current->parent()->text(0)=="Face"){
            currentmodel->current_mode = CURRENT_FACE;
            ui->modelEditWidgets->setCurrentWidget(ui->facePage);
            if(previousObject!=current->parent()->parent()->text(0)){

            }
        }
        if(current->parent()->text(0)=="Normal"){
            currentmodel->current_mode = CURRENT_NORMAL;
            ui->modelEditWidgets->setCurrentWidget(ui->normalPage);
            currentmodel->currentObjectId = current->parent()->parent()->text(0);
            currentmodel->currentNormalId = current->text(0).toInt();
            ui->normalAlpha->setValue(currentmodel->currentNormal()->a);
            ui->normalTheta->setValue((currentmodel->currentNormal()->t-90)%360);
        }
        if(current->parent()->text(0)=="Texture"){
            currentmodel->current_mode = CURRENT_TEXTURE;
            ui->modelEditWidgets->setCurrentWidget(ui->texturePage);
        }
    }
}

/* Object Control */
void MainWindow::objectAddClicked(){
    currentmodel->objectAdd();
    updateLists();
}

void MainWindow::objectRemoveClicked(){
    currentmodel->removeObject();
    updateLists();
}

/* Material Control */
void MainWindow::materialAddClicked(){
    currentmodel->materialAdd();
    updateLists();
}

void MainWindow::materialRemoveClicked(){
    currentmodel->removeMaterial();
    updateLists();
}

/* Face Control */

void MainWindow::faceAddClicked(){
    currentmodel->faceAdd();
    updateLists();
}

void MainWindow::faceRemoveClicked(){
    currentmodel->removeFace();
    updateLists();
}

/* Vertex Control */

void MainWindow::vertexAddClicked(){
    currentmodel->addVertex();
    updateLists();
}

void MainWindow::vertexRemoveClicked(){
    currentmodel->removeVertex();
    updateLists();
}

void MainWindow::vertexXChanged(double v){
    currentmodel->changeVertexX(v);
}

void MainWindow::vertexYChanged(double v){
    currentmodel->changeVertexY(v);
}

void MainWindow::vertexZChanged(double v){
    currentmodel->changeVertexZ(v);
}

/* NormalControl */

void MainWindow::normalAChanged(){
    if(currentmodel->currentNormal()!=NULL){
        currentmodel->currentNormal()->a = (180-qAbs(ui->normalAlpha->value()-180));
    }
}

void MainWindow::normalTChanged(){
    if(currentmodel->currentNormal()!=NULL){
        currentmodel->currentNormal()->t = ((90+ui->normalTheta->value())%360);
    }
}
