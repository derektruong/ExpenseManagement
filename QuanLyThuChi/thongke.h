#ifndef THONGKE_H
#define THONGKE_H

#include "quanlythunhap.h"
#include "quanlychitieu.h"

#include <QString>
#include <QVector>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>

typedef long long int lli;

class ThongKe
{
public:
    ThongKe();

    QVector<lli> LayDuLieuTongThuTheoTuan(QString Username, QString Thang, QString Nam);

    QVector<lli> LayDuLieuTongChiTheoTuan(QString Username, QString Thang, QString Nam);

    QVector<lli> LayDuLieuTongThuTheoNam(QString Username, QString Nam);

    QVector<lli> LayDuLieuTongChiTheoNam(QString Username, QString Nam);

    QVector<lli> LayDuLieuCanDoiTheoTuan(QString Username, QString Thang, QString Nam);

    QVector<lli> LayDuLieuCanDoiTheoNam(QString Username, QString Nam);

private:
    QString TenChu, ThoiGian;
    QuanLyChiTieu ChiTieuQL;
    QuanLyThuNhap ThuNhapQL;
};

#endif // THONGKE_H
