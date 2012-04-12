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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *){
    glwidget->resize(ui->glframe->size());
}
