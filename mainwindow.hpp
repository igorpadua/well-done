#pragma once

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    void addTableItem(NewTask *newTask);
};
