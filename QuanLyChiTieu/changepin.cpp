#include "changepin.h"
#include "ui_changepin.h"

#include <expensetracker.h>

ChangePin::ChangePin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePin)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/Images\\Icon\\cash-icon.png"));

    this->setWindowTitle(QString::fromUtf8("Thay mã pin"));
}

ChangePin::~ChangePin()
{
    delete ui;
}

QString ChangePin::Encrypt(QString str){
    QString res="";

    srand(time(NULL));

    for(int i = 0; i<str.size(); ++i){
        res+= QString::number((str[i].unicode() - 48 ) * 23  + 1998) ;
        int asc = 130 + ( rand() % ( 223 - 130 + 1 ) );
        res+=char(asc);
    }
    return res;
}

QString ChangePin::Decrypt(QString str){
    int s=0;
    QString res="";
    for(int i = 0; i<str.size(); ++i){
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

void ChangePin::on_pushButton_XacNhan_clicked()
{
    QString MaPinCu, MaPinMoi, NhapLaiMaPinMoi;

    MaPinCu = ui->lineEdit_MaPinCu->text();
    MaPinMoi = ui->lineEdit_MaPinMoi->text();
    NhapLaiMaPinMoi = ui->lineEdit_NhapLaiMaPinMoi->text();



    for ( int i = 0; i < MaPinMoi.size(); ++i) {
        if( MaPinMoi[i] < 48 || MaPinMoi[i] > 57 ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Mã pin chỉ gồm các chữ số"));
            return;
        }
    }

    if( MaPinMoi != NhapLaiMaPinMoi ) {
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Nhập lại mã pin sai!!"));
        return;
    }

    myDB.open();
    QSqlQuery qry;

    QString DecryptMaPin;

    if( qry.exec("select * from NguoiDung Where TenDangNhap = '"+TenDangNhap+"'") ){
        while( qry.next() ){
            DecryptMaPin = Decrypt(qry.value("MaPin").toString());
            if( MaPinCu != DecryptMaPin ){
                QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Mã pin cũ không chính xác!!"));
                return;
            }
        }

    }

    QString EncryptMaPin = Encrypt(MaPinMoi);

    if( qry.exec("update NguoiDung set MaPin = '"+EncryptMaPin+"' where TenDangNhap = '"+TenDangNhap+"'") ){
        QMessageBox::information(this,"Thông báo",QString::fromUtf8("Đã thay đổi mã pin thành công!!"));
        this->hide();
    }
    else QMessageBox::warning(this,"Lỗi",QString::fromUtf8("Lỗi không thể thay đổi mã pin!!"));
    this->hide();

}

void ChangePin::on_pushButton_Huy_clicked()
{
    QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn có chắc muốn huỷ!!"));
    this->close();
}
