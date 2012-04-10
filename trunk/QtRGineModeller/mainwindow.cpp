#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("RGine Modelling Tool");
    //this->showMaximized();

    glwidget = new GLWidget(ui->glframe);
    //this->resize(this->size());
    //glwidget->resize(ui->glframe->size());

    ui->vertexEdit->hide();

    QTimer *timer = new QTimer();

    connect(timer,SIGNAL(timeout()),glwidget,SLOT(update()));
    timer->start(10);

    connect(ui->actionLoad,SIGNAL(triggered()),this,SLOT(loadFile()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveFile()));

    connect(ui->actionAdd_Face,SIGNAL(triggered()),this,SLOT(addFace()));

    connect(ui->objectstructure,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(selection()));

    connect(ui->spin_x,SIGNAL(valueChanged(double)),this,SLOT(changeX(double)));
    connect(ui->spin_y,SIGNAL(valueChanged(double)),this,SLOT(changeY(double)));
    connect(ui->spin_z,SIGNAL(valueChanged(double)),this,SLOT(changeZ(double)));

    connect(ui->sliderR,SIGNAL(valueChanged(int)),this,SLOT(changeR(int)));
    connect(ui->sliderG,SIGNAL(valueChanged(int)),this,SLOT(changeG(int)));
    connect(ui->sliderB,SIGNAL(valueChanged(int)),this,SLOT(changeB(int)));

    //ui->statusBar->showMessage("testing status bar");

    QImage texture;
    texture.load("image.bmp");
    //QImage::
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *){
    glwidget->resize(ui->glframe->size());
}

void MainWindow::selection(){
    ui->vertexEdit->hide();
    Vertex vert;
    if(ui->objectstructure->currentItem()->text(1)== "Face"){
        glwidget->model.currentVertex = "";
        glwidget->model.currentObject = ui->objectstructure->currentItem()->text(2);
        glwidget->model.currentFace = ui->objectstructure->currentItem()->text(0);

        int fc=0;
        foreach(Vertex vert, glwidget->model.object[glwidget->model.currentObject].vertex){
            if(vert.facename == glwidget->model.currentFace){
                glwidget->model.faceVertex[fc] = vert.name;
                fc++;
                if(fc>2) {break;}
            }
        }

        vert = glwidget->model.object[glwidget->model.currentObject].vertex[glwidget->model.faceVertex[0]];
    }else if(ui->objectstructure->currentItem()->text(1)== "Vertex"){
        ui->vertexEdit->show();
        glwidget->model.currentVertex = ui->objectstructure->currentItem()->text(0);
        glwidget->model.currentObject = ui->objectstructure->currentItem()->text(2);
        glwidget->model.currentFace = glwidget->model.object[glwidget->model.currentObject].vertex[glwidget->model.currentVertex].facename;

        int fc=0;
        foreach(Vertex vert, glwidget->model.object[glwidget->model.currentObject].vertex){
            if(vert.facename == glwidget->model.currentFace){
                glwidget->model.faceVertex[fc] = vert.name;
                fc++;
                if(fc>2) {break;}
            }
        }

        vert = glwidget->model.object[glwidget->model.currentObject].vertex[glwidget->model.currentVertex];

    }else{
        glwidget->model.currentVertex = "";
        glwidget->model.currentFace = "";
        glwidget->model.currentObject = "";
    }

    ui->spin_x->setValue(vert.x);
    ui->spin_y->setValue(vert.y);
    ui->spin_z->setValue(vert.z);
    ui->sliderR->setValue(vert.r*255);
    ui->sliderG->setValue(vert.g*255);
    ui->sliderB->setValue(vert.b*255);

    QString status;
    status.append("Object: ").append(glwidget->model.currentObject);
    status.append(" Face: ").append(glwidget->model.currentFace);
    status.append(" Vertex: ").append(glwidget->model.currentVertex);
    ui->statusBar->showMessage(status);
}

void MainWindow::buildTree(){
    QTreeWidgetItem *modelitem,*objitem,*faceitem,*vertexitem;

    ui->objectstructure->clear();
    ui->objectstructure->addTopLevelItem(modelitem = new QTreeWidgetItem(0));
    modelitem->setText(0,glwidget->model.name);
    modelitem->setText(1,"Model");
    modelitem->setText(2,"-");
    modelitem->setText(3,"yes");
    //int totfacecount = 0;
    //int totvertcount =0;
    foreach(Object obj, glwidget->model.object){
        modelitem->addChild(objitem = new QTreeWidgetItem(0));
        objitem->setText(0,obj.name);
        objitem->setText(1,"Part");
        objitem->setText(2,obj.name);
        objitem->setText(3,"yes");
        int vertcount = 0;
        foreach(Vertex ver, obj.vertex){
            if(vertcount==0){
                objitem->addChild(faceitem = new QTreeWidgetItem(0));
                faceitem->setText(0,ver.facename);
                faceitem->setText(1,"Face");
                faceitem->setText(2,obj.name);
                //faceitem->setText(3,ver.facename);
                faceitem->setText(3,ver.facename);
            }
            faceitem->addChild(vertexitem = new QTreeWidgetItem(0));
            vertexitem->setText(0,ver.name);
            vertexitem->setText(1,"Vertex");
            vertexitem->setText(2,obj.name);
            //vertexitem->setText(3,ver.facename);
            //vertexitem->setText(4,ver.name);
            vertexitem->setText(3,ver.facename);
            vertcount++;
            vertcount = vertcount%3;
        }
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save"),
                                                    filename,
                                                    tr("All Files (*)"));
    if (!fileName.isEmpty()){
        filename = fileName;

        glwidget->model.save(filename);
    }

}

