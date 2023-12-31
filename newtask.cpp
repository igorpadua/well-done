#include "newtask.hpp"
#include "ui_newtask.h"

NewTask::NewTask(QWidget *parent, const QString &name, const QString &description, const QDate &startDate, const QDate &endDate, const QString &status) :
    QDialog(parent),
    ui(new Ui::NewTask)
  , m_name(name)
  , m_description(description)
  , m_startDate(startDate)
  , m_endDate(endDate)
  , m_status(status)
{
    ui->setupUi(this);

    ui->lineEditName->setText(m_name);
    ui->textEditDescription->setText(m_description);
    ui->dateEditStartDate->setDate(m_startDate);
    ui->dateEditEndDate->setDate(m_endDate);
    ui->comboBox->setCurrentText(m_status);

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &NewTask::buttonBoxClicked);
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

void NewTask::buttonBoxClicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton stdButton = ui->buttonBox->standardButton(button);

    if (stdButton == QDialogButtonBox::Cancel) {
        reject();
        return;
    }

    m_name = ui->lineEditName->text();

    if (m_name.isEmpty()) {
        QMessageBox::warning(this, "Atenção", "O nome da tarefa não pode ser vazio.");
        return;
    }

    m_description = ui->textEditDescription->toPlainText();
    m_startDate = ui->dateEditStartDate->date();
    m_endDate = ui->dateEditEndDate->date();
    m_status = ui->comboBox->currentText();

    accept();
}

