#ifndef CHANGEPIN_H
#define CHANGEPIN_H

#include <QDialog>

#include <expensetracker.h>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QString>

namespace Ui {
class ChangePin;
}

class ChangePin : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePin(QWidget *parent = nullptr);
    ~ChangePin();

    QString Encrypt(QString str);
    QString Decrypt(QString str);

    friend class ExpenseTracker;

protected:
    QString TenDangNhap;

private slots:
    void on_pushButton_XacNhan_clicked();

    void on_pushButton_Huy_clicked();

private:
    Ui::ChangePin *ui;
    QSqlDatabase myDB;

};

#endif // CHANGEPIN_H
