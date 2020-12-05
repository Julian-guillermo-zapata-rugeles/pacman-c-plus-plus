#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "pacman.h"
#include "paredes.h"
#include <QVector>
#include <QTimer>
#include "monedas.h"
#include <QMediaPlayer>
#include "fantasmas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    bool inicio_juego=true;
    bool fin_juego=false;
    bool fantasmas_a_escena=false;
    unsigned short int NumeroFantasmas=6;
    unsigned short int ticks=0;
    unsigned short int fantasma_ticks=0;
    unsigned short int puntaje=0;

    // VECTORES DE OBJETOS //
    QVector<fantasmas*> vector_fantasmas;
    QVector<monedas*> monedero; // vectores con objetos
    QVector<paredes*> paredon; // vectores con objetos

    // TIEMPO , GRAFICOS , MULTIMEDIA //
    QTimer *controlMovimiento = new QTimer(); // unico timer.
    QGraphicsScene *scene;
    pacman *personaje; // personaje principal PACMAN
    QMediaPlayer *melodia = new QMediaPlayer;
    void keyPressEvent(QKeyEvent *evento);
    Ui::MainWindow *ui;

    // MÉTODOS PARA LA CONSTRUCCIÓN DEL MAPA Y ANEXO DE FANTASMAS //
    void construir(bool,std::string); // función para agregar en la escena las paredes y monedas
    void construir_enemigos(); // agrega los enemigos al Qvector
    void eliminarElementos(); // Elimina sin restricción TODOS los Qvectors


private slots:
    void refrescarPantalla(); // refrescar los elementos , usé un unico TIMER
    void on_btn_iniciar_clicked(); // boton Desarollador (modificar mapa en tiempo de ejecución usando el archivo texto)
    void on_btn_salir_clicked();
};
#endif // MAINWINDOW_H
