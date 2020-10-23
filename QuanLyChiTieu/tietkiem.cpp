#include "tietkiem.h"

TietKiem::TietKiem()
{

}

lli TietKiem::LayMucTieu(QString Username, QString TenTaiKhoan){
    lli res = -1;

    this->TenChu = Username;
    this->TenTaiKhoan = TenTaiKhoan;

    QSqlQuery qry;

    if( qry.exec("SELECT tkiem.MucTieu FROM TietKiem tkiem JOIN TaiKhoan tk ON tkiem.MaTaiKhoan = tk.MaTaiKhoan WHERE tk.TenChu = '"+TenChu+"' AND tk.Ten = N'"+TenTaiKhoan+"'  ") ){
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

    qry.prepare("UPDATE tkiem SET tkiem.MucTieu = :MucTieu FROM TietKiem tkiem INNER JOIN TaiKhoan tk ON tkiem.MaTaiKhoan = tk.MaTaiKhoan WHERE tkiem.MaTaiKhoan = :MaTaiKhoan AND tk.TenChu = :Username; ");

    qry.bindValue(":MucTieu", MucTieu);
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

    qry.prepare("DELETE tkiem FROM TietKiem tkiem INNER JOIN TaiKhoan tk ON tkiem.MaTaiKhoan = tk.MaTaiKhoan WHERE tk.TenChu = :Username AND tkiem.MaTaiKhoan = :MaTaiKhoan ");

    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);
    qry.bindValue(":Username", Username);

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

    qry.prepare("SELECT tk.SoDu, tkiem.MucTieu FROM TietKiem tkiem JOIN TaiKhoan tk ON tkiem.MaTaiKhoan = tk.MaTaiKhoan WHERE tk.TenChu = :Username AND tkiem.MaTaiKhoan = :MaTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);

    if( qry.exec() ){
        while ( qry.next() ) {
            res = qry.value("SoDu").toLongLong() - qry.value("MucTieu").toLongLong();
        }
    }

    return res;

}
