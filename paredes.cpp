#include "paredes.h"
#include <iostream>
paredes::paredes(signed int _ancho , signed int _alto , int _x, int _y)
{
    ancho=_ancho;
    alto=_alto;
    x_position=_x;
    y_position=_y;
}

void paredes::mostrar_pared()
{
    std::cout << ancho <<" "<<alto << " "<< x_position << " "<<y_position<<std::endl;
}

QRectF paredes::boundingRect() const
{
    return QRectF(x_position,y_position,ancho,alto);
}

void paredes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawRect(boundingRect());
}
