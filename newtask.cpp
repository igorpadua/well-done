#include "newtask.hpp"
#include "ui_newtask.h"

newTask::newTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newTask)
{
    ui->setupUi(this);
}

newTask::~newTask()
{
    delete ui;
}
