#ifndef TIETKIEM_H
#define TIETKIEM_H

#include "quanlytaikhoan.h"

#include <QString>
#include <QStack>
#include <QVector>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>


class TietKiem : public QuanLyTaiKhoan
{
public:
    TietKiem();

    lli LayMucTieu(QString Username, QString TenTaiKhoan);

    void CapNhatMucTieu(QString Username, int MaTaiKhoan, lli MucTieu);

    void XoaTietKiem(QString Username, int MaTaiKhoan);

    void ThemTietKiem( QString TenTietKiem, lli MucTieu, int MaTaiKhoan);

    lli KiemTraMucTieu(QString Username, int MaTaiKhoan);
};

#endif // TIETKIEM_H
