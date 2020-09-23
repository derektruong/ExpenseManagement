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

protected:
    QString TenChu, LoaiThuNhap;
};

#endif // QUANLYTHUNHAP_H
