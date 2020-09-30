#ifndef LOGINAPP_H
#define LOGINAPP_H

#include <QMainWindow>
#include <expensetracker.h>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlDriverPlugin>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QString>



QT_BEGIN_NAMESPACE
namespace Ui { class LoginAPP; }
QT_END_NAMESPACE

class LoginAPP : public QMainWindow
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDummyPlugin" FILE "F:\TailieuBK\HK3\DALT\QuanLyChiTieu\build-QuanLyChiTieu-Desktop_Qt_5_14_2_MinGW_64_bit-Release\release\sqldrivers\odbc\odbc.json");

public:
    LoginAPP(QWidget *parent = nullptr);
    ~LoginAPP();

    QString Decrypt(QString str);

    friend class ExpenseTracker;// Lớp bạn là lớp ExpenseManagement

protected:
    QString UserName;


private slots:
    void on_pushButton_DangNhap_clicked();

    void on_pushButton_ThemTaiKhoan_clicked();

private:
    Ui::LoginAPP *ui;
    QSqlDatabase myDB;

};
#endif // LOGINAPP_H
