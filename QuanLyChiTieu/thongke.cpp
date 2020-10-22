#include "thongke.h"

ThongKe::ThongKe()
{

}

void ThongKe::CapNhatMaKhoanChi(QString Username, QString ThoiGian, int MaKhoanChi ){
    this->TenChu = Username;
    this->ThoiGian = ThoiGian;

    QSqlQuery qry;
    qry.prepare("INSERT INTO ThongKe ( ThoiGian, TenChu, MaKhoanChi )" "VALUES ( :ThoiGian, :TenChu, :MaKhoanChi )");

    qry.bindValue(":MaKhoanChi", MaKhoanChi);
    qry.bindValue(":ThoiGian", ThoiGian);
    qry.bindValue(":TenChu", Username);

    if( !qry.exec() ){
       qDebug()<<"Lỗi không kết nối được CSDL!";
       return;
    }

}

void ThongKe::CapNhatMaThuNhap(QString Username, QString ThoiGian, int MaThuNhap ){
    this->TenChu = Username;
    this->ThoiGian = ThoiGian;

    QSqlQuery qry;


    qry.prepare("INSERT INTO ThongKe ( ThoiGian, TenChu, MaThuNhap )" "VALUES ( :ThoiGian, :TenChu, :MaThuNhap )");

    qry.bindValue(":MaThuNhap", MaThuNhap);
    qry.bindValue(":ThoiGian", ThoiGian);
    qry.bindValue(":TenChu", Username);

    if( !qry.exec() ){
       qDebug()<<"Lỗi không kết nối được CSDL!";
       return;
    }


}

//Chưa fix 22102020
QVector<lli> ThongKe::LayDuLieuTongThuTheoTuan(QString Username, QString Thang, QString Nam){

    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Day(ThoiGian) AS 'Ngay', MaThuNhap FROM ThongKe WHERE TenChu = :Username AND Month(ThoiGian) = :Thang AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Thang", Thang);
    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            int MTN = qry.value("MaThuNhap").toInt();

            for( int i = 1, j = 5, cnt = 1; i < 30; i += 4, j += 4, ++cnt ){
                if( qry.value("Ngay").toInt() >= i && qry.value("Ngay").toInt() < j )
                    res[cnt] += ThuNhapQL.LaySoTienTong(Username, MTN);
            }
        }

    }

    return res;


}

QVector<lli> ThongKe::LayDuLieuTongChiTheoTuan(QString Username, QString Thang, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Day(ThoiGian) AS 'Ngay', MaKhoanChi FROM ThongKe WHERE TenChu = :Username AND Month(ThoiGian) = :Thang AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Thang", Thang);
    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            int MKC = qry.value("MaKhoanChi").toInt();

            for( int i = 1, j = 5, cnt = 1; i < 30; i += 4, j += 4, ++cnt ){
                if( qry.value("Ngay").toInt() >= i && qry.value("Ngay").toInt() < j )
                    res[cnt] -= ChiTieuQL.LaySoTienTheoMaKhoanChi(Username, MKC);
            }
        }

    }

    return res;
}


QVector<lli> ThongKe::LayDuLieuTongThuTheoNam(QString Username, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Month(ThoiGian) AS 'Thang', MaThuNhap FROM ThongKe WHERE TenChu = :Username AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            int MTN = qry.value("MaThuNhap").toInt();

            for( int i = 1; i <= 12; ++i ){
                if( qry.value("Thang").toInt() == i )
                    res[i] += ThuNhapQL.LaySoTienTong(Username, MTN);
            }
        }

    }

    return res;
}

QVector<lli> ThongKe::LayDuLieuTongChiTheoNam(QString Username, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Month(ThoiGian) AS 'Thang', MaKhoanChi FROM ThongKe WHERE TenChu = :Username AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            int MKC = qry.value("MaKhoanChi").toInt();

            for( int i = 1; i <= 12; ++i ){
                if( qry.value("Thang").toInt() == i )
                    res[i] -= ChiTieuQL.LaySoTienTheoMaKhoanChi(Username, MKC);
            }
        }

    }

    return res;
}

QVector<lli> ThongKe::LayDuLieuCanDoiTheoTuan(QString Username, QString Thang, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Day(ThoiGian) AS 'Ngay', MaKhoanChi, MaThuNhap FROM ThongKe WHERE TenChu = :Username AND Month(ThoiGian) = :Thang AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Thang", Thang);
    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            int MKC = qry.value("MaKhoanChi").toInt();
            int MTN = qry.value("MaThuNhap").toInt();

            for( int i = 1, j = 5, cnt = 1; i < 30; i += 4, j += 4, ++cnt ){
                if( qry.value("Ngay").toInt() >= i && qry.value("Ngay").toInt() < j )
                    res[cnt] += ThuNhapQL.LaySoTienTong(Username, MTN) - ChiTieuQL.LaySoTienTheoMaKhoanChi(Username, MKC);
            }
        }

    }

    return res;
}

QVector<lli> ThongKe::LayDuLieuCanDoiTheoNam(QString Username, QString Nam){
    QVector<lli> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    QSqlQuery qry;

    qry.prepare("SELECT Month(ThoiGian) AS 'Thang', MaKhoanChi, MaThuNhap FROM ThongKe WHERE TenChu = :Username AND Year(ThoiGian) = :Nam");

    qry.bindValue(":Nam", Nam);
    qry.bindValue(":Username", Username);

    if( qry.exec() ){
        while ( qry.next() ) {
            int MKC = qry.value("MaKhoanChi").toInt();
            int MTN = qry.value("MaThuNhap").toInt();

            for( int i = 1; i <= 12; ++i ){
                if( qry.value("Thang").toInt() == i )
                    res[i] += ThuNhapQL.LaySoTienTong(Username, MTN) - ChiTieuQL.LaySoTienTheoMaKhoanChi(Username, MKC);
            }
        }

    }

    return res;
}
