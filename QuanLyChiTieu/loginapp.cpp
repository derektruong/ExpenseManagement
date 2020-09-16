#include "loginapp.h"
#include "ui_loginapp.h"

#include <adduser.h>
#include <expensetracker.h>

LoginAPP::LoginAPP(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginAPP)
{
    ui->setupUi(this);

    this->setFixedSize(801,581);

    this->setWindowTitle(QString::fromUtf8("Đăng nhập"));

    //DataBase

    QSqlDatabase myDB = QSqlDatabase::addDatabase("QODBC");

    myDB.setDatabaseName("DRIVER={SQL Server Native Client 11.0};SERVER=DEREKPC;DATABASE=DO_AN_CHI_TIEU;UID=sa;PWD=derek123;WSID=.;Trusted_connection=yes");

    bool connected = myDB.open();

    if(!connected) ui->label_TrangThai->setText(QString::fromUtf8("Lỗi! Không kết nối được CSDL!"));
    else if(connected) ui->label_TrangThai->setText(QString::fromUtf8("Đã kết nối được CSDL!"));

}

LoginAPP::~LoginAPP()
{
    delete ui;
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

    if( qry.exec("select * from NguoiDung Where TenDangNhap = '"+TenDangNhap+"' and MaPin = '"+MaPin+"' ") ){

        int count = 0;
        while( qry.next() ){
            count++;
        }
        if( count == 1 ){
            QMessageBox::information(this,QString::fromUtf8("Thông báo"),QString::fromUtf8("Tên đăng nhập và mật khẩu đã chính xác!"));
            this->close();
            ExpenseTracker addNewTracker;
            //Tham chiếu Tên đăng nhập để sử dụng trong lớp ExpenseTracker
            addNewTracker.TenDangNhap = TenDangNhap;
            //Hiển thị
            addNewTracker.setModal(true);
            addNewTracker.exec();
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
