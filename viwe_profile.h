#ifndef VIWE_PROFILE_H
#define VIWE_PROFILE_H

#include <QSqlDatabase>
#include <QWidget>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include "account.h"

namespace Ui {class viwe_profile;}

class viwe_profile : public QWidget
{
    Q_OBJECT

public:
    explicit viwe_profile(const QString &myAccountID, const QString &selectedUserID, QWidget *parent = nullptr);
    ~viwe_profile();

private slots:
    void translateUi(bool selectedLanguage);
    void setDarkMode(bool dark);


private:
    Ui::viwe_profile *ui;
    QString myAccountID;
    QString selectedUserID;
    bool isCompany;
    QSqlDatabase db;
    QStringList skillsList;
    QByteArray profilePicture;

};

#endif // VIWE_PROFILE_H
