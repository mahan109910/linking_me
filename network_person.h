#ifndef NETWORK_PERSON_H
#define NETWORK_PERSON_H

#include <QWidget>

namespace Ui {
class network_person;
}

class network_person : public QWidget
{
    Q_OBJECT

public:
    explicit network_person(const QString &username, QWidget *parent = nullptr);
    ~network_person();

private:
    Ui::network_person *ui;
    QString username;
};

#endif // NETWORK_PERSON_H
