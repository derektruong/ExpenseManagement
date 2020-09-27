#include "quanlychitieu.h"


QuanLyChiTieu::QuanLyChiTieu()
{


}

void QuanLyChiTieu::ThemDanhMucMacDinh(QString Username){
    this->TenChu = Username;

    QSqlQuery qry;

    qry.exec("INSERT dbo.DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'BH',  N'Bách Hoá',  0,  N'Đồ gia dụng, đồ chơi, đồ gia dụng,...',  '"+TenChu+"'  )");
    qry.exec("INSERT dbo.DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'DC',  N'Di Chuyển',  0,  N'Xăng, vé xe,...',  '"+TenChu+"'  )");
    qry.exec("INSERT dbo.DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'GD',  N'Gia Đình',  0,  N'Chi phí gia đình, nội thất,...',  '"+TenChu+"'  )");
    qry.exec("INSERT dbo.DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'GT',  N'Giải Trí',  0,  N'Xem phim, du lịch,...',  '"+TenChu+"'  )");
    qry.exec("INSERT dbo.DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'HD',  N'Hoá Đơn',  0,  N'Hoá đơn điện, nước, internet, cáp truyền hình,...',  '"+TenChu+"'  )");
    qry.exec("INSERT dbo.DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'HP',  N'Học Phí',  0,  N'Học phí',  '"+TenChu+"'  )");
    qry.exec("INSERT dbo.DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'KD',  N'Kinh Doanh',  0,  N'Chi phí kinh tế',  '"+TenChu+"'  )");
    qry.exec("INSERT dbo.DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'MS',  N'Mua Sắm',  0,  N'Quần áo, phụ kiện, mỹ phẩm,...',  '"+TenChu+"'  )");
    qry.exec("INSERT dbo.DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'OT',  N'Khác',  0,  N'Mục khác,...',  '"+TenChu+"'  )");
    qry.exec("INSERT dbo.DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'QT',  N'Quà Tặng',  0,  N'Quà tặng,...',  '"+TenChu+"'  )");
    qry.exec("INSERT dbo.DanhMucChiTieu ( MaDanhMuc, TenDanhMuc, TongTien, MoTa, TenChu ) VALUES ( 'SK',  N'Sức Khoẻ',  0,  N'Thuốc, dược phẩm,...',  '"+TenChu+"'  )");

}

QString QuanLyChiTieu::LayMaDanhMuc(QString TenDanhMuc, QString Username){
    QString MDM;

    this->TenChu = Username;

    QSqlQuery qry;

    if( qry.exec("SELECT dmct.* FROM dbo.DanhMucChiTieu dmct WHERE dmct.TenDanhMuc = N'"+TenDanhMuc+"' AND dmct.TenChu = '"+Username+"'") ){
        while ( qry.next() ) {
            MDM = qry.value("MaDanhMuc").toString();
        }
    }
    return MDM;

}

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

void QuanLyChiTieu::XoaTaiKhoanInChiTieu(QString Username, QString TenTaiKhoan ){

    QSqlQuery qry;

    //Tính số tiền phải xoá cho mỗi danh mục
    lli TienGD = 0, TienSK = 0, TienMS = 0, TienHP = 0, TienHD = 0, TienKD = 0, TienOT = 0, TienQT = 0, TienDC = 0, TienGT = 0, TienBH = 0;


    qry.prepare("SELECT MaDanhMuc, SoTien FROM KhoanChi WHERE TenChu = :Username AND TenTaiKhoan = :TenTaiKhoan");

    qry.bindValue(":Username", Username);
    qry.bindValue(":TenTaiKhoan", TenTaiKhoan);

    if( qry.exec() ){

        while( qry.next() ){
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

    qry.prepare("DELETE FROM KhoanChi WHERE TenChu = :Username AND TenTaiKhoan = :TenTaiKhoan");

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

}

