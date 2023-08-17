#include "newtask.hpp"
#include "ui_newtask.h"

NewTask::NewTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTask)
{
    ui->setupUi(this);
}

NewTask::~NewTask()
{
    delete ui;
}

QString NewTask::name() const
{
    return m_name;
}

void NewTask::setName(const QString &newName)
{
    m_name = newName;
}

QString NewTask::description() const
{
    return m_description;
}

void NewTask::setDescription(const QString &newDescription)
{
    m_description = newDescription;
}

QDate NewTask::startDate() const
{
    return m_startDate;
}

void NewTask::setStartDate(const QDate &newStartDate)
{
    m_startDate = newStartDate;
}

QDate NewTask::endDate() const
{
    return m_endDate;
}

void NewTask::setEndDate(const QDate &newEndDate)
{
    m_endDate = newEndDate;
}

QString NewTask::status() const
{
    return m_status;
}

void NewTask::setStatus(const QString &newStatus)
{
    m_status = newStatus;
}
