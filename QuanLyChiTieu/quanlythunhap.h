#ifndef QUANLYTHUNHAP_H
#define QUANLYTHUNHAP_H

#include <QString>
#include <QVector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>

typedef qint64 lli;

class QuanLyThuNhap
{
public:
    QuanLyThuNhap();
    lli LaySoTienTong(QString Username);

    QVector<QString> LayTenThuNhap(QString Username);

    void XoaLoaiThuNhap(QString Username, QString LoaiThuNhap);

    void XoaTaiKhoanInThuNhap(QString Username, QString TenTaiKhoan );


protected:
    QString TenChu, LoaiThuNhap;
};

#endif // QUANLYTHUNHAP_H
