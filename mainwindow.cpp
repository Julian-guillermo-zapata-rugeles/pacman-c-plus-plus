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
#include <QMediaPlayer>
#include <QString>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // unico timer del vídeojuego.
    melodia->setMedia(QUrl("qrc:/pacman-song.mp3"));
    controlMovimiento->start(50);
    connect(controlMovimiento,SIGNAL(timeout()),this,SLOT(refrescarPantalla()));

    // creación de la escena
    scene = new QGraphicsScene(0,0,400,400);
    ui->visorGrafico->setScene(scene);

    // creación de las paredes y moendas
    construir(true,"coordenadas");
    construir(false,"monedero");

    // añadir personajes a la escena
    personaje = new pacman();
    p_fantasma = new fantasmas();
    p_fantasma->cambiar_direccion_fantasma();

    scene->addItem(personaje);
    scene->addItem(p_fantasma);

    scene->setFocusItem(personaje);
    ui->visorGrafico->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(inicio_juego==true){
     //---------------  Movimiento Vertical  ---------------
        if(evento->key()==Qt::Key_W){
                // caso en el que se quiera dezplazar hacia arriba
                     personaje->setMovimiento('w');
                     personaje->setRotation(-90);
        }
        if(evento->key()==Qt::Key_S){
            // caso en el que se quiera dezplazar hacia abajo
                     personaje->setMovimiento('s');
                     personaje->setRotation(90);
        }


        //---------------  Movimiento horizontal ---------------
        if(evento->key()==Qt::Key_D){
            // caso en el que se quiera dezplazar hacia derecha
                     personaje->setMovimiento('d');
                     personaje->setRotation(0);

        }
        if(evento->key()==Qt::Key_A){
            // caso en el que se quiera dezplazar hacia izquierda
                     personaje->setMovimiento('a');
                     personaje->setRotation(180);
        }

}
}

void MainWindow::construir(bool mode,string file)
{
    puntaje=0;
    ui->marcador->setText(QString::number(puntaje));
    ui->marcador->setStyleSheet("font-size:20pt; font-weight:600; color:#fce94f");
    melodia->play();
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

}




void MainWindow::refrescarPantalla()
{
    if(fantasma_ticks>50){
        p_fantasma->cambiar_direccion_fantasma();
        fantasma_ticks=0;
    }
    fantasma_ticks=fantasma_ticks+1;
    if(melodia->state()==QMediaPlayer::StoppedState){
        ui->visorGrafico->show();
        melodia->setMedia(QUrl("qrc:/comer.wav"));
        inicio_juego=true;
        p_fantasma->mover_fantasmas();
        p_fantasma->comprobar_limite();
    }
    personaje->cambiarAnimacion();
    unsigned short int i=0;
    if(monedero.size()==0){
        ui->visorGrafico->hide();
        ui->label_2->setText("GANASTE");
        ui->label_2->setStyleSheet("font-size:36pt; font-weight:600; color:#fce94f");
    }
    else if(monedero.size()<10){
        scene->setBackgroundBrush(Qt::red);
    }
    for(auto& mon:monedero){
        if(personaje->collidesWithItem(mon)){
            melodia->play();
            scene->removeItem(mon);
            monedero.erase(std::remove(monedero.begin(),monedero.end(),mon),monedero.end());
            puntaje=puntaje+1;
            std::cout << " restantes "<<monedero.size() <<std::endl;
            ui->marcador->setText(QString::number(puntaje));
            ui->marcador->setStyleSheet("font-size:20pt; font-weight:600; color:#fce94f");
        }
        i++;
    }
    for(auto& it:paredon){
        if(p_fantasma->collidesWithItem(it)){
            p_fantasma->colision();
            p_fantasma->cambiar_direccion_fantasma();

        }
        if(personaje->collidesWithItem(it)){
            personaje->colision();
        }
        for(auto& it:monedero){

            if(ticks < 10){
               it->setOpacity(0.5);
            }
            else if(ticks >=10 && ticks<20){
                it->setOpacity(1);
            }
            else{
                ticks=0;
            }
         }
    }
    ticks=ticks+1;
    cout << "ticks "<<ticks << endl;

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

void MainWindow::on_btn_salir_clicked()
{
    exit(0);
}
