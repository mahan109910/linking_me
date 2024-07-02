#ifndef MY_NETWORK_H
#define MY_NETWORK_H

#include <QMainWindow>

namespace Ui {
class My_Network;
}

class My_Network : public QMainWindow
{
    Q_OBJECT

public:
    explicit My_Network(QWidget *parent = nullptr);
    ~My_Network();

private:
    Ui::My_Network *ui;
};

#endif // MY_NETWORK_H
