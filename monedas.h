#ifndef MONEDAS_H
#define MONEDAS_H
#include <QGraphicsItem>
#include <QPainter>

class monedas:public QGraphicsItem
{
private:
    signed int ancho;
    signed int alto ;
    int x_position;
    int y_position;
public:
    monedas(int , int , int x, int y);
    void mostrar_pared();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
};

#endif // MONEDAS_H
