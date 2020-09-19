#include "quanlytaikhoan.h"

QuanLyTaiKhoan::QuanLyTaiKhoan()
{
    //DataBase
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QODBC");

    myDB.setDatabaseName("DRIVER={SQL Server Native Client 11.0};SERVER=DEREKPC;DATABASE=DO_AN_CHI_TIEU;UID=sa;PWD=derek123;WSID=.;Trusted_connection=yes");

    bool connected = myDB.open();

    if(!connected) qDebug()<<"Lỗi không kết nối được CSDL!";
}

QString QuanLyTaiKhoan::GetLTK(QString LoaiTaiKhoan){
    return LoaiTaiKhoan;
}

//Lấy số dư của tài khoản nhất định
lli QuanLyTaiKhoan::LaySoDu(QString Username, QString TenTK){
    lli res = 0;

    this->TenChu = Username;
    this->TenTaiKhoan = TenTK;

    QSqlQuery qry;

    if( qry.exec("SELECT tk.* FROM dbo.TaiKhoan tk WHERE tk.TenChu = '"+TenChu+"' AND tk.Ten = N'"+TenTaiKhoan+"'") ){
        while ( qry.next() ) {
            res += qry.value("SoDu").toLongLong();
        }
    }

    else qDebug()<<"Lỗi không kết nối được CSDL!";

    return  res;
}

void QuanLyTaiKhoan::SetLTK(QString LTK){
    this->LoaiTaiKhoan = LTK;
}

void QuanLyTaiKhoan::SetTTK(QString TTK){
    this->TenTaiKhoan = TTK;
}

//Lấy tổng số dư của tất cả tài khoản có thuộc tính BGTTSD = 1
QString QuanLyTaiKhoan::TinhTongSoDu(QString Username){

    lli num = 0;

    QStack<QChar> st;

    QString res = "";

    this->TenChu = Username;

    QSqlQuery qry;

    if( qry.exec("SELECT tk.* FROM dbo.TaiKhoan tk WHERE tk.TenChu = '"+TenChu+"' AND tk.BaoGomTrongTongSoDu = 1") ){
        while ( qry.next() ) {
            num += qry.value("SoDu").toLongLong();
        }
    }

    else qDebug()<<"Lỗi không kết nối được CSDL!";

    //Hiển thị tiền dễ nhìn hơn với '.'

    res = QString::number(num);

    int cnt = 0, i = res.size() - 1;

    while( i >= 0 ){
        st.push(res[i]);
        cnt++;
        if( !(cnt%3) && i) st.push('.');
        i--;
    }
    res="";
    while( !st.empty() ){
        res+=st.top();
        st.pop();
    }
    //qDebug()<<res;

    return  res;

}


//Lấy tên tài khoản của tài khoản nhất định
QVector<QString> QuanLyTaiKhoan::LayTenTaiKhoan(QString Username){

    QVector<QString> res;

    this->TenChu = Username;

    QSqlQuery qry;

    if( qry.exec("SELECT tk.* FROM dbo.TaiKhoan tk WHERE tk.TenChu = '"+TenChu+"'") ){
        while ( qry.next() ) {
            res.push_back(qry.value("Ten").toString());
        }
    }

    else qDebug()<<"Lỗi không kết nối được CSDL!";

    return  res;
}
