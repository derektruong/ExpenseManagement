#include "loan.h"

Loan::Loan()
{

}

int Loan::LayMaTaiKhoan(QString Username, QString TenTaiKhoan){
    int res = -1;

    this->TenChu = Username;
    this->TenTaiKhoan = TenTaiKhoan;

    QSqlQuery qry;

    if( qry.exec("SELECT MaTaiKhoan FROM Loan WHERE TenChu = '"+TenChu+"' AND Ten = N'"+TenTaiKhoan+"' ") ){
        while ( qry.next() ) {
            res = qry.value("MaTaiKhoan").toInt();
        }
    }

    else qDebug()<<"Lỗi không kết nối được CSDL!";

    return  res;
}

void Loan::CapNhatDuNo(QString Username, int MaTaiKhoan, lli SoDuNo){
    this->TenChu = Username;
    this->MaTaiKhoan = MaTaiKhoan;

    QSqlQuery qry;

    qry.prepare("UPDATE Loan SET TienNo = :SoDuNo WHERE MaTaiKhoan = :MaTaiKhoan AND TenChu = :Username; ");

    qry.bindValue(":SoDuNo", SoDuNo);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);
    qry.bindValue(":Username", Username);

    if( !qry.exec() ){
       qDebug()<<"Lỗi không kết nối được CSDL!";
    }
}

void Loan::XoaNo(QString Username, int MaTaiKhoan){
    this->TenChu = Username;
    this->MaTaiKhoan = MaTaiKhoan;

    QSqlQuery qry;

    qry.prepare("DELETE FROM Loan WHERE TenChu = :Username AND MaTaiKhoan = :MaTaiKhoan ");

    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);
    qry.bindValue(":Username", Username);

    if( !qry.exec() ){
        qDebug()<<"Lỗi không kết nối được CSDL!";
    }
}

void Loan::ThemNo(QString Username, QString TenNo, lli TienNo, QString KyHan, int MaTaiKhoan){
    this->TenChu = Username;
    this->TenNo = TenNo;
    this->TienNo = TienNo;
    this->KyHan = KyHan;
    this->MaTaiKhoan = MaTaiKhoan;

    QSqlQuery qry;

    qry.prepare("INSERT INTO Loan ( TenNo, TienNo, KyHan, MaTaiKhoan, TenChu )" "VALUES ( :TenNo, :TienNo, :KyHan, :MaTaiKhoan, :TenChu )");

    qry.bindValue(":TenNo", TenNo);
    qry.bindValue(":TienNo", TienNo);
    qry.bindValue(":KyHan", KyHan);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);
    qry.bindValue(":TenChu", Username);

    if( !qry.exec() ){
        qDebug()<<"Lỗi không kết nối được CSDL!";
    }
}

lli Loan::KiemTraDuNo(QString Username, int MaTaiKhoan){
    QSqlQuery qry;
    lli res = 0;

    qry.prepare("SELECT TienNo FROM Loan WHERE TenChu = :Username AND MaTaiKhoan = :MaTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);

    if( qry.exec() ){
        while ( qry.next() ) {
            res = qry.value("TienNo").toLongLong();
        }
    }

    return res;
}
