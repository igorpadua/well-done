#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db(QSqlDatabase::addDatabase("QSQLITE"))
{
    ui->setupUi(this);

    db.setDatabaseName("/home/igor/Documentos/Programas/well-done/well-done.db");

    if (!db.open()) {
        qDebug() << db.lastError().text();
        ui->statusbar->showMessage("Banco de dados não encontrado!", 1500);
        return;
    }

    QSqlQuery query(db);
    query.exec("SELECT * FROM TASK");

    while (query.next()) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(query.value(5).toString()));
    }

    connectActions();

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setSortingEnabled(true);

    ui->lineSearch->hide();
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

    if (db.open()) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(newTask->name()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(newTask->description()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(newTask->startDate().toString("dd/MM/yyyy")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(newTask->endDate().toString("dd/MM/yyyy")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(newTask->status()));

        ui->tableWidget->resizeRowsToContents();


        ui->statusbar->showMessage("Tarefa adicionada com sucesso!", 1500);

        QSqlQuery query(db);

        query.exec("INSERT INTO TASK (name, description, startDate, finishDate, status) VALUES ('" + newTask->name() + "', '" + newTask->description() + "', '" + newTask->startDate().toString("dd/MM/yyyy") + "', '" + newTask->endDate().toString("dd/MM/yyyy") + "', '" + newTask->status() + "')");

        if (query.lastError().isValid()) {
            qDebug() << query.lastError();
        }

        db.close();

    }

}

void MainWindow::updateTableItem(const NewTask *newTask)
{

    if (!db.open()) {
        qDebug() << db.lastError().text();
        ui->statusbar->showMessage("Tarefa não atualizada!", 1500);
        return;
    }

    ui->tableWidget->setItem(ui->tableWidget->currentRow(), 0, new QTableWidgetItem(newTask->name()));
    ui->tableWidget->setItem(ui->tableWidget->currentRow(), 1, new QTableWidgetItem(newTask->description()));
    ui->tableWidget->setItem(ui->tableWidget->currentRow(), 2, new QTableWidgetItem(newTask->startDate().toString("dd/MM/yyyy")));
    ui->tableWidget->setItem(ui->tableWidget->currentRow(), 3, new QTableWidgetItem(newTask->endDate().toString("dd/MM/yyyy")));
    ui->tableWidget->setItem(ui->tableWidget->currentRow(), 4, new QTableWidgetItem(newTask->status()));

    ui->tableWidget->resizeRowsToContents();

    ui->statusbar->showMessage("Tarefa atualizada com sucesso!", 1500);

    QSqlQuery query(db);

    // causa crash na aplicação
//    qDebug() << ui->tableWidget->item(ui->tableWidget->currentRow(), 5)->text();
    auto id = ui->tableWidget->currentRow() + 1;

    query.exec("UPDATE TASK SET name = '" + newTask->name() + "', description = '" + newTask->description() + "', startDate = '" + newTask->startDate().toString("dd/MM/yyyy") + "', finishDate = '" + newTask->endDate().toString("dd/MM/yyyy") + "', status = '" + newTask->status() + "' WHERE id = " + QString::number(id));


    if (query.lastError().isValid()) {
        qDebug() << query.lastError();
    }

    db.close();


    if (query.lastError().isValid()) {
        qDebug() << query.lastError();
    }
}

void MainWindow::filterTable(const QString &text, const int &column)
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        if (ui->tableWidget->item(i, column)->text().contains(text, Qt::CaseInsensitive)) {
            ui->tableWidget->showRow(i);
        } else {
            ui->tableWidget->hideRow(i);
        }
    }
}

void MainWindow::connectActions() const
{
    connect(ui->actionNova_Tarefa, &QAction::triggered, this, &MainWindow::newTaskTrigged);
    connect(ui->tableWidget, &QTableWidget::doubleClicked, this, &MainWindow::tableWidgetDoubleClicked);
    connect(ui->actionPesquisar, &QAction::triggered, this, &MainWindow::actionPesquisarTriggered);
    connect(ui->lineSearch, &QLineEdit::textChanged, this, &MainWindow::lineSearchTextChanged);
    connect(ui->action_FAZER, &QAction::triggered, this, &MainWindow::actionFazerTriggered);
    connect(ui->actionFazendo, &QAction::triggered, this, &MainWindow::actionFazendoTriggered);
    connect(ui->actionFeito, &QAction::triggered, this, &MainWindow::actionFeitoTriggered);
    connect(ui->actionTodos, &QAction::triggered, this, &MainWindow::actionTodosTriggered);
    connect(ui->actionQt, &QAction::triggered, this, &MainWindow::actionQtTriggered);
    connect(ui->actionWell_Done, &QAction::triggered, this, &MainWindow::actionWellDoneTriggered);
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


void MainWindow::actionPesquisarTriggered()
{
    if (ui->lineSearch->isHidden()) {
        ui->lineSearch->show();
        ui->lineSearch->setFocus();
    } else {
        ui->lineSearch->hide();
        ui->lineSearch->clear();
    }
}


void MainWindow::lineSearchTextChanged(const QString &arg1)
{
    filterTable(arg1, 0);
}


void MainWindow::actionFazerTriggered()
{
    filterTable("À Fazer", 4);
}

void MainWindow::actionFazendoTriggered()
{
    filterTable("Fazendo", 4);
}

void MainWindow::actionFeitoTriggered()
{
    filterTable("Feito", 4);
}

void MainWindow::actionTodosTriggered()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        ui->tableWidget->showRow(i);
    }
}


void MainWindow::actionQtTriggered()
{
    QMessageBox::aboutQt(this, "Sobre Qt");
}


void MainWindow::actionWellDoneTriggered()
{
    QMessageBox::about(this, "Sobre", "Desenvolvido por: <b>Igor Moreira Pádua</b><br>"
                                       "Email: <b>igormoreira@protonmail.com</b><br>"
                                       "GitHub: <b>github.com/igorpadua</b><br>"
                                       "Versão: <b>1.0</b><br>");

}

