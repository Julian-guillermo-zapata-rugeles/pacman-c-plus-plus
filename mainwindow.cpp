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
    scene->addItem(personaje);
    scene->setFocusItem(personaje);
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

void MainWindow::construir_enemigos()
{
    for(unsigned short int a=0;a<3;a++){
        vector_fantasmas.push_back(new fantasmas());
    }
    for(auto& it:vector_fantasmas){
        scene->addItem(it);
        it->cambiar_direccion_fantasma();
    }

}




void MainWindow::refrescarPantalla()
{
    personaje->cambiarAnimacion();
    if(melodia->state()==QMediaPlayer::StoppedState and fin_juego==false){
        melodia->setMedia(QUrl("qrc:/comer.wav"));
        if(fantasmas_a_escena==false){
            construir_enemigos();
            fantasmas_a_escena=true;
        }
    }
    unsigned short int i=0;
    if(monedero.size()==0){
        ui->visorGrafico->hide();
        ui->label_2->setText("GANASTE");
        ui->label_2->setStyleSheet("font-size:36pt; font-weight:600; color:#fce94f");
    }
    else if(monedero.size()<10){
        scene->setBackgroundBrush(Qt::red);
    }

    if(inicio_juego==true and fin_juego==false){
        fantasma_ticks=fantasma_ticks+1;


        //  ------------- AREA DE FANTASMAS ----------------//
        for(auto& fan:vector_fantasmas){
            if(fan->collidesWithItem(personaje)){
                //

                ui->label_2->setText(QString::number(puntaje)+" Puntos (Perdiste)");
                ui->label_2->setStyleSheet("font-size:18pt; font-weight:600; color:red");
                ui->visorGrafico->hide();
                personaje->disconnect();
                fin_juego=true;
                //eliminarElementos();
            }

            fan->mover_fantasmas();
            fan->comprobar_limite();
            for(auto& muros:paredon){
                if(fan->collidesWithItem(muros)){
                    fan->colision();
                    fan->cambiar_direccion_fantasma();
                }
            }
        }
        if(fantasma_ticks>100){
            for(auto& fan:vector_fantasmas){
                fan->cambiar_direccion_fantasma();
                fan->mover_fantasmas();

            }
            fantasma_ticks=0;
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
            for(auto& fan:vector_fantasmas){
                if(it->collidesWithItem(fan)){
                    fan->cambiar_direccion_fantasma();
                }
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
        cout << "ticks "<<ticks <<" fantasmas "<< fantasma_ticks << endl;
    }
}
void MainWindow::on_btn_iniciar_clicked()
{
    eliminarElementos();
    construir(true,"coordenadas");
    construir(false,"monedero");
    construir_enemigos();
    ui->visorGrafico->show();
}

void MainWindow::eliminarElementos()
{
    for(auto& it:paredon){
        scene->removeItem(it);
        paredon.erase(std::remove(paredon.begin(),paredon.end(),it),paredon.end());
    }
    for(auto& it:monedero){
        scene->removeItem(it);
        monedero.erase(std::remove(monedero.begin(),monedero.end(),it),monedero.end());
    }
    for(auto& it:vector_fantasmas){
        scene->removeItem(it);
        vector_fantasmas.erase(std::remove(vector_fantasmas.begin(),vector_fantasmas.end(),it),vector_fantasmas.end());
    }
    scene->removeItem(personaje);
}

void MainWindow::on_btn_salir_clicked()
{
    exit(0);
}
