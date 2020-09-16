#include "expensetracker.h"
#include "ui_expensetracker.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>

ExpenseTracker::ExpenseTracker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpenseTracker)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    //DataBase
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QODBC");

    myDB.setDatabaseName("DRIVER={SQL Server Native Client 11.0};SERVER=DEREKPC;DATABASE=DO_AN_CHI_TIEU;UID=sa;PWD=derek123;WSID=.;Trusted_connection=yes");

    bool connected = myDB.open();

    if(!connected) QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Lỗi! Không kết nối được CSDL!!"));

}

ExpenseTracker::~ExpenseTracker()
{
    delete ui;
}

/*void ExpenseTracker::GetUserName(LoginAPP login){
    TenDangNhap = login.UserName;
}*/

void ExpenseTracker::on_pushButton_TrangChinh_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->label->setText(TenDangNhap);
}

void ExpenseTracker::on_pushButton_ChiTieu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void ExpenseTracker::on_pushButton_ThuNhap_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void ExpenseTracker::on_pushButton_TaiKhoan_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void ExpenseTracker::on_pushButton_ThongKe_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void ExpenseTracker::on_pushButton_NguoiDung_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    QString HoVaTen, Email,CongViec;

    QSqlQuery qry("SELECT * FROM dbo.NguoiDung nd WHERE nd.TenDangNhap = '"+TenDangNhap+"'");
    while( qry.next() ){
        HoVaTen = qry.value("HoVaTen").toString();
        Email = qry.value("Email").toString();
        CongViec = qry.value("CongViec").toString();
    }

    ui->label_HoVaTen_page6->setText(HoVaTen);
    ui->label_TenDangNhap_page6_2->setText(TenDangNhap);
    ui->label_Email_page6_2->setText(Email);
    ui->label_CongViec_page6_2->setText(CongViec);

}

// Resize
void ExpenseTracker::on_pushButton_minimize_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

void ExpenseTracker::on_pushButton_fullscreen_clicked()
{
    this->setWindowState(Qt::WindowMaximized);
    this->setStyleSheet("background-color: rgb(47, 47, 59);}");
    this->setStyleSheet("QPushButton:hover:!pressed{border: 4px solid white;background-color: red;");
}

void ExpenseTracker::on_pushButton_restoredown_clicked()
{
    this->resize(1431,951);
}

void ExpenseTracker::on_pushButton_ThayMaPin_clicked()
{

}
