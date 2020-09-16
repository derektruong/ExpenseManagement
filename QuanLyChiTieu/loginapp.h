#ifndef LOGINAPP_H
#define LOGINAPP_H

#include <QMainWindow>
#include <expensetracker.h>

#include <QtSql/QSqlDatabase>
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

public:
    LoginAPP(QWidget *parent = nullptr);
    ~LoginAPP();

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
