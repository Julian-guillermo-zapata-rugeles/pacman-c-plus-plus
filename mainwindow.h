#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "pacman.h"
#include "paredes.h"
#include <QVector>
#include <QTimer>
#include <monedas.h>

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
    QVector<monedas*> monedero; // vectores con objetos
    QVector<paredes*> paredon; // vectores con objetos

    QTimer *controlMovimiento = new QTimer(); // unico timer.
    QGraphicsScene *scene;
    pacman *personaje; // personaje principal PACMAN

    void keyPressEvent(QKeyEvent *evento);
    Ui::MainWindow *ui;

    void construir(bool,std::string); // función para agregar en la escena las paredes y monedas

private slots:
    void refrescarPantalla();
    void on_btn_iniciar_clicked();
    void eliminarElementos();
};
#endif // MAINWINDOW_H
