#ifndef QUANLYTAIKHOAN_H
#define QUANLYTAIKHOAN_H

#include <QString>
#include <QStack>
#include <QVector>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>

typedef qint64 lli;


class QuanLyTaiKhoan
{
public:
    QuanLyTaiKhoan();
    ~QuanLyTaiKhoan(){}

    QString GetLTK(QString LoaiTaiKhoan);
    QString GetTTK(QString TenTaiKhoan);
    lli  LaySoDu(QString Username, QString TenTK);
    void SetLTK(QString LTK);
    void SetTTK(QString TTK);
    void SetSoDu(lli So_Du);

    QString TinhTongSoDu(QString Username);

    QVector<QString> LayTenTaiKhoan(QString Username);
    QVector<QString> LayTenTatCaTaiKhoan(QString Username);
    virtual int LayMaTaiKhoan(QString Username, QString TenTaiKhoan);
    QString LayLoaiTaiKhoan(QString Username, QString TenTaiKhoan);


protected:
    QString LoaiTaiKhoan;
    QString TenTaiKhoan;
    lli SoDu;
    int MaTaiKhoan;
    QString TenChu;

private:
    lli TongSoDu = 0;
    int inTotal = 1;

};

#endif // QUANLYTAIKHOAN_H
