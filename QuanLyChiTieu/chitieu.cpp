#include "chitieu.h"
#include "ui_chitieu.h"

ChiTieu::ChiTieu(QString DanhMuc, QString username,QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::ChiTieu)
{
    ui->setupUi(this);
    //DataBase
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QODBC");

    myDB.setDatabaseName("DRIVER={SQL Server Native Client 11.0};SERVER=DEREKPC;DATABASE=DO_AN_CHI_TIEU;UID=sa;PWD=derek123;WSID=.;Trusted_connection=yes");

    bool connected = myDB.open();

    if(!connected) qDebug()<<"Lỗi không kết nối được CSDL!";
    //

    this->Username = username;
    this->DanhMuc = DanhMuc;

    QVector<QString> DSTenTK = TaiKhoanQL.LayTenTaiKhoan(username);

    for ( int i = 0; i < DSTenTK.size(); ++i) {
        ui->comboBox_TuTaiKhoan->addItem(DSTenTK[i]);
    }

    ui->label_DenDanhMucHienTai->setText(DanhMuc);

}

ChiTieu::~ChiTieu()
{
    delete ui;
}

void ChiTieu::on_btn_OK_clicked()
{
    //Tiền xử lý dữ liệu
    QString MaDanhMuc, TenTaiKhoan, MoTa, NgayChiTieu;
    lli SoTien;

    MaDanhMuc = DanhMucQL.LayMaDanhMuc(DanhMuc, Username);

    TenTaiKhoan = ui->comboBox_TuTaiKhoan->currentText();

    MoTa = ui->textEdit_MoTa->toPlainText();
    //Kiểm tra hợp lệ số tiền
    for ( int i = 0; i < ui->lineEdit_SoTien->text().size(); ++i) {
        if(ui->lineEdit_SoTien->text()[0] =='0') {
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số tiền nhập không hợp lệ chỉ gồm các chữ số"));
            return;
        }
        if( ui->lineEdit_SoTien->text()[i] < 48 || ui->lineEdit_SoTien->text()[i] > 57 ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số tiền nhập không hợp lệ chỉ gồm các chữ số"));
            return;
        }
    }

    //

    SoTien = ui->lineEdit_SoTien->text().toLongLong();

    if( MoTa == "" ||  SoTien < 0){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Nhập không hợp lệ !!"));
        return;
    }

    NgayChiTieu = ui->dateEdit->text();

    qDebug()<<NgayChiTieu;

    //Định dạng lại format date cho phù hợp với DBase
    QStack<QString> st;

    int s = 0;

    for ( int i = 0; i < NgayChiTieu.size(); ++i) {
        if( NgayChiTieu[i] == '/' ){
            st.push(QString::number(s));
            st.push("/");
            s = 0;
            continue;
        }
        s = s*10 + (NgayChiTieu[i].unicode() - 48);

    }

    st.push(QString::number(s));

    NgayChiTieu = "";

    while ( !st.empty() ) {
        NgayChiTieu+=st.top();
        st.pop();
    }
    qDebug()<<NgayChiTieu;

    // Truy vấn DB

    //// Trừ tiền trong tài khoản

    QSqlQuery qry;

    lli SoDuTK = TaiKhoanQL.LaySoDu(Username,TenTaiKhoan);

    SoDuTK -= SoTien;

    if( SoDuTK < 0 ){
        QMessageBox::warning(this,"Nguy hiểm",QString::fromUtf8("Số tiền chi tiêu vượt quá số dư của tài khoản này!!"));
        return;
    }

    else{
        qry.prepare("UPDATE TaiKhoan SET SoDu = :SoDuTK  WHERE Ten = :TenTaiKhoan AND TenChu = :Username; ");

        qry.bindValue(":SoDuTK", SoDuTK);
        qry.bindValue(":TenTaiKhoan", TenTaiKhoan);
        qry.bindValue(":Username", Username);

        qry.exec();


    }

    ////

    //// Thêm vào bảng KhoanChi

    qry.prepare("INSERT KhoanChi ( SoTien, NgayChiTieu, GhiChu, MaDanhMuc, TenChu )" "VALUES ( :SoTien, :NgayChiTieu, :GhiChu, :MaDanhMuc, :TenChu )");

    qry.bindValue(":SoTien", SoTien);
    qry.bindValue(":NgayChiTieu", NgayChiTieu);
    qry.bindValue(":GhiChu", MoTa);
    qry.bindValue(":MaDanhMuc", MaDanhMuc);
    qry.bindValue(":TenChu", Username);

    qry.exec();

    ////

    //// Thêm tiền trong danh mục

    SoTien += DanhMucQL.LaySoTienTong(MaDanhMuc,Username);

    qry.prepare("UPDATE DanhMucChiTieu SET TongTien = :SoTien WHERE TenChu = :Username AND  dbo.DanhMucChiTieu.MaDanhMuc = :MaDanhMuc; ");

    qry.bindValue(":SoTien", SoTien);
    qry.bindValue(":Username", Username);
    qry.bindValue(":MaDanhMuc", MaDanhMuc);

    qry.exec();

    ////


}

void ChiTieu::on_btn_Huy_clicked()
{
    this->hide();
}
