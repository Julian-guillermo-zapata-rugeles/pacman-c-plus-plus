#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pacman.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,400,400);
    ui->visorGrafico->setScene(scene);
    personaje = new pacman();
    scene->addItem(personaje);

}

MainWindow::~MainWindow()
{
    delete ui;
}

