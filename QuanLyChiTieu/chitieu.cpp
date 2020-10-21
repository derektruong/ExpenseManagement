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

    //Cập nhật thông tin thu nhập cho bảng ThongKe
    ThoiGianThongKe = ui->dateEdit->date().toString("yyyy-MM-dd");
    ThongKeQL.CapNhatTongChi(this->Username, ThoiGianThongKe, SoTien);

    //done

    //Continue..
    if( MoTa == "" ||  SoTien < 0){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Nhập không hợp lệ !!"));
        return;
    }

    NgayChiTieu = ui->dateEdit->date().toString("yyyy/MM/dd");


    // Truy vấn DB
    QSqlQuery qry;

    lli SoDuTK = TaiKhoanQL.LaySoDu(Username,TenTaiKhoan);

    SoDuTK -= SoTien;
    //Lấy mã tài khoản
    int MTK = TaiKhoanQL.LayMaTaiKhoan(this->Username, TenTaiKhoan);


    //Kiểm tra có đủ số dư trong tài khoản hay không
    if( SoDuTK < 0 ){
        QMessageBox::warning(this,"Nguy hiểm",QString::fromUtf8("Số tiền chi tiêu vượt quá số dư của tài khoản này!!"));
        return;
    }

    else{
        //Trừ trong bảng TietKiem nếu có
        if( TaiKhoanQL.LayLoaiTaiKhoan(this->Username, TenTaiKhoan) == "Tiết kiệm" ){
            TietKiemQL.CapNhatSoDu(this->Username, MTK, SoDuTK);
        }
        //done

        // Trừ tiền trong tài khoản
        qry.prepare("UPDATE TaiKhoan SET SoDu = :SoDuTK  WHERE Ten = :TenTaiKhoan AND TenChu = :Username; ");

        qry.bindValue(":SoDuTK", SoDuTK);
        qry.bindValue(":TenTaiKhoan", TenTaiKhoan);
        qry.bindValue(":Username", Username);

        qry.exec();
        //done


    }

    //

    /// Thêm tiền trong danh mục

    SoTien += DanhMucQL.LaySoTienTong(MaDanhMuc, Username);

    qry.prepare("UPDATE DanhMucChiTieu SET TongTien = :SoTien WHERE TenChu = :Username AND  MaDanhMuc = :MaDanhMuc; ");

    qry.bindValue(":SoTien", SoTien);
    qry.bindValue(":Username", Username);
    qry.bindValue(":MaDanhMuc", MaDanhMuc);

    qry.exec();

    ///done

    ////Lấy ID_DanhMuc đưa vào bảng KhoanChi

    int ID_DanhMuc = DanhMucQL.LayID_DanhMuc(MaDanhMuc, Username);

    ////

    /// Thêm vào bảng KhoanChi

    qry.prepare("INSERT KhoanChi ( SoTien, NgayChiTieu, GhiChu, MaDanhMuc, TenChu, TenTaiKhoan, ID_DanhMuc )" "VALUES ( :SoTien, :NgayChiTieu, :GhiChu, :MaDanhMuc, :TenChu, :TenTaiKhoan, :ID_DanhMuc )");

    qry.bindValue(":SoTien", SoTien);
    qry.bindValue(":NgayChiTieu", NgayChiTieu);
    qry.bindValue(":GhiChu", MoTa);
    qry.bindValue(":MaDanhMuc", MaDanhMuc);
    qry.bindValue(":TenChu", Username);
    qry.bindValue(":TenTaiKhoan", TenTaiKhoan);
    qry.bindValue(":ID_DanhMuc", ID_DanhMuc);

    qry.exec();

    ///done


    buttonPressed();

    this->hide();


}

void ChiTieu::on_btn_Huy_clicked()
{
    this->hide();
}
