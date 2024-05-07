#ifndef INFORMATION_H
#define INFORMATION_H

#include <QMainWindow>

namespace Ui {
class information;
}

class information : public QMainWindow
{
    Q_OBJECT

public:
    explicit information(QWidget *parent = nullptr);
    ~information();

private:
    Ui::information *ui;
};

#endif // INFORMATION_H
