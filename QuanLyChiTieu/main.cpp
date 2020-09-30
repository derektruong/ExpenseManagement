#include "loginapp.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlDriverPlugin>




int main(int argc, char *argv[])
{
    QApplication::libraryPaths();
    QApplication a(argc, argv);
    LoginAPP w;
    w.setWindowIcon(QIcon(":/Images\\Icon\\cash-icon.png"));
    w.show();
    return a.exec();
}
