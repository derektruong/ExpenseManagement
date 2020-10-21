#ifndef QUANLYTHUNHAP_H
#define QUANLYTHUNHAP_H

#include <QString>
#include <QVector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>

typedef long long int lli;

class QuanLyThuNhap
{
public:
    QuanLyThuNhap();
    lli LaySoTienTong(QString Username);

    QVector<QString> LayTenThuNhap(QString Username);

    int LayMaLoaiThuNhap(QString Username, QString LoaiThuNhap);

    void XoaLoaiThuNhap(QString Username, QString LoaiThuNhap);

    void XoaTaiKhoanInThuNhap(QString Username, QString TenTaiKhoan );

    QVector<QVector<lli>> LayThongKe7NgayTruoc(QString Username, QString LoaiThuNhap, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam);

    QVector<QVector<lli>> LayThongKe30NgayTruoc(QString Username, QString LoaiThuNhap, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam);

    QVector<QVector<lli>> LayThongKe3ThangTruoc(QString Username, QString LoaiThuNhap, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam);

    QVector<lli> LayThongKe1Nam(QString Username, QString LoaiThuNhap, QString TenTaiKhoan, QString Nam);

protected:
    QString TenChu, LoaiThuNhap, TenTaiKhoan;
};

#endif // QUANLYTHUNHAP_H
