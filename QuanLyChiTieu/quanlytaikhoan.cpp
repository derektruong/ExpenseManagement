#include "quanlytaikhoan.h"

QuanLyTaiKhoan::QuanLyTaiKhoan()
{

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

    if( qry.exec("SELECT * FROM TaiKhoan WHERE TenChu = '"+TenChu+"' AND Ten = N'"+TenTaiKhoan+"'") ){
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

    if( qry.exec("SELECT * FROM dbo.TaiKhoan WHERE TenChu = '"+TenChu+"' AND BaoGomTrongTongSoDu = 1") ){
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


//Lấy tên tài khoản của tài khoản có trong tổng số dư
QVector<QString> QuanLyTaiKhoan::LayTenTaiKhoan(QString Username){

    QVector<QString> res;

    this->TenChu = Username;

    QSqlQuery qry;

    if( qry.exec("SELECT * FROM TaiKhoan WHERE TenChu = '"+TenChu+"' AND BaoGomTrongTongSoDu = 1") ){
        while ( qry.next() ) {
            res.push_back(qry.value("Ten").toString());
        }
    }

    else qDebug()<<"Lỗi không kết nối được CSDL!";

    return  res;
}
//Lấy tên tài khoản của tài khoản có trong tổng số dư

QVector<QString> QuanLyTaiKhoan::LayTenTatCaTaiKhoan(QString Username){

    QVector<QString> res;

    this->TenChu = Username;

    QSqlQuery qry;

    if( qry.exec("SELECT Ten FROM TaiKhoan WHERE TenChu = '"+TenChu+"'") ){
        while ( qry.next() ) {
            res.push_back(qry.value("Ten").toString());
        }
    }

    else qDebug()<<"Lỗi không kết nối được CSDL!";

    return  res;
}

int QuanLyTaiKhoan::LayMaTaiKhoan(QString Username, QString TenTaiKhoan){
    int res = -1;

    this->TenChu = Username;
    this->TenTaiKhoan = TenTaiKhoan;

    QSqlQuery qry;

    if( qry.exec("SELECT MaTaiKhoan FROM TaiKhoan WHERE TenChu = '"+TenChu+"' AND Ten = N'"+TenTaiKhoan+"'  ") ){
        while ( qry.next() ) {
            res = qry.value("MaTaiKhoan").toInt();
        }
    }

    else qDebug()<<"Lỗi không kết nối được CSDL!";

    return  res;

}


QString QuanLyTaiKhoan::LayLoaiTaiKhoan(QString Username, QString TenTaiKhoan){
    QString res = "";

    this->TenChu = Username;
    this->TenTaiKhoan = TenTaiKhoan;

    QSqlQuery qry;

    if( qry.exec("SELECT Loai FROM TaiKhoan WHERE TenChu = '"+TenChu+"' AND Ten = N'"+TenTaiKhoan+"'  ") ){
        while ( qry.next() ) {
            res = qry.value("Loai").toString();
        }
    }

    else qDebug()<<"Lỗi không kết nối được CSDL!";

    return  res;
}
