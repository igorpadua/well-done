#pragma once

#include <QWidget>

namespace Ui {
class newTask;
}

class newTask : public QWidget
{
    Q_OBJECT

public:
    explicit newTask(QWidget *parent = nullptr);
    ~newTask();

private:
    Ui::newTask *ui;
};

