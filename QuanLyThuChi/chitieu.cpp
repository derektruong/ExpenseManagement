#include "chitieu.h"
#include "ui_chitieu.h"

ChiTieu::ChiTieu(QString DanhMuc, QString username,QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::ChiTieu)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color: red");

    this->setFixedSize(671, 551);

    this->setWindowIcon(QIcon(":/Images\\Icon\\cash-icon.png"));

    this->setWindowTitle(QString::fromUtf8("Chi tiêu"));
    //

    this->Username = username;
    this->DanhMuc = DanhMuc;

    QVector<QString> DSTenTK = TaiKhoanQL.LayTenTaiKhoan(username);

    if( !DSTenTK.size() ){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có tài khoản nào!!"));
        this->close();
        ui->btn_Huy->animateClick(5);
    }

    for ( int i = 0; i < DSTenTK.size(); ++i) {
        ui->comboBox_TuTaiKhoan->addItem(DSTenTK[i]);
    }

    ui->label_DenDanhMucHienTai->setText(DanhMuc);

    // Đặt ngày dateEdit về ngày hiện tại

    QDate crrDate = QDate::currentDate();

    ui->dateEdit->setDate(crrDate);


}

ChiTieu::~ChiTieu()
{
    delete ui;
}

void ChiTieu::on_btn_OK_clicked()
{
    //Tiền xử lý dữ liệu
    QString MaDanhMuc, TenTaiKhoan, MoTa, NgayChiTieu, ThoiGianThongKe;
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

    //Kiểm tra Số tiền chi với số dư còn lại trong taikhoan
    lli SoDu = TaiKhoanQL.LaySoDu(Username, TenTaiKhoan);

    //Continue..
    if( MoTa == "" || SoTien < 0 || SoDu < SoTien){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Nhập không hợp lệ hoặc số dư không đủ!!"));
        return;
    }

    NgayChiTieu = ui->dateEdit->date().toString("yyyy-MM-dd");


    // Truy vấn DB
    QSqlQuery qry;

    ////Lấy ID_DanhMuc đưa vào bảng KhoanChi

    int ID_DanhMuc = DanhMucQL.LayID_DanhMuc(MaDanhMuc, Username);

    ////

    /// Thêm vào bảng KhoanChi

    qry.prepare("INSERT INTO KhoanChi ( SoTien, NgayChiTieu, GhiChu, TenTaiKhoan, ID_DanhMuc ) VALUES ( :SoTien, :NgayChiTieu, :GhiChu, :TenTaiKhoan, :ID_DanhMuc )");

    qry.bindValue(":SoTien", SoTien);
    qry.bindValue(":NgayChiTieu", NgayChiTieu);
    qry.bindValue(":GhiChu", MoTa);
    qry.bindValue(":TenTaiKhoan", TenTaiKhoan);
    qry.bindValue(":ID_DanhMuc", ID_DanhMuc);

    if( !qry.exec() ){
        QMessageBox::warning(this,"Nguy hiểm",QString::fromUtf8("Số tiền chi tiêu vượt quá số dư của tài khoản này!!"));
    }

    ///done


    buttonPressed();

    this->hide();


}

void ChiTieu::on_btn_Huy_clicked()
{
    this->hide();
}
