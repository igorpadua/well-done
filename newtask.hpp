#pragma once

#include <QDialog>
#include <QDate>
#include <QAbstractButton>
#include <QMessageBox>

namespace Ui {
class NewTask;
}

class NewTask : public QDialog
{
    Q_OBJECT

public:
    explicit NewTask(QWidget *parent = nullptr, const QString &name = "", const QString &description = "", const QDate &startDate = QDate::currentDate(), const QDate &endDate = QDate::currentDate(), const QString &status = "");
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

private slots:
    void buttonBoxClicked(QAbstractButton *button);

private:
    Ui::NewTask *ui;
    QString m_name;
    QString m_description;
    QDate m_startDate;
    QDate m_endDate;
    QString m_status;
};

