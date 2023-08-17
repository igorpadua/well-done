#pragma once

#include <QMainWindow>
#include <QDebug>

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

private:
    Ui::MainWindow *ui;
    void addTableItem(const NewTask *newTask);
    void updateTableItem(const NewTask *newTask);
    void filterTable(const QString &text, const int &column);
};
