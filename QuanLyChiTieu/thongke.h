#ifndef THONGKE_H
#define THONGKE_H

#include <QString>
#include <QVector>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>

typedef qint64 lli;

class ThongKe
{
public:
    ThongKe();

    void CapNhatTongThu(QString Username, QString ThoiGian, lli SoTien );

    void CapNhatTongChi(QString Username, QString ThoiGian, lli SoTien );

    QVector<lli> LayDuLieuTongThuTheoTuan(QString Username, QString Thang, QString Nam);

    QVector<lli> LayDuLieuTongChiTheoTuan(QString Username, QString Thang, QString Nam);



private:
    QString TenChu, ThoiGian;
};

#endif // THONGKE_H
