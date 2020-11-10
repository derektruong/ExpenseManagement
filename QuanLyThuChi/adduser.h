#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include <loginapp.h>
#include <quanlychitieu.h>


#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>


namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    ~AddUser();
    QString Encrypt(QString str);

private slots:
    void on_pushButton_DangKy_AddUser_clicked();

private:
    Ui::AddUser *ui;
    LoginAPP *login;
    QuanLyChiTieu ChiTieu;
};

#endif // ADDUSER_H
