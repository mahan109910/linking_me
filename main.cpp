#include "welcome.h"
#include "singin.h"
#include "login.h"
#include <QApplication>

int selectedLanguage = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    welcome w;
    w.show();
    return a.exec();
}
