#include "thongke.h"

ThongKe::ThongKe()
{

}

void ThongKe::CapNhatTongThu(QString Username, QString ThoiGian, lli SoTien ){
    this->TenChu = Username;
    this->ThoiGian = ThoiGian;

    bool CheckExistDate = false;
    lli TienThu = 0, TienCanDoi = 0;

    QSqlQuery qry;

    qry.prepare("SELECT TongThu, CanDoi, ThoiGian FROM ThongKe WHERE TenChu = :Username ");

    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        int cnt = 0;
        while ( qry.next() ) {
            if( qry.value("ThoiGian").toString() == ThoiGian ){
                TienThu += qry.value("TongThu").toLongLong();
                TienCanDoi += qry.value("CanDoi").toLongLong();
                cnt++;
            }

        }
        if( cnt ) CheckExistDate = true;
    }
    //Nếu ngày chưa tồn tại
    if( !CheckExistDate ) {
        qry.prepare("INSERT INTO ThongKe ( TongThu, TongChi, CanDoi, ThoiGian, TenChu )" "VALUES ( :TongThu, :TongChi, :CanDoi, :ThoiGian, :TenChu )");

        qry.bindValue(":TongThu", SoTien);
        qry.bindValue(":TongChi", 0);
        qry.bindValue(":CanDoi", SoTien);
        qry.bindValue(":ThoiGian", ThoiGian);
        qry.bindValue(":TenChu", Username);

        if( !qry.exec() ){
           qDebug()<<"Lỗi không kết nối được CSDL!";
           return;
        }

    }
    //Nếu ngày đã tồn tại
    else if ( CheckExistDate ) {
        qry.prepare("UPDATE ThongKe SET	TongThu = :TongThu, CanDoi = :CanDoi WHERE TenChu = :TenChu AND ThoiGian = :ThoiGian");

        qry.bindValue(":TongThu", SoTien + TienThu);
        qry.bindValue(":CanDoi", TienCanDoi + SoTien);
        qry.bindValue(":ThoiGian", ThoiGian);
        qry.bindValue(":TenChu", Username);

        if( !qry.exec() ){
           qDebug()<<"Lỗi không kết nối được CSDL!";
           return;
        }
    }

}

void ThongKe::CapNhatTongChi(QString Username, QString ThoiGian, lli SoTien ){
    this->TenChu = Username;
    this->ThoiGian = ThoiGian;

    bool CheckExistDate = false;
    lli TienChi = 0, TienCanDoi = 0;

    QSqlQuery qry;

    qry.prepare("SELECT TongChi, CanDoi, ThoiGian FROM ThongKe WHERE TenChu = :Username ");

    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        int cnt = 0;
        while ( qry.next() ) {
            if( qry.value("ThoiGian").toString() == ThoiGian ){
                TienChi += qry.value("TongChi").toLongLong();
                TienCanDoi += qry.value("CanDoi").toLongLong();
                cnt++;
            }

        }
        if( cnt ) CheckExistDate = true;
    }
    //Nếu ngày chưa tồn tại
    if( !CheckExistDate ) {
        qry.prepare("INSERT INTO ThongKe ( TongThu, TongChi, CanDoi, ThoiGian, TenChu )" "VALUES ( :TongThu, :TongChi, :CanDoi, :ThoiGian, :TenChu )");

        qry.bindValue(":TongThu", 0);
        qry.bindValue(":TongChi", SoTien);
        qry.bindValue(":CanDoi", -SoTien);
        qry.bindValue(":ThoiGian", ThoiGian);
        qry.bindValue(":TenChu", Username);

        if( !qry.exec() ){
           qDebug()<<"Lỗi không kết nối được CSDL!";
           return;
        }

    }
    //Nếu ngày đã tồn tại
    else if ( CheckExistDate ) {
        qry.prepare("UPDATE ThongKe SET	TongChi = :TongChi, CanDoi = :CanDoi WHERE TenChu = :TenChu AND ThoiGian = :ThoiGian");

        qry.bindValue(":TongChi", TienChi + SoTien);
        qry.bindValue(":CanDoi", TienCanDoi - SoTien);
        qry.bindValue(":ThoiGian", ThoiGian);
        qry.bindValue(":TenChu", Username);

        if( !qry.exec() ){
           qDebug()<<"Lỗi không kết nối được CSDL!";
           return;
        }
    }
}

