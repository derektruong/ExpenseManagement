#ifndef QUANLYCHITIEU_H
#define QUANLYCHITIEU_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>

typedef long long int lli;

class QuanLyChiTieu
{
public:
    QuanLyChiTieu();

    void ThemDanhMucMacDinh(QString Username);

    QString LayMaDanhMuc(QString TenDanhMuc, QString Username);

    lli LaySoTienTong(QString MaDanhMuc, QString Username);


private:
    QString MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu;
};

#endif // QUANLYCHITIEU_H
