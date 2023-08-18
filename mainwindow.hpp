#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include "newtask.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newTaskTrigged();
    void tableWidgetDoubleClicked(const QModelIndex &index);
    void actionPesquisarTriggered();
    void lineSearchTextChanged(const QString &arg1);
    void actionFazerTriggered();
    void actionFazendoTriggered();
    void actionFeitoTriggered();
    void actionTodosTriggered();
    void actionQtTriggered();
    void actionWellDoneTriggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    void addTableItem(const NewTask *newTask);
    void updateTableItem(const NewTask *newTask);
    void filterTable(const QString &text, const int &column);
    void connectActions() const;
};
