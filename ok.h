#ifndef OK_H
#define OK_H

#include <QWidget>

namespace Ui {
class ok;
}

class ok : public QWidget
{
    Q_OBJECT

public:
    explicit ok(QWidget *parent = nullptr);
    ~ok();

private:
    Ui::ok *ui;
};

#endif // OK_H
