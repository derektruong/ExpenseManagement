#include "loan.h"

Loan::Loan()
{

}

int Loan::LayMaTaiKhoanInLoan(QString Username, QString TenTaiKhoan){
    int res = -1;

    this->TenChu = Username;
    this->TenTaiKhoan = TenTaiKhoan;

    QSqlQuery qry;

    if( qry.exec("SELECT MaTaiKhoan FROM TaiKhoan WHERE TenChu = '"+TenChu+"' AND Ten = N'"+TenTaiKhoan+"' ") ){
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

    qry.prepare("UPDATE TaiKhoan SET SoDu = :SoDuNo WHERE MaTaiKhoan = :MaTaiKhoan AND TenChu = :Username; ");

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

    qry.prepare("DELETE lo FROM Loan lo INNER JOIN TaiKhoan tk ON tk.MaTaiKhoan = lo.MaTaiKhoan WHERE tk.TenChu = :Username AND lo.MaTaiKhoan = :MaTaiKhoan ");

    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);
    qry.bindValue(":Username", Username);

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

    qry.prepare("SELECT tk.SoDu FROM Loan lo JOIN TaiKhoan tk ON tk.MaTaiKhoan = lo.MaTaiKhoan WHERE tk.TenChu = :Username AND lo.MaTaiKhoan = :MaTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":MaTaiKhoan", MaTaiKhoan);

    if( qry.exec() ){
        while ( qry.next() ) {
            res = qry.value("TienNo").toLongLong();
        }
    }

    return res;
}
