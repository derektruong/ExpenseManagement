#include "loginapp.h"
#include "ui_loginapp.h"

#include <adduser.h>
#include <expensetracker.h>

//#include "C:\\Qt\\Qt5.14.2\\5.14.2\\Src\\qtbase\\src\\plugins\\sqldrivers\\odbc\\qsql_odbc.cpp"


LoginAPP::LoginAPP(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginAPP)
{
    ui->setupUi(this);

    this->setFixedSize(641,451);

    this->setWindowTitle(QString::fromUtf8("Đăng nhập"));

    //DataBase

    myDB = QSqlDatabase::addDatabase("QODBC");

    myDB.setDatabaseName("DRIVER={SQL Server Native Client 11.0};SERVER=DEREKPC\\DEREK;DATABASE=DO_AN_THU_CHI;UID=.;PWD=.;WSID=.;Trusted_connection=yes");
    bool connected = myDB.open();

    /*QString dbFilename = QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/DO_AN_THU_CHI.mdf");

    qDebug()<<QCoreApplication::applicationDirPath();

    QString connStr0 = "DRIVER={ODBC Driver 13.1 for SQL Server};SERVER=%1;AttachDbFilename=%2;Integrated Security=true;";
    QString connStr1 = "DRIVER={ODBC Driver 13 for SQL Server};SERVER=%1;AttachDbFilename=%2;Integrated Security=true;";
    QString connStr2 = "DRIVER={ODBC Driver 17 for SQL Server};SERVER=%1;AttachDbFilename=%2;Integrated Security=true;";
    QString connStr3 = "DRIVER={ODBC Driver 11 for SQL Server};SERVER=%1;AttachDbFilename=%2;Integrated Security=true;";
    QString connStr4 = "DRIVER={SQL Server Native Client 11.0};SERVER=%1;AttachDbFilename=%2;Integrated Security=true;";
    QString connStr5 = "DRIVER={SQL Server};SERVER=%1;AttachDbFilename=%2;Integrated Security=true;";
    QString connStr6 = "DRIVER={SQL Server Native Client RDA};SERVER=%1;AttachDbFilename=%2;Integrated Security=true;";

    myDB.setDatabaseName(connStr1.arg("(localdb)\\MSSQLLocalDB").arg(dbFilename));

    bool connected = myDB.open();

    if( !connected ){
        myDB.setDatabaseName(connStr2.arg("(localdb)\\MSSQLLocalDB").arg(dbFilename));
        connected = myDB.open();
    }

    if( !connected ){
        myDB.setDatabaseName(connStr0.arg("(localdb)\\MSSQLLocalDB").arg(dbFilename));
        connected = myDB.open();
    }

    if( !connected ){
        myDB.setDatabaseName(connStr3.arg("(localdb)\\MSSQLLocalDB").arg(dbFilename));
        connected = myDB.open();
    }

    if( !connected ){
        myDB.setDatabaseName(connStr4.arg("(localdb)\\MSSQLLocalDB").arg(dbFilename));
        connected = myDB.open();
    }
    if( !connected ){
        myDB.setDatabaseName(connStr5.arg("(localdb)\\MSSQLLocalDB").arg(dbFilename));
        connected = myDB.open();
    }

    if( !connected ){
        myDB.setDatabaseName(connStr6.arg("(localdb)\\MSSQLLocalDB").arg(dbFilename));
        connected = myDB.open();
    }*/
    //qDebug()<<myDB.lastError().text();

    if(!connected) ui->label_TrangThai->setText(QString::fromUtf8("Lỗi! Không kết nối được CSDL!"));
    else if(connected) ui->label_TrangThai->setText(QString::fromUtf8("Đã kết nối được CSDL!"));

}

LoginAPP::~LoginAPP()
{
    delete ui;
}


QString LoginAPP::Decrypt(QString str){
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

    if( qry.exec("select * from NguoiDung Where TenDangNhap = '"+TenDangNhap+"'") ){

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
