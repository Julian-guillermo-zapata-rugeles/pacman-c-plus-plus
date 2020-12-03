/*

Julian Guillermo Zapata Rugeles


*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pacman.h"
#include "paredes.h"
#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,400,400);
    ui->visorGrafico->setScene(scene);
    personaje = new pacman();
    scene->addItem(personaje);
    scene->setFocusItem(personaje);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::keyPressEvent(QKeyEvent *evento)
{
     //---------------  Movimiento Vertical  ---------------
    if(evento->key()==Qt::Key_W){
        // caso en el que se quiera dezplazar hacia arriba
             personaje->setMovimiento('w');
    }
    if(evento->key()==Qt::Key_S){
        // caso en el que se quiera dezplazar hacia abajo
             personaje->setMovimiento('s');
    }


    //---------------  Movimiento horizontal ---------------
    if(evento->key()==Qt::Key_D){
        // caso en el que se quiera dezplazar hacia arriba
             personaje->setMovimiento('d');

    }
    if(evento->key()==Qt::Key_A){
        // caso en el que se quiera dezplazar hacia izquierda
             personaje->setMovimiento('a');
    }
}

