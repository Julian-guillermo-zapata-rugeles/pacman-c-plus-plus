#include "pacman.h"

pacman::pacman(QObject *parent) : QObject(parent)
{
    ancho=30;
    alto=30;
    coordenada_x=200;
    coordenada_y=200;
    filas=0;
    columnas=0;
    pixmap = new QPixmap(":/imagenes/img_pacman.png");
    controlMovimiento->start(200);
    connect(controlMovimiento,SIGNAL(timeout()),this,SLOT(cambiarAnimacion()));
    setPos(coordenada_x,coordenada_y);

}

QRectF pacman::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,0,ancho,alto);
}

void pacman::comprobar_limite()
{

    if(coordenada_x<=0){
        coordenada_x=399;
    }
    else if(coordenada_x>400){
        coordenada_x=1;
    }
    else if(coordenada_y<=0){
        coordenada_y=399;
    }
    else if (coordenada_y>400){
        coordenada_y=0;
    }
    setPos(coordenada_x,coordenada_y);
}

void pacman::cambiarAnimacion()
{
    columnas=columnas+30;
    if (columnas>=90){
        columnas=0;
    }
     this->update(-ancho/2,-alto/2,ancho,alto);
    setPos(coordenada_x,coordenada_y);

}




