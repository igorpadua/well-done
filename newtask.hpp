#pragma once

#include <QWidget>
#include <QDate>

namespace Ui {
class NewTask;
}

class NewTask : public QWidget
{
    Q_OBJECT

public:
    explicit NewTask(QWidget *parent = nullptr);
    ~NewTask();

    QString name() const;
    void setName(const QString &newName);
    QString description() const;
    void setDescription(const QString &newDescription);
    QDate startDate() const;
    void setStartDate(const QDate &newStartDate);
    QDate endDate() const;
    void setEndDate(const QDate &newEndDate);
    QString status() const;
    void setStatus(const QString &newStatus);

private:
    Ui::NewTask *ui;
    QString m_name;
    QString m_description;
    QDate m_startDate;
    QDate m_endDate;
    QString m_status;
};

