#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>

namespace Ui {
class message;
}

class message : public QWidget
{
    Q_OBJECT

public:
    explicit message(const QString &username, QWidget *parent = nullptr);
    ~message();

private:
    Ui::message *ui;
    QString username;
};

#endif // MESSAGE_H
