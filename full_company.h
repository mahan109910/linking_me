#ifndef FULL_COMPANY_H
#define FULL_COMPANY_H

#include <QWidget>
#include <QString>

namespace Ui {
class Full_company;
}

class Full_company : public QWidget
{
    Q_OBJECT

public:
    explicit Full_company(const QString &username, QWidget *parent = nullptr);
    ~Full_company();

private:
    Ui::Full_company *ui;
    QString m_username;
    void translateUi();
    void setDarkMode(bool dark);

private slots:
    void on_pushButton_ok_company_clicked();
    void on_pushButton_bake_company_clicked();
};

#endif // FULL_COMPANY_H
