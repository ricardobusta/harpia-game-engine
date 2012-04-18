#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QFileDialog>

//just for debugging
#define TRACE(x) ui->statusBar->showMessage(x)
#define STR(x) QString::number(x)

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
    connect(ui->faceVertex,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceVertexChanged()));
    connect(ui->faceNormal,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceNormalChanged()));
    connect(ui->faceTexture,SIGNAL(currentIndexChanged(QString)),this,SLOT(faceTextureChanged()));
    connect(ui->faceVNumber,SIGNAL(currentIndexChanged(int)),this,SLOT(faceVNumberChanged()));

    /* vertex */
    connect(ui->vertexAdd,SIGNAL(clicked()),this,SLOT(vertexAddClicked()));
    connect(ui->vertexRemove,SIGNAL(clicked()),this,SLOT(vertexRemoveClicked()));
    connect(ui->vertexX,SIGNAL(valueChanged(double)),this,SLOT(vertexXChanged(double)));
    connect(ui->vertexY,SIGNAL(valueChanged(double)),this,SLOT(vertexYChanged(double)));
    connect(ui->vertexZ,SIGNAL(valueChanged(double)),this,SLOT(vertexZChanged(double)));

    /* texture */
    connect(ui->textureU,SIGNAL(valueChanged(double)),this,SLOT(textureUChanged(double)));
    connect(ui->textureV,SIGNAL(valueChanged(double)),this,SLOT(textureVChanged(double)));

    /* model */
    connect(ui->modelList,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),this,SLOT(modelSelect(QTreeWidgetItem*,QTreeWidgetItem*)));

    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(load()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newModel()));

    connect(ui->normalAlpha,SIGNAL(valueChanged(int)),this,SLOT(normalAChanged()));
    connect(ui->normalTheta,SIGNAL(valueChanged(int)),this,SLOT(normalTChanged()));

    /* Interface */

    connect(ui->actionViewAxis,SIGNAL(toggled(bool)),glwidget,SLOT(toggleDrawAxis(bool)));

    /* test */

    currentmodel->load("assets/testfile.txt");
    //    currentmodel->texture.load("assets/image.bmp");
    //    currentmodel->texture.load("assets/image2.bmp");

    /*
    QImage texture;
    texture.load("assets/image.bmp");
    QImage tex2 = QImage(QSize(64,64),QImage::Format_ARGB32);
    for(int i=0;i<64;i++){
        for(int j=0;j<64;j++){
            tex2.setPixel(i,j,texture.pixel(i*(texture.width()/64.0),j*(texture.height()/64.0)));
        }
    }
    ui->textureDisplay->setPixmap(QPixmap::fromImage(tex2));*/

    updateLists();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *){
    glwidget->resize(ui->glframe->size());
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

        currentmodel->load(filename);

        updateLists();
    }
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
        seconditem->setText(0,STR(m.id));
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
            thirditem->setText(0,STR(f.id));
            // ui->faceList->addItem( new QListWidgetItem( STR(f.id) ) );
        }

        //Add vertex type node
        seconditem->addChild(thirditemtype = new QTreeWidgetItem(0));
        thirditemtype->setText(0,"Vertex");

        //Add vertexes
        foreach(ModelVertex v, o.vertex){
            thirditemtype->addChild(thirditem = new QTreeWidgetItem(0));
            thirditem->setText(0,STR(v.id));
            //ui->vertexList->addItem( new QListWidgetItem( STR(v.id) ) );
        }

        //Add normal type node
        seconditem->addChild(thirditemtype = new QTreeWidgetItem(0));
        thirditemtype->setText(0,"Normal");

        //Add normals
        foreach(ModelNormal n, o.normal){
            thirditemtype->addChild(thirditem = new QTreeWidgetItem(0));
            thirditem->setText(0,STR(n.id));
            //ui->normalList->addItem( new QListWidgetItem( STR(n.id) ) );
        }

        //Add texture coordinates type node
        seconditem->addChild(thirditemtype = new QTreeWidgetItem(0));
        thirditemtype->setText(0,"Texture");

        //Add texture coordinates
        foreach(ModelTexCoord t, o.texcoord){
            thirditemtype->addChild(thirditem = new QTreeWidgetItem(0));
            thirditem->setText(0,STR(t.id));
            //ui->texList->addItem( new QListWidgetItem( STR(t.id) ) );
        }

        //Add texture coordinates type node
        seconditem->addChild(thirditemtype = new QTreeWidgetItem(0));
        thirditemtype->setText(0,"Pivot");

        //Add texture coordinates
        foreach(ModelPivot p, o.pivot){
            thirditemtype->addChild(thirditem = new QTreeWidgetItem(0));
            thirditem->setText(0,p.name);
            //ui->texList->addItem( new QListWidgetItem( STR(t.id) ) );
        }
    }

    ui->modelList->expandAll();
}

