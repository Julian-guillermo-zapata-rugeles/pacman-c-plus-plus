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
#include <fstream>


using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // unico timer del vídeojuego.
    controlMovimiento->start(80);
    connect(controlMovimiento,SIGNAL(timeout()),this,SLOT(refrescarPantalla()));

    // creación de la escena
    scene = new QGraphicsScene(0,0,400,400);
    ui->visorGrafico->setScene(scene);

    // creación de las paredes y moendas
    construir(true,"coordenadas");
    construir(false,"monedero");

    // añadir personajes a la escena
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
        // caso en el que se quiera dezplazar hacia derecha
                 personaje->setMovimiento('d');

    }
    if(evento->key()==Qt::Key_A){
        // caso en el que se quiera dezplazar hacia izquierda
                 personaje->setMovimiento('a');
    }

}

void MainWindow::construir(bool mode,string file)
{
    if(mode==true){
           paredon.clear();
    }
    else{
           monedero.clear();
    }
    ifstream plano_coordenadas;
    plano_coordenadas.open(file);
    int ancho,alto,x,y;
    while (!plano_coordenadas.eof()) {
        plano_coordenadas >> ancho >> alto >> x >> y ;
        cout << ancho <<"-"<<alto <<"-"<< x <<"-"<< y << endl;

        if(mode==true){
            paredon.push_back(new paredes(ancho,alto,x,y));
        }
        else{
            monedero.push_back(new monedas(ancho,alto,x,y));
            }

        }
    if(mode==true){
        for (auto& it:paredon) {
            scene->addItem(it);
               scene->addItem(it);
        }
    }
    else{
        for (auto& it:monedero) {
            scene->addItem(it);
               scene->addItem(it);
        }
    }
    //scene->advance();
}




void MainWindow::refrescarPantalla()
{
    personaje->cambiarAnimacion();
    for(auto& it:paredon){
        if(personaje->collidesWithItem(it)){
            if(personaje->getMovimiento()=='w'){
                personaje->coordenada_y+=5;
            }
            else if(personaje->getMovimiento()=='s'){
                personaje->coordenada_y-=5;
            }
            else if(personaje->getMovimiento()=='a'){
                personaje->coordenada_x+=5;
            }
            else if(personaje->getMovimiento()=='d'){
                personaje->coordenada_x-=5;
            }
            personaje->setMovimiento('0');
        }
    }
}


void MainWindow::on_btn_iniciar_clicked()
{
    eliminarElementos();
    construir(true,"coordenadas");
    construir(false,"monedero");
}

void MainWindow::eliminarElementos()
{
     for(auto& it:paredon){
         scene->removeItem(it);
     }
     for(auto& it:monedero){
         scene->removeItem(it);
     }
}
