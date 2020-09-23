#include "quanlythunhap.h"

QuanLyThuNhap::QuanLyThuNhap()
{

}

lli QuanLyThuNhap::LaySoTienTong(QString Username){

    this->TenChu = Username;
    lli res = 0;

    QSqlQuery qry;

    qry.prepare("SELECT SoTien FROM ThuNhap WHERE TenChu = :Username ");

    if( qry.exec() ){

        while ( qry.next() ) {
            res += qry.value("SoTien").toLongLong();
        }
    }
    else{
        qDebug()<<"Loi CSDL";
        return -1;
    }

    return res;
}

QVector<QString> QuanLyThuNhap::LayTenThuNhap(QString Username){

    this->TenChu = Username;

    QVector<QString> res;

    QSqlQuery qry;

    if( qry.exec("SELECT LoaiThuNhap FROM LoaiThuNhap WHERE TenChu = '"+this->TenChu+"'") ){
        while ( qry.next() ) {
            res.push_back(qry.value("LoaiThuNhap").toString());
        }
    }

    else qDebug()<<"Lỗi không kết nối được CSDL!";

    return  res;
}