/* Model Control */

void MainWindow::modelSelect(QTreeWidgetItem* current,QTreeWidgetItem* previous){
    if(current!=NULL and current->parent()!=NULL){
        currentmodel->current_mode = CURRENT_NONE;
        ui->modelEditWidgets->setCurrentWidget(ui->emptyPage);
        if(current->parent()->text(0)=="Model"){
            currentmodel->current_mode = CURRENT_MODEL;
            ui->modelEditWidgets->setCurrentWidget(ui->emptyPage);
        }else if(current->parent()->text(0)=="Object"){
            currentmodel->current_mode = CURRENT_OBJECT;
            ui->modelEditWidgets->setCurrentWidget(ui->objectPage);
            ui->objectName->setText(current->text(0));
            ui->objectTexture->setText(currentmodel->object[qHash(current->text(0))].textureFileName);
        }else if(current->parent()->text(0)=="Material"){
            currentmodel->current_mode = CURRENT_MATERIAL;
            ui->modelEditWidgets->setCurrentWidget(ui->materialPage);
            currentmodel->currentMaterialId = current->text(0).toInt();
        }else if(current->parent()->text(0)=="Vertex"){
            currentmodel->current_mode = CURRENT_VERTEX;
            ui->modelEditWidgets->setCurrentWidget(ui->vertexPage);
            currentmodel->currentObjectId = qHash(current->parent()->parent()->text(0));
            currentmodel->currentVertexId = current->text(0).toInt();
            if(currentmodel->currentVertex()!=NULL){
                ui->vertexX->setValue(currentmodel->currentVertex()->x);
                ui->vertexY->setValue(currentmodel->currentVertex()->y);
                ui->vertexZ->setValue(currentmodel->currentVertex()->z);
            }
        }else if(current->parent()->text(0)=="Face"){
            currentmodel->current_mode = CURRENT_FACE;
            ui->modelEditWidgets->setCurrentWidget(ui->facePage);
            currentmodel->currentObjectId = qHash(current->parent()->parent()->text(0));
            currentmodel->currentFaceId = current->text(0).toInt();

            //unecessary to do always, need optimization
            ui->faceVertex->clear();
            ui->faceNormal->clear();
            ui->faceTexture->clear();

            foreach(ModelVertex v,currentmodel->currentObject()->vertex){
                ui->faceVertex->addItem(STR(v.id));
            }
            foreach(ModelFace f,currentmodel->currentObject()->face){
                ui->faceNormal->addItem(STR(f.id));
            }
            foreach(ModelTexCoord t,currentmodel->currentObject()->texcoord){
                ui->faceTexture->addItem(STR(t.id));
            }
            //need optimization above
            ui->faceVNumber->setCurrentIndex(0);
            ui->faceVertex->setCurrentIndex(ui->faceVertex->findText(STR(currentmodel->currentFace()->vertex[0])));
            ui->faceNormal->setCurrentIndex(ui->faceNormal->findText(STR(currentmodel->currentFace()->normal[0])));
            ui->faceTexture->setCurrentIndex(ui->faceTexture->findText(STR(currentmodel->currentFace()->texcoord[0])));
        }else if(current->parent()->text(0)=="Normal"){
            currentmodel->current_mode = CURRENT_NORMAL;
            ui->modelEditWidgets->setCurrentWidget(ui->normalPage);
            currentmodel->currentObjectId = qHash(current->parent()->parent()->text(0));
            currentmodel->currentNormalId = current->text(0).toInt();
            ui->normalAlpha->setValue(currentmodel->currentNormal()->a);
            ui->normalTheta->setValue((currentmodel->currentNormal()->t-90)%360);
        }else if(current->parent()->text(0)=="Texture"){
            currentmodel->current_mode = CURRENT_TEXTURE;
            ui->modelEditWidgets->setCurrentWidget(ui->texturePage);
            currentmodel->currentObjectId = qHash(current->parent()->parent()->text(0));
            currentmodel->currentTextureId = current->text(0).toInt();
            ui->textureU->setValue(currentmodel->currentTexture()->u);
            ui->textureV->setValue(currentmodel->currentTexture()->v);
        }else if(current->parent()->text(0)=="Pivot"){
            currentmodel->current_mode = CURRENT_PIVOT;
            ui->modelEditWidgets->setCurrentWidget(ui->pivotPage);
            currentmodel->currentObjectId = qHash(current->parent()->parent()->text(0));
            currentmodel->currentPivotId = qHash(current->text(0));
            if(currentmodel->currentPivot()!=NULL){
                /*ui->pivotX->setValue(currentmodel->currentPivot()->x);
                ui->pivotY->setValue(currentmodel->currentPivot()->y);
                ui->pivotZ->setValue(currentmodel->currentPivot()->z);
                ui->pivotA->setValue(currentmodel->currentPivot()->a);
                ui->pivotT->setValue(currentmodel->currentPivot()->t);*/
            }
        }else if (current->text(0) == "Object"){
            ui->modelEditWidgets->setCurrentWidget(ui->objectParentPage);
        }else if (current->text(0) == "Vertex"){
            ui->modelEditWidgets->setCurrentWidget(ui->objectParentPage);
        }else if (current->text(0) == "Object"){
            ui->modelEditWidgets->setCurrentWidget(ui->objectParentPage);
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

void MainWindow::objectNameChanged(){

}

void MainWindow::objectTextureChanged(){

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

void MainWindow::materialSetType(){

}

void MainWindow::materialSlider1Changed(){

}

void MainWindow::materialSlider2Changed(){

}

void MainWindow::materialSlider3Changed(){

}

void MainWindow::materialSlider4Changed(){

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

void MainWindow::faceVertexChanged()
{
//    currentmodel->currentFace()->vertex[currentmodel->currentFaceVNumber] = ui->faceVertex->currentText().toInt();
}

void MainWindow::faceNormalChanged()
{
    //currentmodel->currentFace()->normal[currentmodel->currentFaceVNumber] = ui->faceNormal->currentText().toInt();
}

void MainWindow::faceTextureChanged()
{
    //currentmodel->currentFace()->texcoord[currentmodel->currentFaceVNumber] = ui->faceTexture->currentText().toInt();
}

void MainWindow::faceVNumberChanged(){
    currentmodel->currentFaceVNumber = ui->faceVNumber->currentIndex();
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
    currentmodel->currentVertex()->x = v;
}

void MainWindow::vertexYChanged(double v){
    currentmodel->currentVertex()->y = v;
}

void MainWindow::vertexZChanged(double v){
    currentmodel->currentVertex()->z = v;
}

/* Texture Coordinates Control */

void MainWindow::textureAddClicked()
{
}

void MainWindow::textureRemoveClicked()
{
}

void MainWindow::textureUChanged(double v){
    currentmodel->currentTexture()->u = v;
}

void MainWindow::textureVChanged(double v){
    currentmodel->currentTexture()->v = v;
}

/* NormalControl */

void MainWindow::normalAddClicked()
{
}

void MainWindow::normalRemoveClicked()
{
}

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
