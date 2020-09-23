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

