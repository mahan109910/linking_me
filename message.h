#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include "messageme.h"

namespace Ui {
class message;
}

class message : public QWidget
{
    Q_OBJECT

public:
    explicit message(const QString &Account_ID, QWidget *parent = nullptr);
    ~message();

private slots:
    void openChat(QListWidgetItem *item);

private:
    Ui::message *ui;
    QString Account_ID;
    QStackedWidget *stackedWidget;
};

#endif // MESSAGE_H
