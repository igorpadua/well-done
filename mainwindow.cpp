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
    NewTask *newTask = new NewTask(this);
    newTask->exec();

    if (newTask->result() == QDialog::Rejected) {
        return;
    }

    addTableItem(newTask);
}

void MainWindow::addTableItem(NewTask *newTask)
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(newTask->name()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(newTask->description()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(newTask->startDate().toString("dd/MM/yyyy")));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(newTask->endDate().toString("dd/MM/yyyy")));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(newTask->status()));
}

