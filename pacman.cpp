#include "pacman.h"

pacman::pacman(QObject *parent) : QObject(parent)
{

    movimiento='0';
    // Configuración dimensiones del pixmap //
    ancho=30;
    alto=30;
    //
    // Coordenadas donde se ubicará  pixmap //
    coordenada_x=210;
    coordenada_y=200;
    //
    filas=0;    // fila del pixmap
    columnas=0; // columnas del pixmap
    pixmap = new QPixmap(":/imagenes/pacman_mini.png");
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

void pacman::setMovimiento(char value)
{
    movimiento_anterior=movimiento;
    movimiento = value;
}

void pacman::colision()
{
    if(getMovimiento()=='w'){
        coordenada_y+=5;
    }
    else if(getMovimiento()=='s'){
        coordenada_y-=5;
    }
    else if(getMovimiento()=='a'){
        coordenada_x+=5;
    }
    else if(getMovimiento()=='d'){
       coordenada_x-=5;
    }
    setMovimiento('0');
}

char pacman::getMovimiento() const
{
    return movimiento;
}

char pacman::getMovimiento_anterior() const
{
    return movimiento_anterior;
}




void pacman::cambiarAnimacion()
{
    /*
    Alternar las imágenes en el sprite pacman se determina como máximo cuantos cuadros tiene la imagen
    al alcanzar el máximo se resetea nuevamente para reanudar el ciclo del pacman.
    */
    this->update(-ancho/2,-alto/2,ancho,alto);
    columnas=columnas+30;
    if (columnas>=120){
        columnas=0;
    }


    if(movimiento=='w'){
        coordenada_y-=5;
        }
    else if(movimiento=='s'){
        coordenada_y+=5;
    }
    else if (movimiento=='a'){
        coordenada_x-=5;
    }
    else if (movimiento=='d') {
        coordenada_x+=5;
    }
    setPos(coordenada_x,coordenada_y);
    comprobar_limite();
}





