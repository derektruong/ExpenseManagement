#ifndef THONGKE_H
#define THONGKE_H

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

    void CapNhatTongThu(QString Username, QString ThoiGian, lli SoTien );

    void CapNhatTongChi(QString Username, QString ThoiGian, lli SoTien );

    QVector<lli> LayDuLieuTongThuTheoTuan(QString Username, QString Thang, QString Nam);

    QVector<lli> LayDuLieuTongChiTheoTuan(QString Username, QString Thang, QString Nam);

    QVector<lli> LayDuLieuTongThuTheoNam(QString Username, QString Nam);

    QVector<lli> LayDuLieuTongChiTheoNam(QString Username, QString Nam);

    QVector<lli> LayDuLieuCanDoiTheoTuan(QString Username, QString Thang, QString Nam);

    QVector<lli> LayDuLieuCanDoiTheoNam(QString Username, QString Nam);



private:
    QString TenChu, ThoiGian;
};

#endif // THONGKE_H
