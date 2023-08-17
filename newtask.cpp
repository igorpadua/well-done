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

QString newTask::name() const
{
    return m_name;
}

void newTask::setName(const QString &newName)
{
    m_name = newName;
}

QString newTask::description() const
{
    return m_description;
}

void newTask::setDescription(const QString &newDescription)
{
    m_description = newDescription;
}

QDate newTask::startDate() const
{
    return m_startDate;
}

void newTask::setStartDate(const QDate &newStartDate)
{
    m_startDate = newStartDate;
}

QDate newTask::finishDate() const
{
    return m_finishDate;
}

void newTask::setFinishDate(const QDate &newFinishDate)
{
    m_finishDate = newFinishDate;
}

QString newTask::getStatus() const
{
    return status;
}

void newTask::setStatus(const QString &newStatus)
{
    status = newStatus;
}
