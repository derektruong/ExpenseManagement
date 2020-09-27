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

    int LayMaTaiKhoan(QString Username, QString TenTaiKhoan);

    lli LayMucTieu(QString Username, QString TenTaiKhoan);

    void CapNhatMucTieu(QString Username, int MaTaiKhoan, lli MucTieu);

    void CapNhatSoDu(QString Username, int MaTaiKhoan, lli SoDuTK);

    void XoaTietKiem(QString Username, int MaTaiKhoan);

    void ThemTietKiem(QString Username, QString TenTietKiem, lli SoDu, lli MucTieu, int MaTaiKhoan);

    lli KiemTraMucTieu(QString Username, int MaTaiKhoan);
};

#endif // TIETKIEM_H
