#include "tietkiem.h"

TietKiem::TietKiem()
{

}


int TietKiem::LayMaTaiKhoan(QString Username, QString TenTaiKhoan){
    int res = -1;

    this->TenChu = Username;
    this->TenTaiKhoan = TenTaiKhoan;

    QSqlQuery qry;

    if( qry.exec("SELECT MaTaiKhoan FROM TietKiem WHERE TenChu = '"+TenChu+"' AND Ten = N'"+TenTaiKhoan+"'  ") ){
        while ( qry.next() ) {
            res = qry.value("MaTaiKhoan").toInt();
        }
    }

    else qDebug()<<"Lỗi không kết nối được CSDL!";

    return  res;
}

void TietKiem::CapNhatSoDu(QString Username, int MaTaiKhoan, lli SoDuTK){
    this->TenChu = Username;
    this->MaTaiKhoan = MaTaiKhoan;

    QSqlQuery qry;

    qry.prepare("UPDATE TietKiem SET SoDu = :SoDuTK WHERE MaTaiKhoan = :MaTaiKhoan AND TenChu = :Username; ");

    qry.bindValue(":SoDuTK", SoDuTK);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);
    qry.bindValue(":Username", Username);

    if( !qry.exec() ){
       qDebug()<<"Lỗi không kết nối được CSDL!";
    }
}

void TietKiem::XoaTietKiem(QString Username, int MaTaiKhoan){
    this->TenChu = Username;
    this->MaTaiKhoan = MaTaiKhoan;

    QSqlQuery qry;

    qry.prepare("DELETE FROM TietKiem WHERE TenChu = :Username AND MaTaiKhoan = :MaTaiKhoan ");

    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);
    qry.bindValue(":Username", Username);

    if( !qry.exec() ){
        qDebug()<<"Lỗi không kết nối được CSDL!";
    }

}

void TietKiem::ThemTietKiem(QString Username, QString TenTietKiem, lli SoDu, lli MucTieu, int MaTaiKhoan){
    QSqlQuery qry;

    qry.prepare("INSERT INTO TietKiem ( TenTietKiem, SoDu, MucTieu, MaTaiKhoan, TenChu )" "VALUES (  :TenTietKiem, :SoDu, :MucTieu, :MaTaiKhoan, :TenChu )");

    qry.bindValue(":TenTietKiem", TenTietKiem);
    qry.bindValue(":SoDu", SoDu);
    qry.bindValue(":MucTieu", MucTieu);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);
    qry.bindValue(":TenChu", Username);

    if( !qry.exec() ){
        qDebug()<<"Lỗi không kết nối được CSDL!";
    }

}

lli TietKiem::KiemTraMucTieu(QString Username, int MaTaiKhoan){
    QSqlQuery qry;
    lli res = 0;

    qry.prepare("SELECT SoDu, MucTieu FROM TietKiem WHERE TenChu = :Username AND MaTaiKhoan = :MaTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);

    if( qry.exec() ){
        while ( qry.next() ) {
            res = qry.value("SoDu").toLongLong() - qry.value("MucTieu").toLongLong();
        }
    }

    return res;

}
