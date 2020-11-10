#include "loan.h"

Loan::Loan()
{

}

void Loan::XoaNo(QString Username, int MaTaiKhoan){
    this->TenChu = Username;
    this->MaTaiKhoan = MaTaiKhoan;

    QSqlQuery qry;

    qry.prepare("DELETE FROM Loan WHERE MaTaiKhoan = :MaTaiKhoan ");

    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);

    if( !qry.exec() ){
        qDebug()<<"Lỗi không kết nối được CSDL!";
    }
}

void Loan::ThemNo(QString TenNo, QString KyHan, int MaTaiKhoan){
    this->TenNo = TenNo;
    this->KyHan = KyHan;
    this->MaTaiKhoan = MaTaiKhoan;

    QSqlQuery qry;

    qry.prepare("INSERT INTO Loan ( TenNo, KyHan, MaTaiKhoan)" "VALUES ( :TenNo, :KyHan, :MaTaiKhoan )");

    qry.bindValue(":TenNo", TenNo);
    qry.bindValue(":KyHan", KyHan);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);

    if( !qry.exec() ){
        qDebug()<<"Lỗi không kết nối được CSDL!";
    }
}

lli Loan::KiemTraDuNo(QString Username, int MaTaiKhoan){
    QSqlQuery qry;
    lli res = 0;

    qry.prepare("SELECT TaiKhoan.SoDu FROM Loan JOIN TaiKhoan ON TaiKhoan.MaTaiKhoan = Loan.MaTaiKhoan WHERE TaiKhoan.TenChu = :Username AND Loan.MaTaiKhoan = :MaTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);

    if( qry.exec() ){
        while ( qry.next() ) {
            res = qry.value("SoDu").toLongLong();
        }
    }

    return res;
}
