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
    bool inicio_juego=false;
    unsigned short int ticks=0;
    unsigned short int fantasma_ticks=0;
    QVector<monedas*> monedero; // vectores con objetos
    QVector<paredes*> paredon; // vectores con objetos
    QTimer *controlMovimiento = new QTimer(); // unico timer.
    QGraphicsScene *scene;
    pacman *personaje; // personaje principal PACMAN
    fantasmas *p_fantasma;
    QMediaPlayer *melodia = new QMediaPlayer;
    void keyPressEvent(QKeyEvent *evento);
    Ui::MainWindow *ui;
    unsigned short int puntaje=0;
    void construir(bool,std::string); // función para agregar en la escena las paredes y monedas

private slots:
    void refrescarPantalla();
    void on_btn_iniciar_clicked();
    void eliminarElementos();
    void on_btn_salir_clicked();
};
#endif // MAINWINDOW_H
