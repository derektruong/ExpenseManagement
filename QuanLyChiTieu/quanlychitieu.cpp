#include "quanlychitieu.h"


QuanLyChiTieu::QuanLyChiTieu()
{


}

void QuanLyChiTieu::ThemDanhMucMacDinh(QString Username){
    this->TenChu = Username;

    QSqlQuery qry;

    qry.exec("INSERT DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'BH',  N'Bách Hoá',  0,  N'Đồ gia dụng, đồ chơi, đồ gia dụng,...',  '"+TenChu+"'  )");
    qry.exec("INSERT DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'DC',  N'Di Chuyển',  0,  N'Xăng, vé xe,...',  '"+TenChu+"'  )");
    qry.exec("INSERT DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'GD',  N'Gia Đình',  0,  N'Chi phí gia đình, nội thất,...',  '"+TenChu+"'  )");
    qry.exec("INSERT DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'GT',  N'Giải Trí',  0,  N'Xem phim, du lịch,...',  '"+TenChu+"'  )");
    qry.exec("INSERT DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'HD',  N'Hoá Đơn',  0,  N'Hoá đơn điện, nước, internet, cáp truyền hình,...',  '"+TenChu+"'  )");
    qry.exec("INSERT DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'HP',  N'Học Phí',  0,  N'Học phí',  '"+TenChu+"'  )");
    qry.exec("INSERT DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'KD',  N'Kinh Doanh',  0,  N'Chi phí kinh tế',  '"+TenChu+"'  )");
    qry.exec("INSERT DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'MS',  N'Mua Sắm',  0,  N'Quần áo, phụ kiện, mỹ phẩm,...',  '"+TenChu+"'  )");
    qry.exec("INSERT DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'OT',  N'Khác',  0,  N'Mục khác,...',  '"+TenChu+"'  )");
    qry.exec("INSERT DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'QT',  N'Quà Tặng',  0,  N'Quà tặng,...',  '"+TenChu+"'  )");
    qry.exec("INSERT DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'SK',  N'Sức Khoẻ',  0,  N'Thuốc, dược phẩm,...',  '"+TenChu+"'  )");

}

//DMCT
QString QuanLyChiTieu::LayMaDanhMuc(QString TenDanhMuc, QString Username){
    QString MDM;

    this->TenChu = Username;

    QSqlQuery qry;

    if( qry.exec("SELECT MaDanhMuc FROM DanhMucChiTieu WHERE TenDanhMuc = N'"+TenDanhMuc+"' AND TenChu = '"+Username+"'") ){
        while ( qry.next() ) {
            MDM = qry.value("MaDanhMuc").toString();
        }
    }
    return MDM;

}
//DMCT
int QuanLyChiTieu::LayID_DanhMuc(QString MaDanhMuc, QString Username){
    int res = 0;

    this->TenChu = Username;

    QSqlQuery qry;

    if( qry.exec("SELECT ID_DanhMuc FROM DanhMucChiTieu WHERE MaDanhMuc = '"+MaDanhMuc+"' AND TenChu = '"+Username+"'") ){
        while ( qry.next() ) {
            res = qry.value("ID_DanhMuc").toInt();
        }
    }
    return res;

}

//Hàm này chỉ được gọi sau khi INSERT vào bảng KhoanChi
int QuanLyChiTieu::LayMaKhoanChi(){
    int res = 0;

    QSqlQuery qry;

    if( qry.exec("SELECT MaKhoanChi FROM KhoanChi WHERE MaKhoanChi = SCOPE_IDENTITY()") ){
        while ( qry.next() ) {
            res = qry.value("MaKhoanChi").toInt();
        }
    }
    return res;

}
//

lli QuanLyChiTieu::LaySoTienTong(QString MaDanhMuc, QString Username){

    lli res = 0;

    this->TenChu = Username;
    this->MaDanhMuc = MaDanhMuc;

    QSqlQuery qry;

    if( qry.exec("SELECT TongTien FROM DanhMucChiTieu WHERE MaDanhMuc = '"+MaDanhMuc+"' AND TenChu = '"+Username+"'")){

        while (qry.next()) {
            res = qry.value("TongTien").toLongLong();
        }
    }
    else{
        qDebug()<<"Loi CSDL";
        return -1;
    }
    return res;
}

