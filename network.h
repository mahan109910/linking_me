#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>

namespace Ui {
class network;
}

class network : public QWidget
{
    Q_OBJECT

public:
    explicit network(QWidget *parent = nullptr);
    ~network();

private:
    Ui::network *ui;
};

#endif // NETWORK_H
