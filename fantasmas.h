#ifndef FANTASMAS_H
#define FANTASMAS_H
#include <QObject>
#include <QPainter>
#include <QGraphicsItem>
#include <QPixmap>

class fantasmas : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    explicit fantasmas(QObject *parent = nullptr);
    void cambiar_direccion_fantasma();
    unsigned short getVelocidad() const;
    void setVelocidad(unsigned short value);
    void mover_fantasmas();
    void colision();
    void comprobar_limite();

private:

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );

    QPixmap *fantasma; //creamos un Qpixmap
    // coordenadas de movimiento //
    char direction='0';
    signed int coordenada_x;
    signed int coordenada_y;
    unsigned short int velocidad;
    // sprite coordenadas //
    unsigned short int filas;
    unsigned short int columnas;
    unsigned short int ancho;
    unsigned short int alto;

signals:

};

#endif // FANTASMAS_H
