#ifndef SERCH_H
#define SERCH_H

#include <QWidget>
#include <QString>

namespace Ui {
class serch;
}

class serch : public QWidget
{
    Q_OBJECT

public:
    explicit serch(const QString &Account_ID, const QString &searchText, QWidget *parent = nullptr);
    ~serch();

private slots:
    void onUserSelected(const QString &selectedUserID);

private:
    Ui::serch *ui;
    QString Account_ID;
    QString searchText;
};

#endif // SERCH_H
