#ifndef SERCH_H
#define SERCH_H

#include <QWidget>

namespace Ui {
class serch;
}

class serch : public QWidget
{
    Q_OBJECT

public:
    explicit serch(const QString &serchv,QWidget *parent = nullptr);
    ~serch();

private:
    Ui::serch *ui;
    QString serchv;
};

#endif // SERCH_H
