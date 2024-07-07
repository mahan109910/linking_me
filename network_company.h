#ifndef NETWORK_COMPANY_H
#define NETWORK_COMPANY_H

#include <QWidget>

namespace Ui {
class network_company;
}

class network_company : public QWidget
{
    Q_OBJECT

public:
    explicit network_company(const QString &username, QWidget *parent = nullptr);
    ~network_company();

private:
    Ui::network_company *ui;
    QString username;
};

#endif // NETWORK_COMPANY_H
