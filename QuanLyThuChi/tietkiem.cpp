#include "tietkiem.h"

TietKiem::TietKiem()
{

}

lli TietKiem::LayMucTieu(QString Username, QString TenTaiKhoan){
    lli res = -1;

    this->TenChu = Username;
    this->TenTaiKhoan = TenTaiKhoan;

    QSqlQuery qry;

    if( qry.exec("SELECT TietKiem.MucTieu FROM TietKiem JOIN TaiKhoan ON TietKiem.MaTaiKhoan = TaiKhoan.MaTaiKhoan WHERE TaiKhoan.TenChu = '"+TenChu+"' AND TaiKhoan.Ten = '"+TenTaiKhoan+"'  ") ){
        while ( qry.next() ) {
            res = qry.value("MucTieu").toLongLong();
        }
    }

    else qDebug()<<"Lỗi không kết nối được CSDL!";

    return  res;
}

void TietKiem::CapNhatMucTieu(QString Username, int MaTaiKhoan, lli MucTieu){
    this->TenChu = Username;
    this->MaTaiKhoan = MaTaiKhoan;

    QSqlQuery qry;

    qry.prepare("UPDATE TietKiem SET MucTieu = :MucTieu WHERE MaTaiKhoan = :MaTaiKhoan ");

    qry.bindValue(":MucTieu", MucTieu);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);

    if( !qry.exec() ){
       qDebug()<<"Lỗi không kết nối được CSDL!";
    }
}

void TietKiem::XoaTietKiem(QString Username, int MaTaiKhoan){
    this->TenChu = Username;
    this->MaTaiKhoan = MaTaiKhoan;

    QSqlQuery qry;

    qry.prepare("DELETE FROM TietKiem  WHERE  TietKiem.MaTaiKhoan = :MaTaiKhoan ");

    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);

    if( !qry.exec() ){
        qDebug()<<"Lỗi không kết nối được CSDL!";
    }

}

void TietKiem::ThemTietKiem( QString TenTietKiem, lli MucTieu, int MaTaiKhoan){
    QSqlQuery qry;

    qry.prepare("INSERT INTO TietKiem ( TenTietKiem, MucTieu, MaTaiKhoan )" "VALUES (  :TenTietKiem, :MucTieu, :MaTaiKhoan )");

    qry.bindValue(":TenTietKiem", TenTietKiem);
    qry.bindValue(":MucTieu", MucTieu);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);

    if( !qry.exec() ){
        qDebug()<<"Lỗi không kết nối được CSDL!";
    }

}

lli TietKiem::KiemTraMucTieu(QString Username, int MaTaiKhoan){
    QSqlQuery qry;
    lli res = 0;

    qry.prepare("SELECT TaiKhoan.SoDu, TietKiem.MucTieu FROM TietKiem JOIN TaiKhoan ON TietKiem.MaTaiKhoan = TaiKhoan.MaTaiKhoan WHERE TaiKhoan.TenChu = :Username AND TietKiem.MaTaiKhoan = :MaTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);

    if( qry.exec() ){
        while ( qry.next() ) {
            res = qry.value("SoDu").toLongLong() - qry.value("MucTieu").toLongLong();
        }
    }

    return res;

}
