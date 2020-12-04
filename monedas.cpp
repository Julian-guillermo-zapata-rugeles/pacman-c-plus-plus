#include "monedas.h"



monedas::monedas(int an, int al, int x, int y)
{
    ancho=an;
    alto=al;
    x_position=x;
    y_position=y;
}

QRectF monedas::boundingRect() const
{
    return QRectF(x_position,y_position,ancho,alto);
}

void monedas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());

}
