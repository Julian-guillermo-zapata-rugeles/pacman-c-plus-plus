#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pacman.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,400,400);
    ui->visorGrafico->setScene(scene);
    personaje = new pacman();
    scene->addItem(personaje);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key()==Qt::Key_W){
             personaje->coordenada_y=personaje->coordenada_y-2;
             personaje->comprobar_limite();
    }
    if(evento->key()==Qt::Key_S){
             personaje->coordenada_y=personaje->coordenada_y+2;
             personaje->comprobar_limite();
    }

    //---------------  Movimiento horizontal ---------------
    if(evento->key()==Qt::Key_D){
             personaje->coordenada_x=personaje->coordenada_x+3;
             personaje->comprobar_limite();
    }
    if(evento->key()==Qt::Key_A){
             personaje->coordenada_x=personaje->coordenada_x-3;
             personaje->comprobar_limite();
    }
}