lli QuanLyChiTieu::LaySoTienTheoMaKhoanChi(QString Username, int MaKhoanChi){
    this->TenChu = Username;
    lli res = 0;

    QSqlQuery qry;
    qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND kc.MaKhoanChi = :MaKhoanChi ");


    qry.bindValue(":MaKhoanChi", MaKhoanChi);
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

void QuanLyChiTieu::XoaTaiKhoanInChiTieu(QString Username, QString TenTaiKhoan ){
    QVector< int > MaKhoanChi;

    QSqlQuery qry;

    //Tính số tiền phải xoá cho mỗi danh mục
    lli TienGD = 0, TienSK = 0, TienMS = 0, TienHP = 0, TienHD = 0, TienKD = 0, TienOT = 0, TienQT = 0, TienDC = 0, TienGT = 0, TienBH = 0;


    qry.prepare("SELECT dmct.MaDanhMuc, kc.SoTien, kc.MaKhoanChi FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND kc.TenTaiKhoan = :TenTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":TenTaiKhoan", TenTaiKhoan);

    if( qry.exec() ){

        while( qry.next() ){
            MaKhoanChi.push_back( qry.value("MaKhoanChi").toInt() );
            if( qry.value("MaDanhMuc").toString() == "GD" ) TienGD += qry.value("SoTien").toLongLong();
            if( qry.value("MaDanhMuc").toString() == "SK" ) TienSK += qry.value("SoTien").toLongLong();
            if( qry.value("MaDanhMuc").toString() == "MS" ) TienMS += qry.value("SoTien").toLongLong();
            if( qry.value("MaDanhMuc").toString() == "HP" ) TienHP += qry.value("SoTien").toLongLong();
            if( qry.value("MaDanhMuc").toString() == "HD" ) TienHD += qry.value("SoTien").toLongLong();
            if( qry.value("MaDanhMuc").toString() == "KD" ) TienKD += qry.value("SoTien").toLongLong();
            if( qry.value("MaDanhMuc").toString() == "OT" ) TienOT += qry.value("SoTien").toLongLong();
            if( qry.value("MaDanhMuc").toString() == "QT" ) TienQT += qry.value("SoTien").toLongLong();
            if( qry.value("MaDanhMuc").toString() == "DC" ) TienDC += qry.value("SoTien").toLongLong();
            if( qry.value("MaDanhMuc").toString() == "GT" ) TienGT += qry.value("SoTien").toLongLong();
            if( qry.value("MaDanhMuc").toString() == "BH" ) TienBH += qry.value("SoTien").toLongLong();


        }
    }
    else{
        qDebug()<<"Loi CSDL";
        return;
    }

    //Xoá trong bảng KhoanChi

    qry.prepare("DELETE kc FROM KhoanChi kc INNER JOIN dbo.DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND kc.TenTaiKhoan = :TenTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":TenTaiKhoan", TenTaiKhoan);

    if( !qry.exec() ){
        qDebug()<<"Loi CSDL";
        return;
    }

    // Cập nhật TongTien trong bảng DanhMucChiTieu

    TienGD = this->LaySoTienTong("GD", Username) - TienGD;
    TienSK = this->LaySoTienTong("SK", Username) - TienSK;
    TienMS = this->LaySoTienTong("MS", Username) - TienMS;
    TienHP = this->LaySoTienTong("HP", Username) - TienHP;
    TienHD = this->LaySoTienTong("HD", Username) - TienHD;
    TienKD = this->LaySoTienTong("KD", Username) - TienKD;
    TienOT = this->LaySoTienTong("OT", Username) - TienOT;
    TienQT = this->LaySoTienTong("QT", Username) - TienQT;
    TienDC = this->LaySoTienTong("DC", Username) - TienDC;
    TienGT = this->LaySoTienTong("GT", Username) - TienGT;
    TienBH = this->LaySoTienTong("BH", Username) - TienBH;

    QVector<QString> DanhMuc = {"GD", "SK", "MS", "HP", "HD", "KD", "OT", "QT", "DC", "GT", "BH"};

    QVector<lli> SoTien = {TienGD, TienSK, TienMS, TienHP, TienHD, TienKD, TienOT, TienQT, TienDC, TienGT, TienBH};

    for( int i = 0; i < 11; ++i ){
        qry.prepare("UPDATE DanhMucChiTieu SET TongTien = :TongTien  WHERE MaDanhMuc = :DanhMuc AND TenChu = :Username ");

        qry.bindValue(":TongTien", SoTien[i]);
        qry.bindValue(":DanhMuc", DanhMuc[i]);
        qry.bindValue(":Username", Username);

        qry.exec();

    }

    //Xoá trong thống kê
    for( int i = 0; i < MaKhoanChi.size(); ++i ){
        qry.prepare("DELETE FROM ThongKe WHERE MaKhoanChi = :MKC");

        qry.bindValue(":MKC", MaKhoanChi[i]);
        qry.exec();
    }

}

QVector<QVector<lli>> QuanLyChiTieu::LayThongKe7NgayTruoc(QString Username, QString TenDanhMuc, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam){
    QVector<QVector<lli>> res = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    QVector<int> DayOfMon = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    QString MDM = this->LayMaDanhMuc(TenDanhMuc, Username);

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

        if( TenDanhMuc == "Tất Cả" && TenTaiKhoan == "Tất Cả" )
            qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year");
        if( TenDanhMuc != "Tất Cả" && TenTaiKhoan == "Tất Cả" )
            qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND dmct.MaDanhMuc = :MDM");
        if( TenDanhMuc == "Tất Cả" && TenTaiKhoan != "Tất Cả" )
            qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND kc.TenTaiKhoan = :TenTaiKhoan");
        if( TenDanhMuc != "Tất Cả" && TenTaiKhoan != "Tất Cả" )
            qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND dmct.MaDanhMuc = :MDM AND kc.TenTaiKhoan = :TenTaiKhoan");

        qry.bindValue(":Username", Username);
        qry.bindValue(":day", i);
        qry.bindValue(":month", month);
        qry.bindValue(":year", year);
        qry.bindValue(":MDM", MDM);
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

QVector<QVector<lli>> QuanLyChiTieu::LayThongKe30NgayTruoc(QString Username, QString TenDanhMuc, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam){
    QVector<QVector<lli>> res = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    QVector<int> DayOfMon = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    QString MDM = this->LayMaDanhMuc(TenDanhMuc, Username);

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
            if( TenDanhMuc == "Tất Cả" && TenTaiKhoan == "Tất Cả" )
                qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year");
            if( TenDanhMuc != "Tất Cả" && TenTaiKhoan == "Tất Cả" )
                qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND dmct.MaDanhMuc = :MDM");
            if( TenDanhMuc == "Tất Cả" && TenTaiKhoan != "Tất Cả" )
                qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND kc.TenTaiKhoan = :TenTaiKhoan");
            if( TenDanhMuc != "Tất Cả" && TenTaiKhoan != "Tất Cả" )
                qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND dmct.MaDanhMuc = :MDM AND kc.TenTaiKhoan = :TenTaiKhoan");

            qry.bindValue(":Username", Username);
            qry.bindValue(":day", i);
            qry.bindValue(":month", month);
            qry.bindValue(":year", year);
            qry.bindValue(":MDM", MDM);
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

QVector<QVector<lli>> QuanLyChiTieu::LayThongKe3ThangTruoc(QString Username, QString TenDanhMuc, QString TenTaiKhoan, QString Ngay, QString Thang,QString Nam){
    QVector<QVector<lli>> res = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    QVector<int> DayOfMon = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    QString MDM = this->LayMaDanhMuc(TenDanhMuc, Username);

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
            if( TenDanhMuc == "Tất Cả" && TenTaiKhoan == "Tất Cả" )
                qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year");
            if( TenDanhMuc != "Tất Cả" && TenTaiKhoan == "Tất Cả" )
                qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND dmct.MaDanhMuc = :MDM");
            if( TenDanhMuc == "Tất Cả" && TenTaiKhoan != "Tất Cả" )
                qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND kc.TenTaiKhoan = :TenTaiKhoan");
            if( TenDanhMuc != "Tất Cả" && TenTaiKhoan != "Tất Cả" )
                qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Day(kc.NgayChiTieu) =:day AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND dmct.MaDanhMuc = :MDM AND kc.TenTaiKhoan = :TenTaiKhoan");

            qry.bindValue(":Username", Username);
            qry.bindValue(":day", i);
            qry.bindValue(":month", month);
            qry.bindValue(":year", year);
            qry.bindValue(":MDM", MDM);
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

QVector<lli> QuanLyChiTieu::LayThongKe1Nam(QString Username, QString TenDanhMuc, QString TenTaiKhoan, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int year = Nam.toInt();
    QString MDM = this->LayMaDanhMuc(TenDanhMuc, Username);

    QSqlQuery qry;

    for( int i = 12; i > 0; --i ){
        //Xử lý query tuỳ theo trường hợp
        if( TenDanhMuc == "Tất Cả" && TenTaiKhoan == "Tất Cả" )
            qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year");
        if( TenDanhMuc != "Tất Cả" && TenTaiKhoan == "Tất Cả" )
            qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND dmct.MaDanhMuc = :MDM");
        if( TenDanhMuc == "Tất Cả" && TenTaiKhoan != "Tất Cả" )
            qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND kc.TenTaiKhoan = :TenTaiKhoan");
        if( TenDanhMuc != "Tất Cả" && TenTaiKhoan != "Tất Cả" )
            qry.prepare("SELECT kc.SoTien FROM KhoanChi kc JOIN DanhMucChiTieu dmct ON kc.ID_DanhMuc = dmct.ID_DanhMuc WHERE dmct.TenChu = :Username AND Month(kc.NgayChiTieu) = :month AND Year(kc.NgayChiTieu) = :year AND dmct.MaDanhMuc = :MDM AND kc.TenTaiKhoan = :TenTaiKhoan");

        qry.bindValue(":Username", Username);
        qry.bindValue(":month", i);
        qry.bindValue(":year", year);
        qry.bindValue(":MDM", MDM);
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
