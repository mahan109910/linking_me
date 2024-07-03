#ifndef JOB_H
#define JOB_H

#include <QWidget>

namespace Ui {
class job;
}

class job : public QWidget
{
    Q_OBJECT

public:
    explicit job(QWidget *parent = nullptr);
    ~job();

private:
    Ui::job *ui;
};

#endif // JOB_H
