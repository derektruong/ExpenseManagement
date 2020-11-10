#include "adduser.h"
#include "ui_adduser.h"


AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);

    this->setFixedSize(1151,671);

    this->setWindowIcon(QIcon(":/Images\\Icon\\cash-icon.png"));

    this->setWindowTitle(QString::fromUtf8("Đăng ký"));

}

AddUser::~AddUser()
{
    delete ui;
}

QString AddUser::Encrypt(QString str){
    QString res="";

    srand(time(NULL));

    for(int i = 0; i<str.size(); ++i){
        res+= QString::number((str[i].unicode() - 48 ) * 23  + 1998) ;
        int asc = 130 + ( rand() % ( 223 - 130 + 1 ) );
        res+=char(asc);
    }
    return res;
}

void AddUser::on_pushButton_DangKy_AddUser_clicked()
{
    QString TenDangNhap, MaPin, NhapLaiMaPin, HoVaTen, Email, CongViec;

    TenDangNhap = ui->lineEdit_TenDangNhap_AddUser->text();
    MaPin = ui->lineEdit_MaPin_AddUser->text();
    NhapLaiMaPin = ui->lineEdit_NhapLaiMaPin_AddUser->text();
    HoVaTen = ui->lineEdit_HoVaTen_AddUser->text();
    Email = ui->lineEdit_Email_AddUser->text();
    CongViec = ui->lineEdit_CongViec_AddUser->text();

    for ( int i = 0; i < MaPin.size(); ++i) {
        if( MaPin[i] < 48 || MaPin[i] > 57 ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Mã pin chỉ gồm các chữ số"));
            return;
        }
    }
    if( MaPin != NhapLaiMaPin ) {
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Nhập lại mã pin sai!!"));
        return;
    }

    if( TenDangNhap == "" || MaPin == ""  || NhapLaiMaPin == "" || HoVaTen == "" || Email == ""  || CongViec == "" ){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Phải nhập đủ các thông tin!!"));
        return;
    }

    QSqlQuery qry;

    QString EncryptMaPin = Encrypt(MaPin);

    qry.prepare("INSERT INTO NguoiDung( TenDangNhap, MaPin, HoVaTen, Email, CongViec )" "VALUES( :TenDangNhap, :EncryptMaPin, :HoVaTen, :Email, :CongViec )");

    qry.bindValue(":TenDangNhap", TenDangNhap);
    qry.bindValue(":EncryptMaPin", EncryptMaPin);
    qry.bindValue(":HoVaTen", HoVaTen);
    qry.bindValue(":Email", Email);
    qry.bindValue(":CongViec", CongViec);

    if( qry.exec()){
        ChiTieu.ThemDanhMucMacDinh(TenDangNhap);
        QMessageBox::information(this, QString::fromUtf8("Chúc mừng"), QString::fromUtf8("Bạn đã đăng ký thành công!!"));

        QString Index = TenDangNhap+"_index";
        qry.prepare("CREATE UNIQUE INDEX IF NOT EXISTS :Index ON LoaiThuNhap(LoaiThuNhap) WHERE TenChu = :TenDangNhap ");

        qry.bindValue(":Index", Index);
        qry.bindValue(":TenDangNhap", TenDangNhap);

        if( !qry.exec()) qDebug()<<"Lỗi không kết nối được CSDL!";

        qry.prepare("CREATE UNIQUE INDEX IF NOT EXISTS :Index ON TaiKhoan(Ten) WHERE TenChu = :TenDangNhap ");

        qry.bindValue(":Index", Index);
        qry.bindValue(":TenDangNhap", TenDangNhap);

        if( !qry.exec()) qDebug()<<"Lỗi không kết nối được CSDL!";

        hide();

    }
    else{
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Tên đăng nhập đã tồn tại!!"));
        return;
    }

}
