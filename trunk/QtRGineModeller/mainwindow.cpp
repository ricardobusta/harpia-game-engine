#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("RGine Modeller");
    //this->showMaximized();

    glwidget = new GLWidget(ui->glframe);
    //this->resize(this->size());
    //glwidget->resize(ui->glframe->size());

    QTimer *timer = new QTimer();

    connect(timer,SIGNAL(timeout()),glwidget,SLOT(update()));
    timer->start(10);

    connect(ui->actionLoad,SIGNAL(triggered()),this,SLOT(loadFile()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveFile()));

    connect(ui->actionAdd_Face,SIGNAL(triggered()),this,SLOT(addFace()));

    connect(ui->objectstructure,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(selectVertex()));

    //ui->statusBar->showMessage("testing status bar");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *){
    glwidget->resize(ui->glframe->size());
}

void MainWindow::selectVertex(){
    if(ui->objectstructure->currentItem()->text(1)== "V"){
        glwidget->model.currentVertex = ui->objectstructure->currentItem()->text(4);
        glwidget->model.currentFace = ui->objectstructure->currentItem()->text(3);
        glwidget->model.currentObject = ui->objectstructure->currentItem()->text(2);

        QString status;
        status.append("Object: ").append(glwidget->model.currentObject);
        status.append(" Face: ").append(glwidget->model.currentFace);
        status.append(" Vertex: ").append(glwidget->model.currentVertex);
        ui->statusBar->showMessage(status);
    }
}

void MainWindow::buildTree(){
    QTreeWidgetItem *modelitem,*objitem,*faceitem,*vertexitem;

    ui->objectstructure->clear();
    ui->objectstructure->addTopLevelItem(modelitem = new QTreeWidgetItem(0));
    modelitem->setText(0,glwidget->model.name);
    modelitem->setText(1,"M");
    modelitem->setText(5,"yes");
    //int totfacecount = 0;
    //int totvertcount =0;
    foreach(Object obj, glwidget->model.object){
        modelitem->addChild(objitem = new QTreeWidgetItem(0));
        objitem->setText(0,obj.name);
        objitem->setText(1,"O");
        objitem->setText(2,obj.name);
        objitem->setText(5,"yes");
        int vertcount = 0;
        foreach(Vertex ver, obj.vertex){
            if(vertcount==0){
                objitem->addChild(faceitem = new QTreeWidgetItem(0));
                faceitem->setText(0,ver.facename);
                faceitem->setText(1,"F");
                faceitem->setText(2,obj.name);
                faceitem->setText(3,ver.facename);
                faceitem->setText(5,"yes");
            }
            faceitem->addChild(vertexitem = new QTreeWidgetItem(0));
            vertexitem->setText(0,ver.name);
            vertexitem->setText(1,"V");
            vertexitem->setText(2,obj.name);
            vertexitem->setText(3,ver.facename);
            vertexitem->setText(4,ver.name);
            vertexitem->setText(5,"yes");
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
        glwidget->model.object[newobjname].vertex[newvertexname].x = 0;
        glwidget->model.object[newobjname].vertex[newvertexname].y = 0;
        glwidget->model.object[newobjname].vertex[newvertexname].z = 0;
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
