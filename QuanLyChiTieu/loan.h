#ifndef LOAN_H
#define LOAN_H

#include "quanlytaikhoan.h"

#include <QString>
#include <QStack>
#include <QVector>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>

class Loan : public QuanLyTaiKhoan
{
public:
    Loan();

    void CapNhatDuNo(QString Username, int MaTaiKhoan, lli SoDuNo);

    void XoaNo(QString Username, int MaTaiKhoan);

    void ThemNo(QString TenNo, QString KyHan, int MaTaiKhoan);

    lli KiemTraDuNo(QString Username, int MaTaiKhoan);

private:
    QString TenNo, KyHan;
    lli TienNo;
};

#endif // LOAN_H
