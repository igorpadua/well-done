#pragma once

#include <QWidget>
#include <QDate>

namespace Ui {
class newTask;
}

class newTask : public QWidget
{
    Q_OBJECT

public:
    explicit newTask(QWidget *parent = nullptr);
    ~newTask();

    QString name() const;
    void setName(const QString &newName);
    QString description() const;
    void setDescription(const QString &newDescription);
    QDate startDate() const;
    void setStartDate(const QDate &newStartDate);
    QDate finishDate() const;
    void setFinishDate(const QDate &newFinishDate);
    QString getStatus() const;
    void setStatus(const QString &newStatus);

private:
    Ui::newTask *ui;
    QString m_name;
    QString m_description;
    QDate m_startDate;
    QDate m_finishDate;
    QString status;
};

