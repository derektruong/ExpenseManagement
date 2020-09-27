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

void QuanLyThuNhap::XoaLoaiThuNhap(QString Username, QString LoaiThuNhap){
    this->TenChu = Username;
    this->LoaiThuNhap = LoaiThuNhap;

    QSqlQuery qry;

    //Xoá trong bảng LoaiThuNhap

    qry.prepare("DELETE FROM LoaiThuNhap WHERE TenChu = :Username AND LoaiThuNhap = :LoaiThuNhap");

    qry.bindValue(":Username", Username);
    qry.bindValue(":LoaiThuNhap", LoaiThuNhap);

    if( !qry.exec() ){
       qDebug()<<"Lỗi không kết nối được CSDL!";
    }

    //Xoá trong bảng ThuNhap

    qry.prepare("DELETE FROM ThuNhap WHERE TenChu = :Username AND LoaiThuNhap = :LoaiThuNhap");

    qry.bindValue(":Username", Username);
    qry.bindValue(":LoaiThuNhap", LoaiThuNhap);

    if( !qry.exec() ){
       qDebug()<<"Lỗi không kết nối được CSDL!";
    }

}

void QuanLyThuNhap::XoaTaiKhoanInThuNhap(QString Username, QString TenTaiKhoan ){
    QSqlQuery qry;

    //Xoá trong bảng ThuNhap

    qry.prepare("DELETE FROM ThuNhap WHERE TenChu = :Username AND TenTaiKhoan = :TenTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":TenTaiKhoan", TenTaiKhoan);

    if( !qry.exec() ){
       qDebug()<<"Lỗi không kết nối được CSDL!";
    }
}
