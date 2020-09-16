#include "loginapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginAPP w;
    w.show();
    return a.exec();
}
