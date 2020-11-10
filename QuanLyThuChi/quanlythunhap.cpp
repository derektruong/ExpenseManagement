#include "quanlythunhap.h"

QuanLyThuNhap::QuanLyThuNhap()
{

}

lli QuanLyThuNhap::LaySoTienTong(QString Username, int MaThuNhap){

    this->TenChu = Username;
    lli res = 0;

    QSqlQuery qry;
    if( MaThuNhap < 0 )
        qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username ");
    else {
        qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND ThuNhap.MaThuNhap = :MaThuNhap ");
    }

    qry.bindValue(":MaThuNhap", MaThuNhap);
    qry.bindValue(":Username", Username);

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

//LoaiThuNhap
int QuanLyThuNhap::LayMaLoaiThuNhap(QString Username, QString LoaiThuNhap){
    int res = 0;

    QSqlQuery qry;

    qry.prepare("SELECT LoaiThuNhap.MaLoaiThuNhap FROM LoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND LoaiThuNhap.LoaiThuNhap = :LoaiThuNhap");

    qry.bindValue(":Username", Username);
    qry.bindValue(":LoaiThuNhap", LoaiThuNhap);
    if( qry.exec() ){
        while ( qry.next() ) {
            res = qry.value("MaLoaiThuNhap").toInt();
        }
    }
    return res;
}

//Hàm này chỉ được gọi sau khi INSERT vào bảng LoaiThuNhap
int QuanLyThuNhap::LayMaThuNhap(){
    int res = 0;

    QSqlQuery qry;

    if( qry.exec("SELECT MaThuNhap FROM ThuNhap WHERE MaThuNhap = SCOPE_IDENTITY()") ){
        while ( qry.next() ) {
            res = qry.value("MaThuNhap").toInt();
            qDebug()<<res;
        }
    }
    return res;
}
//

//LoaiThuNhap
void QuanLyThuNhap::XoaLoaiThuNhap(QString Username, QString LoaiThuNhap){
    this->TenChu = Username;
    this->LoaiThuNhap = LoaiThuNhap;

    QSqlQuery qry;
    //Xoá trong bảng ThuNhap

    qry.prepare("DELETE ThuNhap FROM ThuNhap INNER JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND LoaiThuNhap.LoaiThuNhap = :LoaiThuNhap");

    qry.bindValue(":Username", Username);
    qry.bindValue(":LoaiThuNhap", LoaiThuNhap);

    if( !qry.exec() ){
       qDebug()<<"Lỗi không kết nối được CSDL!";
    }

    //Xoá trong bảng LoaiThuNhap

    qry.prepare("DELETE FROM LoaiThuNhap WHERE TenChu = :Username AND LoaiThuNhap = :LoaiThuNhap");

    qry.bindValue(":Username", Username);
    qry.bindValue(":LoaiThuNhap", LoaiThuNhap);

    if( !qry.exec() ){
       qDebug()<<"Lỗi không kết nối được CSDL!";
    }


}

void QuanLyThuNhap::XoaTaiKhoanInThuNhap(QString Username, QString TenTaiKhoan ){
    QVector< int > MaThuNhap;
    QSqlQuery qry;

    qry.prepare("SELECT ThuNhap.MaThuNhap FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND ThuNhap.TenTaiKhoan = :TenTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":TenTaiKhoan", TenTaiKhoan);

    if( qry.exec() ){

        while( qry.next() ){
            MaThuNhap.push_back( qry.value("MaThuNhap").toInt() );
        }
    }
    //Xoá trong bảng ThuNhap

    qry.prepare("DELETE ThuNhap FROM ThuNhap INNER JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND ThuNhap.TenTaiKhoan = :TenTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":TenTaiKhoan", TenTaiKhoan);

    if( !qry.exec() ){
       qDebug()<<"Lỗi không kết nối được CSDL!";
    }

    //Xoá trong thống kê
    for( int i = 0; i < MaThuNhap.size(); ++i ){
        qry.prepare("DELETE FROM ThongKe WHERE MaThuNhap = :MaThuNhap");

        qry.bindValue(":MaThuNhap", MaThuNhap[i]);
        qry.exec();
    }
}

QVector<QVector<lli>> QuanLyThuNhap::LayThongKe7NgayTruoc(QString Username, QString LoaiThuNhap, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam){
    QVector<QVector<lli>> res = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    QVector<int> DayOfMon = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int day = Ngay.toInt();
    int month = Thang.toInt();
    int year = Nam.toInt();

    if( !(year%100) )
        DayOfMon[2] = (!(Nam.toInt()%400)) ? 29 : 28;
    else
        DayOfMon[2] = (!(Nam.toInt()%4)) ? 29 : 28;


    QSqlQuery qry;

    for( int i = day, cnt = 7; cnt > 0; --i, --cnt ){
        if( !i ){
            month--;
            if( !month ){
                month = 12;
                year--;
            }
            i = DayOfMon[month];
        }

        if( LoaiThuNhap == "Tất Cả" && TenTaiKhoan == "Tất Cả" )
            qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year");
        if( LoaiThuNhap != "Tất Cả" && TenTaiKhoan == "Tất Cả" )
            qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND LoaiThuNhap.LoaiThuNhap = :LoaiThuNhap");
        if( LoaiThuNhap == "Tất Cả" && TenTaiKhoan != "Tất Cả" )
            qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND ThuNhap.TenTaiKhoan = :TenTaiKhoan");
        if( LoaiThuNhap != "Tất Cả" && TenTaiKhoan != "Tất Cả" )
            qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND LoaiThuNhap.LoaiThuNhap = :LoaiThuNhap AND ThuNhap.TenTaiKhoan = :TenTaiKhoan");

        qry.bindValue(":Username", Username);
        qry.bindValue(":day", QString::number(i));
        qry.bindValue(":month", QString::number(month));
        qry.bindValue(":year", QString::number(year));
        qry.bindValue(":LoaiThuNhap", LoaiThuNhap);
        qry.bindValue(":TenTaiKhoan", TenTaiKhoan);

        res[cnt][0] = i;
        res[cnt][1] = month;

        if( qry.exec() ){
            while ( qry.next() ) {
                //qDebug()<<qry.value("SoTien").toLongLong()<<" ";
                res[cnt][2] += qry.value("SoTien").toLongLong();
            }
        }
        else qDebug()<<"Lỗi không kết nối được CSDL!";
    }

    return res;
}

QVector<QVector<lli>> QuanLyThuNhap::LayThongKe30NgayTruoc(QString Username, QString LoaiThuNhap, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam){
    QVector<QVector<lli>> res = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    QVector<int> DayOfMon = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int day = Ngay.toInt();
    int month = Thang.toInt();
    int year = Nam.toInt();

    if( !(year%100) )
        DayOfMon[2] = (!(Nam.toInt()%400)) ? 29 : 28;
    else
        DayOfMon[2] = (!(Nam.toInt()%4)) ? 29 : 28;


    QSqlQuery qry;

    int i = day, cnt = 10;

    while( cnt ){
        int day_begin;
        int month_begin;
        for( int cntDay = 3; cntDay > 0; --cntDay ){
            //Kiểm tra hợp lệ ngày tháng
            if( !i ){
                month--;
                if( !month ){
                    month = 12;
                    year--;
                }
                i = DayOfMon[month];
            }
            if( cntDay == 3 ){
                day_begin = i;
                month_begin = month;
            }

            //Xử lý query tuỳ theo trường hợp
            if( LoaiThuNhap == "Tất Cả" && TenTaiKhoan == "Tất Cả" )
                qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year");
            if( LoaiThuNhap != "Tất Cả" && TenTaiKhoan == "Tất Cả" )
                qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND LoaiThuNhap.LoaiThuNhap = :LoaiThuNhap");
            if( LoaiThuNhap == "Tất Cả" && TenTaiKhoan != "Tất Cả" )
                qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND ThuNhap.TenTaiKhoan = :TenTaiKhoan");
            if( LoaiThuNhap != "Tất Cả" && TenTaiKhoan != "Tất Cả" )
                qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND LoaiThuNhap.LoaiThuNhap = :LoaiThuNhap AND ThuNhap.TenTaiKhoan = :TenTaiKhoan");

            qry.bindValue(":Username", Username);
            qry.bindValue(":day", QString::number(i));
            qry.bindValue(":month", QString::number(month));
            qry.bindValue(":year", QString::number(year));
            qry.bindValue(":LoaiThuNhap", LoaiThuNhap);
            qry.bindValue(":TenTaiKhoan", TenTaiKhoan);

            if( qry.exec() ){
                while ( qry.next() ) {
                    res[cnt][3] += qry.value("SoTien").toLongLong();
                }
            }
            else qDebug()<<"Lỗi không kết nối được CSDL!";
            //trừ ngày đi 1
            if( cntDay - 1 == 0 ){
                int day_end = i;
                res[cnt][0] = day_end;
                res[cnt][1] = day_begin;
                res[cnt][2] = month_begin;
            }
            i--;
        }
        cnt--;

    }

    return  res;
}

QVector<QVector<lli>> QuanLyThuNhap::LayThongKe3ThangTruoc(QString Username, QString LoaiThuNhap, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam){
    QVector<QVector<lli>> res = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    QVector<int> DayOfMon = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int day = Ngay.toInt();
    int month = Thang.toInt();
    int year = Nam.toInt();

    if( !(year%100) )
        DayOfMon[2] = (!(Nam.toInt()%400)) ? 29 : 28;
    else
        DayOfMon[2] = (!(Nam.toInt()%4)) ? 29 : 28;


    QSqlQuery qry;

    int i = day, cnt = 10;

    while( cnt ){
        int day_begin;
        int month_begin;
        for( int cntDay = 10; cntDay > 0; --cntDay ){
            //Kiểm tra hợp lệ ngày tháng
            if( !i ){
                month--;
                if( !month ){
                    month = 12;
                    year--;
                }
                i = DayOfMon[month];
            }
            if( cntDay == 10 ){
                day_begin = i;
                month_begin = month;
            }
            //Xử lý query tuỳ theo trường hợp
            if( LoaiThuNhap == "Tất Cả" && TenTaiKhoan == "Tất Cả" )
                qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year");
            if( LoaiThuNhap != "Tất Cả" && TenTaiKhoan == "Tất Cả" )
                qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND LoaiThuNhap.LoaiThuNhap = :LoaiThuNhap");
            if( LoaiThuNhap == "Tất Cả" && TenTaiKhoan != "Tất Cả" )
                qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND ThuNhap.TenTaiKhoan = :TenTaiKhoan");
            if( LoaiThuNhap != "Tất Cả" && TenTaiKhoan != "Tất Cả" )
                qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%d', ThuNhap.NgayThuNhap) =:day AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND LoaiThuNhap.LoaiThuNhap = :LoaiThuNhap AND ThuNhap.TenTaiKhoan = :TenTaiKhoan");

            qry.bindValue(":Username", Username);
            qry.bindValue(":day", QString::number(i));
            qry.bindValue(":month", QString::number(month));
            qry.bindValue(":year", QString::number(year));
            qry.bindValue(":LoaiThuNhap", LoaiThuNhap);
            qry.bindValue(":TenTaiKhoan", TenTaiKhoan);

            if( qry.exec() ){
                while ( qry.next() ) {
                    res[cnt][3] += qry.value("SoTien").toLongLong();
                }
            }
            else qDebug()<<"Lỗi không kết nối được CSDL!";
            //trừ ngày đi 1
            if( cntDay - 1 == 0 ){
                int day_end = i;
                res[cnt][0] = day_end;
                res[cnt][1] = day_begin;
                res[cnt][2] = month_begin;
            }
            i--;
        }
        cnt--;

    }

    return  res;
}

QVector<lli> QuanLyThuNhap::LayThongKe1Nam(QString Username, QString LoaiThuNhap, QString TenTaiKhoan, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int year = Nam.toInt();

    QSqlQuery qry;

    for( int i = 12; i > 0; --i ){
        //Xử lý query tuỳ theo trường hợp
        if( LoaiThuNhap == "Tất Cả" && TenTaiKhoan == "Tất Cả" )
            qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year");
        if( LoaiThuNhap != "Tất Cả" && TenTaiKhoan == "Tất Cả" )
            qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND LoaiThuNhap.LoaiThuNhap = :LoaiThuNhap");
        if( LoaiThuNhap == "Tất Cả" && TenTaiKhoan != "Tất Cả" )
            qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND ThuNhap.TenTaiKhoan = :TenTaiKhoan");
        if( LoaiThuNhap != "Tất Cả" && TenTaiKhoan != "Tất Cả" )
            qry.prepare("SELECT ThuNhap.SoTien FROM ThuNhap JOIN LoaiThuNhap ON ThuNhap.MaLoaiThuNhap = LoaiThuNhap.MaLoaiThuNhap WHERE LoaiThuNhap.TenChu = :Username AND strftime('%m', ThuNhap.NgayThuNhap) = :month AND strftime('%Y', ThuNhap.NgayThuNhap) = :year AND LoaiThuNhap.LoaiThuNhap = :LoaiThuNhap AND ThuNhap.TenTaiKhoan = :TenTaiKhoan");

        qry.bindValue(":Username", Username);
        qry.bindValue(":month", QString::number(i));
        qry.bindValue(":year", QString::number(year));
        qry.bindValue(":LoaiThuNhap", LoaiThuNhap);
        qry.bindValue(":TenTaiKhoan", TenTaiKhoan);

        if( qry.exec() ){
            while ( qry.next() ) {
                res[i] += qry.value("SoTien").toLongLong();
            }
        }
        else qDebug()<<"Lỗi không kết nối được CSDL!";
    }

    return res;
}
