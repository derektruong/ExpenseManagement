#include "loginapp.h"
#include "ui_loginapp.h"

#include <adduser.h>
#include <expensetracker.h>


LoginAPP::LoginAPP(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginAPP)
{
    ui->setupUi(this);

    this->setFixedSize(641,451);

    this->setWindowTitle(QString::fromUtf8("Đăng nhập"));

    //DataBase

    myDB = QSqlDatabase::addDatabase("QSQLITE");

    //myDB.setDatabaseName("F:\\TailieuBK\\HK3\\DALT\\ToSQLiteQuanLyThuChi\\DO_AN_THU_CHI.db");
    myDB.setDatabaseName(QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/DO_AN_THU_CHI.db"));
    bool connected = myDB.open();

    if(!connected){
        ui->label_TrangThai->setText(QString::fromUtf8("Lỗi! Không kết nối được CSDL!"));
        CreateTriggerKhoanChi();
    }
    else if(connected) ui->label_TrangThai->setText(QString::fromUtf8("Đã kết nối được CSDL!"));

}

LoginAPP::~LoginAPP()
{
    delete ui;
}

//Tạo các Trigger trong bảng KhoanChi
void LoginAPP::CreateTriggerKhoanChi(){
    QSqlQuery qry;
    //Create Trigger KhoanChi To DanhMucChiTieu
    qry.prepare("CREATE TRIGGER IF NOT EXISTS TRG_KhoanChi_DMCT  AFTER INSERT ON KhoanChi WHEN (NEW.SoTien <= (SELECT TaiKhoan.SoDu FROM TaiKhoan WHERE NEW.TenTaiKhoan = TaiKhoan.Ten AND TaiKhoan.TenChu = ( SELECT DanhMucChiTieu.TenChu FROM DanhMucChiTieu WHERE DanhMucChiTieu.ID_DanhMuc = NEW.ID_DanhMuc) ) )  BEGIN  UPDATE DanhMucChiTieu  SET TongTien = TongTien + NEW.SoTien WHERE ID_DanhMuc = NEW.ID_DanhMuc; END;");

    if( !qry.exec() ){
        qDebug()<<"Lỗi! Không kết nối được CSDL!\n";
    }
    //Create Trigger KhoanChi To ThongKe
    qry.prepare("CREATE TRIGGER IF NOT EXISTS TRG_KhoanChi_ThongKe  AFTER INSERT ON KhoanChi WHEN (NEW.SoTien <= (SELECT TaiKhoan.SoDu FROM TaiKhoan WHERE NEW.TenTaiKhoan = TaiKhoan.Ten AND TaiKhoan.TenChu = ( SELECT DanhMucChiTieu.TenChu FROM DanhMucChiTieu WHERE DanhMucChiTieu.ID_DanhMuc = NEW.ID_DanhMuc) ) )  BEGIN  INSERT INTO ThongKe ( ThoiGian, TenChu, MaThuNhap, MaKhoanChi ) VALUES ( NEW.NgayChiTieu, ( SELECT DanhMucChiTieu.TenChu FROM DanhMucChiTieu WHERE DanhMucChiTieu.ID_DanhMuc = NEW.ID_DanhMuc), NULL, NEW.MaKhoanChi ); END;");

    if( !qry.exec() ){
        qDebug()<<"Lỗi! Không kết nối được CSDL!\n";
    }

    //Create Trigger KhoanChi To TaiKhoan

    qry.prepare("CREATE TRIGGER IF NOT EXISTS TRG_KhoanChi_TaiKhoan AFTER INSERT ON KhoanChi WHEN (NEW.SoTien <= (SELECT TaiKhoan.SoDu FROM TaiKhoan WHERE NEW.TenTaiKhoan = TaiKhoan.Ten AND TaiKhoan.TenChu = ( SELECT DanhMucChiTieu.TenChu FROM DanhMucChiTieu WHERE DanhMucChiTieu.ID_DanhMuc = NEW.ID_DanhMuc) ) )  BEGIN  UPDATE TaiKhoan  SET SoDu = SoDu - NEW.SoTien WHERE NEW.TenTaiKhoan = TaiKhoan.Ten AND TaiKhoan.TenChu = ( SELECT DanhMucChiTieu.TenChu FROM DanhMucChiTieu WHERE DanhMucChiTieu.ID_DanhMuc = NEW.ID_DanhMuc); END;");

    if( !qry.exec() ){
        qDebug()<<"Lỗi! Không kết nối được CSDL!\n";
    }

}
//Tạo các Trigger trong bảng ThuNhap
void LoginAPP::CreateTriggerThuNhap(){
    QSqlQuery qry;
    //Create Trigger ThuNhap To ThongKe
    qry.prepare("CREATE TRIGGER IF NOT EXISTS TRG_ThuNhap_ThongKe AFTER INSERT ON ThuNhap WHEN (NEW.SoTien > 0)  BEGIN INSERT INTO ThongKe ( ThoiGian, TenChu, MaThuNhap, MaKhoanChi ) VALUES ( NEW.NgayThuNhap, ( SELECT LoaiThuNhap.TenChu FROM LoaiThuNhap WHERE LoaiThuNhap.MaLoaiThuNhap = NEW.MaLoaiThuNhap ), NEW.MaThuNhap, NULL ); END; ");

    if( !qry.exec() ){
        qDebug()<<"Lỗi! Không kết nối được CSDL!\n";
    }

    //Create Trigger ThuNhap To TaiKhoan

    qry.prepare("CREATE TRIGGER IF NOT EXISTS TRG_ThuNhap_TaiKhoan AFTER INSERT ON ThuNhap WHEN (NEW.SoTien > 0)  BEGIN UPDATE TaiKhoan SET SoDu = SoDu + NEW.SoTien WHERE TaiKhoan.Ten = NEW.TenTaiKhoan AND TaiKhoan.TenChu =  ( SELECT LoaiThuNhap.TenChu FROM LoaiThuNhap WHERE LoaiThuNhap.MaLoaiThuNhap = NEW.MaLoaiThuNhap ); UPDATE TaiKhoan SET SoDu = SoDu - 2 * NEW.SoTien WHERE TaiKhoan.Ten = NEW.TenTaiKhoan AND TaiKhoan.Loai = 'Nợ' AND TaiKhoan.TenChu =  ( SELECT LoaiThuNhap.TenChu FROM LoaiThuNhap WHERE LoaiThuNhap.MaLoaiThuNhap = NEW.MaLoaiThuNhap ); END;");

    if( !qry.exec() ){
        qDebug()<<"Lỗi! Không kết nối được CSDL!\n";
    }
}

QString LoginAPP::Decrypt(QString str){
    int s=0;
    QString res="";
    for(int i = 0; i < str.size(); ++i){
        if( str[i].unicode() < 48 || str[i].unicode() > 57 ){
            s = (s - 1998)/23;
            res += QString::number(s);
            s=0;
            continue;
        }

        s = s*10 + (str[i].unicode() - 48);
    }
    return res;
}


void LoginAPP::on_pushButton_DangNhap_clicked()
{
    QString TenDangNhap = ui->lineEdit_TenDangNhap->text();
    QString MaPin = ui->lineEdit_MaPin->text();

    /*if( !myDB.isOpen() ) {
        qDebug()<<QString::fromUtf8("Lỗi! Không kết nối được CSDL!");

        return;
    }*/
    for ( int i = 0; i < MaPin.size(); ++i) {
        if( MaPin[i] < 48 || MaPin[i] > 57 ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Mã pin chỉ gồm các chữ số"));
            return;
        }
    }

    myDB.open();

    QSqlQuery qry;

    QString DecryptMaPin;

    if( qry.exec("SELECT * FROM NguoiDung WHERE TenDangNhap = '"+TenDangNhap+"'") ){

        int count = 0;
        while( qry.next() ){
            count++;
            DecryptMaPin = Decrypt(qry.value("MaPin").toString());
            if( MaPin == DecryptMaPin){
                //QMessageBox::information(this,QString::fromUtf8("Thông báo"),QString::fromUtf8("Tên đăng nhập và mật khẩu đã chính xác!"));
                this->close();
                ExpenseTracker addNewTracker;
                //Tham chiếu Tên đăng nhập để sử dụng trong lớp ExpenseTracker
                addNewTracker.TenDangNhap = TenDangNhap;

                //Hiển thị
                addNewTracker.setModal(true);
                addNewTracker.exec();
                this->close();
            }
            else{
                QMessageBox::warning(this,QString::fromUtf8("Chú ý"),QString::fromUtf8("Tên đăng nhập hoặc mật khẩu không chính xác!\n Nếu chưa có tài khoản hãy thêm mới!!"));
            }

        }

        if( count < 1 ){
            QMessageBox::warning(this,QString::fromUtf8("Chú ý"),QString::fromUtf8("Tên đăng nhập hoặc mật khẩu không chính xác!\n Nếu chưa có tài khoản hãy thêm mới!!"));
        }

    }
}

void LoginAPP::on_pushButton_ThemTaiKhoan_clicked()
{
    AddUser AddUser;
    AddUser.setModal(true);
    AddUser.exec();
}
