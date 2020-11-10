#include "loginapp.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlDriverPlugin>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath(a.applicationDirPath() + "/sqldrivers");
    LoginAPP w;
    w.setWindowIcon(QIcon(":/Images\\Icon\\cash-icon.png"));
    w.show();
    return a.exec();
}
