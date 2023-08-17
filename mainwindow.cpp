#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNova_Tarefa, &QAction::triggered, this, &MainWindow::newTaskTrigged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::newTaskTrigged()
{

}

