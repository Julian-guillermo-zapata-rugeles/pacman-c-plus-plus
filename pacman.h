#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QTime>

class pacman : public QObject , public QGraphicsItem
        // heredamos de QGraphicsItem sus método públicos
{
    Q_OBJECT
public:
    explicit pacman(QObject *parent = nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
    QPixmap *pixmap; //creamos un Qpixmap
    QTimer *controlMovimiento = new QTimer();

    // coordenadas de movimiento //
    signed int coordenada_x;
    signed int coordenada_y;

    // funciones publicas //
    void comprobar_limite();

private:
    // dimensiones de la figura //
    unsigned short int ancho;
    unsigned short int alto;


    // sprite coordenadas //
    unsigned short int filas;
    unsigned short int columnas;

signals:
    public slots:
        void cambiarAnimacion();


};

#endif // PACMAN_H
