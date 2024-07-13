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
    void setDarkMode(bool dark);
    void sendMessage();
    void sendImage();
    void sendAudio();
    void sendVideo();
    void displayMessage(const QString &senderId, const QString &content, const QString &contentType);

private:
    Ui::messageme *ui;
    QString Account_ID;
    QString targetUser;

    void loadMessages();
    void sendFile(const QString &filePath, const QString &fileType); // افزودن این خط

};

#endif // MESSAGEME_H
