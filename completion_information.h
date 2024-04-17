#ifndef COMPLETION_INFORMATION_H
#define COMPLETION_INFORMATION_H

#include <QMainWindow>

namespace Ui {
class Completion_information;
}

class Completion_information : public QMainWindow
{
    Q_OBJECT

public:
    explicit Completion_information(QWidget *parent = nullptr);
    ~Completion_information();

private:
    Ui::Completion_information *ui;
};

#endif // COMPLETION_INFORMATION_H
