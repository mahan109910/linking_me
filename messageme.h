#ifndef MESSAGEME_H
#define MESSAGEME_H

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QString>
#include "ui_messageme.h" // اضافه کردن این خط

namespace Ui {
class messageme;
}

class messageme : public QWidget
{
    Q_OBJECT

public:
    explicit messageme(const QString &Account_ID, const QString &targetUser, QWidget *parent = nullptr);
    ~messageme();

private slots:
    void sendMessage();
    //void translateUi(bool selectedLanguage);
    void setDarkMode(bool dark);

private:
    Ui::messageme *ui; // تعریف اشاره‌گر به کلاس Ui::MessageMe
    QString Account_ID;
    QString targetUser;

    void loadMessages();
};

#endif // MESSAGEME_H