void MainWindow::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    filename,
                                                    tr("All Files (*);;Text Files (*.txt)"));
    if (!fileName.isEmpty())
    {
        filename = fileName;

        glwidget->model.clear();
        glwidget->model.load(filename);

        buildTree();
    }
}

void MainWindow::addFace(){
    QString newobjname = "NewObject";
    glwidget->model.object[newobjname] = Object();
    glwidget->model.object[newobjname].name = newobjname;
    QString newfacename = "face";
    newfacename.append(QString::number(glwidget->model.facecount));
    for(int i=0;i<3;i++){
        QString newvertexname = "vertex";
        newvertexname.append(QString::number(glwidget->model.vertcount));
        glwidget->model.object[newobjname].vertex[newvertexname] = Vertex();
        glwidget->model.object[newobjname].vertex[newvertexname].name = newvertexname;
        glwidget->model.object[newobjname].vertex[newvertexname].facename = newfacename;
        glwidget->model.object[newobjname].vertex[newvertexname].objectname = newobjname;
        glwidget->model.vertcount++;
    }
    glwidget->model.facecount++;

    buildTree();
}

void MainWindow::removeFace(){

}

void MainWindow::addObject(){

}

void MainWindow::removeObject(){

}

void MainWindow::changeX(double val){
    QString vert = glwidget->model.currentVertex;
    QString obj = glwidget->model.currentObject;
    if(obj!="" and vert!=""){
        glwidget->model.object[obj].vertex[vert].x = val;
    }
}
void MainWindow::changeY(double val){
    QString vert = glwidget->model.currentVertex;
    QString obj = glwidget->model.currentObject;
    if(obj!="" and vert!=""){
        glwidget->model.object[obj].vertex[vert].y = val;
    }
}
void MainWindow::changeZ(double val){
    QString vert = glwidget->model.currentVertex;
    QString obj = glwidget->model.currentObject;
    if(obj!="" and vert!=""){
        glwidget->model.object[obj].vertex[vert].z = val;
    }
}

void MainWindow::changeR(int val)
{
    QString vert = glwidget->model.currentVertex;
    QString face = glwidget->model.currentFace;
    QString obj = glwidget->model.currentObject;
    if(obj!="" and vert!=""){
        glwidget->model.object[obj].vertex[vert].r = val/255.0;
    }
    else if(obj!="" and face!=""){
        glwidget->model.object[obj].vertex[glwidget->model.faceVertex[0]].r = val/255.0;
        glwidget->model.object[obj].vertex[glwidget->model.faceVertex[1]].r = val/255.0;
        glwidget->model.object[obj].vertex[glwidget->model.faceVertex[2]].r = val/255.0;
    }
}
void MainWindow::changeG(int val)
{
    QString vert = glwidget->model.currentVertex;
    QString face = glwidget->model.currentFace;
    QString obj = glwidget->model.currentObject;
    if(obj!="" and vert!=""){
        glwidget->model.object[obj].vertex[vert].g = val/255.0;
    }
    else if(obj!="" and face!=""){
        glwidget->model.object[obj].vertex[glwidget->model.faceVertex[0]].g = val/255.0;
        glwidget->model.object[obj].vertex[glwidget->model.faceVertex[1]].g = val/255.0;
        glwidget->model.object[obj].vertex[glwidget->model.faceVertex[2]].g = val/255.0;
    }
}
void MainWindow::changeB(int val)
{
    QString vert = glwidget->model.currentVertex;
    QString face = glwidget->model.currentFace;
    QString obj = glwidget->model.currentObject;
    if(obj!="" and vert!=""){
        glwidget->model.object[obj].vertex[vert].b = val/255.0;
    }
    else if(obj!="" and face!=""){
        glwidget->model.object[obj].vertex[glwidget->model.faceVertex[0]].b = val/255.0;
        glwidget->model.object[obj].vertex[glwidget->model.faceVertex[1]].b = val/255.0;
        glwidget->model.object[obj].vertex[glwidget->model.faceVertex[2]].b = val/255.0;
    }
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