QVector<lli> ThongKe::LayDuLieuTongThuTheoTuan(QString Username, QString Thang, QString Nam){

    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Day(ThoiGian) AS 'Ngay', TongThu FROM ThongKe WHERE TenChu = :Username AND Month(ThoiGian) = :Thang AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Thang", Thang);
    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            if( qry.value("Ngay").toInt() >= 1 && qry.value("Ngay").toInt() < 5 )
                res[1] += qry.value("TongThu").toLongLong();
            if( qry.value("Ngay").toInt() >= 5 && qry.value("Ngay").toInt() < 9 )
                res[2] += qry.value("TongThu").toLongLong();
            if( qry.value("Ngay").toInt() >= 9 && qry.value("Ngay").toInt() < 13 )
                res[3] += qry.value("TongThu").toLongLong();
            if( qry.value("Ngay").toInt() >= 13 && qry.value("Ngay").toInt() < 17 )
                res[4] += qry.value("TongThu").toLongLong();
            if( qry.value("Ngay").toInt() >= 17 && qry.value("Ngay").toInt() < 21 )
                res[5] += qry.value("TongThu").toLongLong();
            if( qry.value("Ngay").toInt() >= 21 && qry.value("Ngay").toInt() < 25 )
                res[6] += qry.value("TongThu").toLongLong();
            if( qry.value("Ngay").toInt() >= 25 && qry.value("Ngay").toInt() < 29 )
                res[7] += qry.value("TongThu").toLongLong();
            if( qry.value("Ngay").toInt() >= 29 && qry.value("Ngay").toInt() < 32 )
                res[8] += qry.value("TongThu").toLongLong();
        }

    }

    return res;


}

QVector<lli> ThongKe::LayDuLieuTongChiTheoTuan(QString Username, QString Thang, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Day(ThoiGian) AS 'Ngay', TongChi FROM ThongKe WHERE TenChu = :Username AND Month(ThoiGian) = :Thang AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Thang", Thang);
    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            if( qry.value("Ngay").toInt() >= 1 && qry.value("Ngay").toInt() < 5 )
                res[1] -= qry.value("TongChi").toLongLong();
            if( qry.value("Ngay").toInt() >= 5 && qry.value("Ngay").toInt() < 9 )
                res[2] -= qry.value("TongChi").toLongLong();
            if( qry.value("Ngay").toInt() >= 9 && qry.value("Ngay").toInt() < 13 )
                res[3] -= qry.value("TongChi").toLongLong();
            if( qry.value("Ngay").toInt() >= 13 && qry.value("Ngay").toInt() < 17 )
                res[4] -= qry.value("TongChi").toLongLong();
            if( qry.value("Ngay").toInt() >= 17 && qry.value("Ngay").toInt() < 21 )
                res[5] -= qry.value("TongChi").toLongLong();
            if( qry.value("Ngay").toInt() >= 21 && qry.value("Ngay").toInt() < 25 )
                res[6] -= qry.value("TongChi").toLongLong();
            if( qry.value("Ngay").toInt() >= 25 && qry.value("Ngay").toInt() < 29 )
                res[7] -= qry.value("TongChi").toLongLong();
            if( qry.value("Ngay").toInt() >= 29 && qry.value("Ngay").toInt() < 32 )
                res[8] -= qry.value("TongChi").toLongLong();
        }

    }

    return res;
}


QVector<lli> ThongKe::LayDuLieuTongThuTheoNam(QString Username, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Month(ThoiGian) AS 'Thang', TongThu FROM ThongKe WHERE TenChu = :Username AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            if( qry.value("Thang").toInt() == 1 )
                res[1] += qry.value("TongThu").toLongLong();
            if( qry.value("Thang").toInt() == 2 )
                res[2] += qry.value("TongThu").toLongLong();
            if( qry.value("Thang").toInt() == 3 )
                res[3] += qry.value("TongThu").toLongLong();
            if( qry.value("Thang").toInt() == 4 )
                res[4] += qry.value("TongThu").toLongLong();
            if( qry.value("Thang").toInt() == 5 )
                res[5] += qry.value("TongThu").toLongLong();
            if( qry.value("Thang").toInt() == 6 )
                res[6] += qry.value("TongThu").toLongLong();
            if( qry.value("Thang").toInt() == 7 )
                res[7] += qry.value("TongThu").toLongLong();
            if( qry.value("Thang").toInt() == 8 )
                res[8] += qry.value("TongThu").toLongLong();
            if( qry.value("Thang").toInt() == 9 )
                res[9] += qry.value("TongThu").toLongLong();
            if( qry.value("Thang").toInt() == 10 )
                res[10] += qry.value("TongThu").toLongLong();
            if( qry.value("Thang").toInt() == 11 )
                res[11] += qry.value("TongThu").toLongLong();
            if( qry.value("Thang").toInt() == 12 )
                res[12] += qry.value("TongThu").toLongLong();
        }

    }

    return res;
}

