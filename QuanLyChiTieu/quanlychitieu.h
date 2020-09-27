#ifndef QUANLYCHITIEU_H
#define QUANLYCHITIEU_H


#include <QString>
#include <QVector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>

typedef qint64 lli;

class QuanLyChiTieu
{
public:
    QuanLyChiTieu();

    void ThemDanhMucMacDinh(QString Username);

    QString LayMaDanhMuc(QString TenDanhMuc, QString Username);

    lli LaySoTienTong(QString MaDanhMuc, QString Username);

    void XoaTaiKhoanInChiTieu(QString Username, QString TenTaiKhoan );


private:
    QString MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu;
};

#endif // QUANLYCHITIEU_H
