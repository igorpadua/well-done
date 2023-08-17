#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNova_Tarefa, &QAction::triggered, this, &MainWindow::newTaskTrigged);
    connect(ui->tableWidget, &QTableWidget::doubleClicked, this, &MainWindow::tableWidgetDoubleClicked);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->resizeRowsToContents();
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
        ui->statusbar->showMessage("Tarefa não adicionada!", 1500);
        return;
    }

    addTableItem(newTask);
}

void MainWindow::addTableItem(const NewTask *newTask)
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(newTask->name()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(newTask->description()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(newTask->startDate().toString("dd/MM/yyyy")));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(newTask->endDate().toString("dd/MM/yyyy")));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(newTask->status()));

    ui->tableWidget->resizeRowsToContents();

    ui->statusbar->showMessage("Tarefa adicionada com sucesso!", 1500);
}

void MainWindow::updateTableItem(const NewTask *newTask)
{
    ui->tableWidget->setItem(ui->tableWidget->currentRow(), 0, new QTableWidgetItem(newTask->name()));
    ui->tableWidget->setItem(ui->tableWidget->currentRow(), 1, new QTableWidgetItem(newTask->description()));
    ui->tableWidget->setItem(ui->tableWidget->currentRow(), 2, new QTableWidgetItem(newTask->startDate().toString("dd/MM/yyyy")));
    ui->tableWidget->setItem(ui->tableWidget->currentRow(), 3, new QTableWidgetItem(newTask->endDate().toString("dd/MM/yyyy")));
    ui->tableWidget->setItem(ui->tableWidget->currentRow(), 4, new QTableWidgetItem(newTask->status()));

    ui->tableWidget->resizeRowsToContents();

    ui->statusbar->showMessage("Tarefa atualizada com sucesso!", 1500);
}


void MainWindow::tableWidgetDoubleClicked(const QModelIndex &index)
{
   NewTask *newTask = new NewTask(this, ui->tableWidget->item(index.row(), 0)->text(), ui->tableWidget->item(index.row(), 1)->text(),
                                  QDate::fromString(ui->tableWidget->item(index.row(), 2)->text(), "dd/MM/yyyy"),
                                  QDate::fromString(ui->tableWidget->item(index.row(), 3)->text(), "dd/MM/yyyy"), ui->tableWidget->item(index.row(), 4)->text());

   newTask->exec();

   if (newTask->result() == QDialog::Rejected) {
       ui->statusbar->showMessage("Atualização cancelada!", 1500);
       return;
   }

   updateTableItem(newTask);
}

