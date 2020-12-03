#ifndef PAREDES_H
#define PAREDES_H
#include <QGraphicsItem>
#include <QPainter>

class paredes : public QGraphicsItem
{
private:
    signed int ancho;
    signed int alto ;
    int x_position;
    int y_position;
public:
    paredes(signed int , signed int , int x, int y);
    void mostrar_pared();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
};

#endif // PAREDES_H