QVector<lli> ThongKe::LayDuLieuTongChiTheoNam(QString Username, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Month(ThoiGian) AS 'Thang', TongChi FROM ThongKe WHERE TenChu = :Username AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            if( qry.value("Thang").toInt() == 1 )
                res[1] -= qry.value("TongChi").toLongLong();
            if( qry.value("Thang").toInt() == 2 )
                res[2] -= qry.value("TongChi").toLongLong();
            if( qry.value("Thang").toInt() == 3 )
                res[3] -= qry.value("TongChi").toLongLong();
            if( qry.value("Thang").toInt() == 4 )
                res[4] -= qry.value("TongChi").toLongLong();
            if( qry.value("Thang").toInt() == 5 )
                res[5] -= qry.value("TongChi").toLongLong();
            if( qry.value("Thang").toInt() == 6 )
                res[6] -= qry.value("TongChi").toLongLong();
            if( qry.value("Thang").toInt() == 7 )
                res[7] -= qry.value("TongChi").toLongLong();
            if( qry.value("Thang").toInt() == 8 )
                res[8] -= qry.value("TongChi").toLongLong();
            if( qry.value("Thang").toInt() == 9 )
                res[9] -= qry.value("TongChi").toLongLong();
            if( qry.value("Thang").toInt() == 10 )
                res[10] -= qry.value("TongChi").toLongLong();
            if( qry.value("Thang").toInt() == 11 )
                res[11] -= qry.value("TongChi").toLongLong();
            if( qry.value("Thang").toInt() == 12 )
                res[12] -= qry.value("TongChi").toLongLong();
        }

    }

    return res;
}

QVector<lli> ThongKe::LayDuLieuCanDoiTheoTuan(QString Username, QString Thang, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Day(ThoiGian) AS 'Ngay', CanDoi FROM ThongKe WHERE TenChu = :Username AND Month(ThoiGian) = :Thang AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Thang", Thang);
    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            if( qry.value("Ngay").toInt() >= 1 && qry.value("Ngay").toInt() < 5 )
                res[1] += qry.value("CanDoi").toLongLong();
            if( qry.value("Ngay").toInt() >= 5 && qry.value("Ngay").toInt() < 9 )
                res[2] += qry.value("CanDoi").toLongLong();
            if( qry.value("Ngay").toInt() >= 9 && qry.value("Ngay").toInt() < 13 )
                res[3] += qry.value("CanDoi").toLongLong();
            if( qry.value("Ngay").toInt() >= 13 && qry.value("Ngay").toInt() < 17 )
                res[4] += qry.value("CanDoi").toLongLong();
            if( qry.value("Ngay").toInt() >= 17 && qry.value("Ngay").toInt() < 21 )
                res[5] += qry.value("CanDoi").toLongLong();
            if( qry.value("Ngay").toInt() >= 21 && qry.value("Ngay").toInt() < 25 )
                res[6] += qry.value("CanDoi").toLongLong();
            if( qry.value("Ngay").toInt() >= 25 && qry.value("Ngay").toInt() < 29 )
                res[7] += qry.value("CanDoi").toLongLong();
            if( qry.value("Ngay").toInt() >= 29 && qry.value("Ngay").toInt() < 32 )
                res[8] += qry.value("CanDoi").toLongLong();
        }

    }

    return res;
}

QVector<lli> ThongKe::LayDuLieuCanDoiTheoNam(QString Username, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Month(ThoiGian) AS 'Thang', CanDoi FROM ThongKe WHERE TenChu = :Username AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            if( qry.value("Thang").toInt() == 1 )
                res[1] += qry.value("CanDoi").toLongLong();
            if( qry.value("Thang").toInt() == 2 )
                res[2] += qry.value("CanDoi").toLongLong();
            if( qry.value("Thang").toInt() == 3 )
                res[3] += qry.value("CanDoi").toLongLong();
            if( qry.value("Thang").toInt() == 4 )
                res[4] += qry.value("CanDoi").toLongLong();
            if( qry.value("Thang").toInt() == 5 )
                res[5] += qry.value("CanDoi").toLongLong();
            if( qry.value("Thang").toInt() == 6 )
                res[6] += qry.value("CanDoi").toLongLong();
            if( qry.value("Thang").toInt() == 7 )
                res[7] += qry.value("CanDoi").toLongLong();
            if( qry.value("Thang").toInt() == 8 )
                res[8] += qry.value("CanDoi").toLongLong();
            if( qry.value("Thang").toInt() == 9 )
                res[9] += qry.value("CanDoi").toLongLong();
            if( qry.value("Thang").toInt() == 10 )
                res[10] += qry.value("CanDoi").toLongLong();
            if( qry.value("Thang").toInt() == 11 )
                res[11] += qry.value("CanDoi").toLongLong();
            if( qry.value("Thang").toInt() == 12 )
                res[12] += qry.value("CanDoi").toLongLong();
        }

    }

    return res;
}
