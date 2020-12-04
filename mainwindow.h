#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "pacman.h"
#include "paredes.h"
#include <QVector>
#include <QTimer>

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
    QVector<paredes*> paredon;
    QTimer *controlMovimiento = new QTimer();
    QGraphicsScene *scene;
    pacman *personaje;
    void keyPressEvent(QKeyEvent *evento);
    Ui::MainWindow *ui;
    void construir_paredes();
private slots:
    void refrescarPantalla();
    void on_btn_iniciar_clicked();
    void eliminarElementos();
};
#endif // MAINWINDOW_H
