#include "adduser.h"
#include "ui_adduser.h"


AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);

    this->setFixedSize(1147,749);

    this->setWindowTitle(QString::fromUtf8("Đăng ký"));

    //DataBase
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QODBC");

    myDB.setDatabaseName("DRIVER={SQL Server Native Client 11.0};SERVER=DEREKPC;DATABASE=DO_AN_CHI_TIEU;UID=sa;PWD=derek123;WSID=.;Trusted_connection=yes");

    bool connected = myDB.open();

    if(!connected) QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Lỗi! Không kết nối được CSDL!!"));
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

    if( qry.exec("INSERT dbo.NguoiDung( TenDangNhap,MaPin,HoVaTen,Email,CongViec ) VALUES('"+TenDangNhap+"', '" +EncryptMaPin+"',  N'" + HoVaTen +"', '" + Email +"', N'"+ CongViec +"' )")){
        ChiTieu.ThemDanhMucMacDinh(TenDangNhap);
        QMessageBox::information(this, QString::fromUtf8("Chúc mừng"), QString::fromUtf8("Bạn đã đăng ký thành công!!"));
        hide();

    }
    else{
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Tên đăng nhập đã tồn tại!!"));
        return;
    }

}
