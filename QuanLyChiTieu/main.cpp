#include "loginapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginAPP w;
    w.setWindowIcon(QIcon(":/Images\\Icon\\cash-icon.png"));
    w.show();
    return a.exec();
}
