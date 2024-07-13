#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include "messageme.h"
#include <QString>
#include <QSqlDatabase>

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

    void on_pushButton_network_home_clicked();

    void on_pushButton_job_home_clicked();

    void on_pushButton_home_home_clicked();

private:
    Ui::message *ui;
    QString Account_ID;
    QStackedWidget *stackedWidget;
    bool isCompany;
    QSqlDatabase db;
};

#endif // MESSAGE_H
