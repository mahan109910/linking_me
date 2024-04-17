#ifndef MANAGERS_H
#define MANAGERS_H

#include <QMainWindow>

namespace Ui {
class managers;
}

class managers : public QMainWindow
{
    Q_OBJECT

public:
    explicit managers(QWidget *parent = nullptr);
    ~managers();

private:
    Ui::managers *ui;
};

#endif // MANAGERS_H
