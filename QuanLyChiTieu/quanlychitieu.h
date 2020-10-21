#ifndef QUANLYCHITIEU_H
#define QUANLYCHITIEU_H


#include <QString>
#include <QVector>
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

    int LayID_DanhMuc(QString MaDanhMuc, QString Username);

    //Hàm này chỉ được gọi sau khi INSERT vào bảng KhoanChi
    int LayMaKhoanChi();
    //

    lli LaySoTienTong(QString MaDanhMuc, QString Username);

    void XoaTaiKhoanInChiTieu(QString Username, QString TenTaiKhoan );

    QVector<QVector<lli>> LayThongKe7NgayTruoc(QString Username, QString TenDanhMuc, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam);

    QVector<QVector<lli>> LayThongKe30NgayTruoc(QString Username, QString TenDanhMuc, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam);

    QVector<QVector<lli>> LayThongKe3ThangTruoc(QString Username, QString TenDanhMuc, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam);

    QVector<lli> LayThongKe1Nam(QString Username, QString TenDanhMuc, QString TenTaiKhoan, QString Nam);


private:
    QString MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu;
};

#endif // QUANLYCHITIEU_H
