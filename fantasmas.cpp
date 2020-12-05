#include "fantasmas.h"
#include <iostream>
#include <random>
fantasmas::fantasmas(QObject *parent) : QObject(parent)
{
    srand(time(0));
    ancho=30;
    alto=30;
    coordenada_x=200;
    coordenada_y=200;
    filas=0;
    columnas=0;
    velocidad=3;
    fantasma = new QPixmap(":/imagenes/fantasma.png");
    setPos(coordenada_x,coordenada_y);

}

void fantasmas::cambiar_direccion_fantasma()
{
    velocidad=3;
    int direccion=0+rand()%4;
    std::cout <<"direccion :"<< direccion <<std::endl;
    if(direccion==0){
        direction='w';
    }
    else if(direccion==1){
        direction='s';
    }
    else if(direccion==2){
        direction='a';
    }
    else{
        direction='d';
        std::cout << " ----- izquierda----------" << std::endl;
    }
}

QRectF fantasmas::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void fantasmas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     painter->drawPixmap(-ancho/2,-alto/2,*fantasma,columnas,0,ancho,alto);
}

unsigned short fantasmas::getVelocidad() const
{
    return velocidad;
}

void fantasmas::setVelocidad(unsigned short value)
{
    velocidad = value;
}

void fantasmas::colision()
{
    if(direction=='w'){
        coordenada_y+=3;
    }
    else if(direction=='s'){
        coordenada_y-=3;
    }
    else if(direction=='a'){
        coordenada_x+=3;
    }
    else if(direction=='d'){
       coordenada_x-=3;
    }
    velocidad=0;
  ;
}



void fantasmas::comprobar_limite()
{
    /*
    comprobar límite :
        esta función trasladará a pacman a hacia una esquina contraria cuando pacman sobrepase el límite definido

    */

    if(coordenada_x<=0){
        // caso en que pacman se acerca al límite izquierdo
        coordenada_x=399;
    }
    else if(coordenada_x>400){
        // caso en que pacman se acerca al límite derecho
        coordenada_x=1;
    }
    else if(coordenada_y<=0){
        // caso en que pacman se acerca al límite superior
        coordenada_y=399;
    }
    else if (coordenada_y>400){
        // caso en que pacman se acerca al límite inferior
        coordenada_y=0;
    }
    setPos(coordenada_x,coordenada_y);
}

void fantasmas::mover_fantasmas()
{
    if(direction=='w'){
        coordenada_y=coordenada_y-3;
    }
    if(direction=='s'){
        coordenada_y=coordenada_y+3;
    }
    if(direction=='a'){
        coordenada_x=coordenada_x-3;
    }
    if(direction=='d'){
        coordenada_x=coordenada_x+3;
    }
    setPos(coordenada_x,coordenada_y);
}
