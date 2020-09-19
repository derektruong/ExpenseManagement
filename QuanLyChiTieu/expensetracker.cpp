#include "expensetracker.h"
#include "ui_expensetracker.h"

#include <changepin.h>
#include <chitieu.h>

using namespace QtCharts;



ExpenseTracker::ExpenseTracker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpenseTracker)
{
    ui->setupUi(this);
    //DataBase
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QODBC");

    myDB.setDatabaseName("DRIVER={SQL Server Native Client 11.0};SERVER=DEREKPC;DATABASE=DO_AN_CHI_TIEU;UID=sa;PWD=derek123;WSID=.;Trusted_connection=yes");

    bool connected = myDB.open();

    if(!connected) QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Lỗi! Không kết nối được CSDL!!"));

    // Hiển thị trang chủ đầu tiên khi truy cập phần mềm

    ui->stackedWidget->setCurrentIndex(0);

    ui->pushButton_TrangChinh->animateClick(10);

    // Đặt title
    this->setWindowTitle(QString::fromUtf8("Quản lý chi tiêu"));



}

ExpenseTracker::~ExpenseTracker()
{
    delete ui;
}

QString ExpenseTracker::FormatMoney(lli Tien){
    //Hiển thị tiền dễ nhìn hơn với '.'

    QStack<QChar> st;

    QString res = "";

    res = QString::number(Tien);

    int cnt = 0, i = res.size() - 1;

    while( i >= 0 ){
        st.push(res[i]);
        cnt++;
        if( !(cnt%3) && i) st.push('.');
        i--;
    }
    res="";
    while( !st.empty() ){
        res+=st.top();
        st.pop();
    }
    //qDebug()<<res;

    return  res;
}


void ExpenseTracker::on_pushButton_TrangChinh_clicked()
{
    // Làm mới trang chủ
    ui->stackedWidget->setCurrentIndex(0);
    //Đồ thị
    lli TienGD, TienSK, TienMS, TienHP, TienHD, TienKD, TienOT, TienQT, TienDC, TienGT, TienBH;

    TienGD = DanhMucQL.LaySoTienTong("GD", TenDangNhap);
    TienSK = DanhMucQL.LaySoTienTong("SK", TenDangNhap);
    TienMS = DanhMucQL.LaySoTienTong("MS", TenDangNhap);
    TienHP = DanhMucQL.LaySoTienTong("HP", TenDangNhap);
    TienHD = DanhMucQL.LaySoTienTong("HD", TenDangNhap);
    TienKD = DanhMucQL.LaySoTienTong("KD", TenDangNhap);
    TienOT = DanhMucQL.LaySoTienTong("OT", TenDangNhap);
    TienQT = DanhMucQL.LaySoTienTong("QT", TenDangNhap);
    TienDC = DanhMucQL.LaySoTienTong("DC", TenDangNhap);
    TienGT = DanhMucQL.LaySoTienTong("GT", TenDangNhap);
    TienBH = DanhMucQL.LaySoTienTong("BH", TenDangNhap);

    QPieSeries *series = new QPieSeries();

    series->append("GD", TienGD);
    series->append("SK", TienSK);
    series->append("MS", TienMS);
    series->append("HP", TienHP);
    series->append("HD", TienHD);
    series->append("KD", TienKD);
    series->append("OT", TienOT);
    series->append("QT", TienQT);
    series->append("DC", TienDC);
    series->append("GT", TienGT);
    series->append("BH", TienBH);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString::fromUtf8("Tương quan số tiền chi tiêu cho mỗi danh mục"));
    chart->theme();

    QChartView *chartView = new QChartView(chart);

    chartView->setParent(ui->frame);
    chartView->resize(831,581);
    chartView->show();


    //

    ui->label_MainMoney->setText(TaiKhoanQL.TinhTongSoDu(TenDangNhap)+"đ");
    if(countMain < 1 ){
        QVector<QString> DSTenTK = TaiKhoanQL.LayTenTaiKhoan(TenDangNhap);

        for ( int i = 0; i < DSTenTK.size(); ++i) {
            ui->comboBox->addItem(DSTenTK[i]);
        }
    }

    countMain++;

    //ui->comboBox->
    if( ui->comboBox->currentIndex() ){
        lli SoDu = 0;

        SoDu = TaiKhoanQL.LaySoDu(TenDangNhap, ui->comboBox->currentText());

        ui->label_MainMoney->setText(FormatMoney(SoDu) + "đ");

        ui->pushButton_TrangChinh->animateClick(2);
    }



    QSqlQuery qry("SELECT * FROM dbo.NguoiDung nd WHERE nd.TenDangNhap = '"+TenDangNhap+"'");
    while( qry.next() ){
        this->HoTen = qry.value("HoVaTen").toString();
    }
    ui->label_HoVaTen_page1->setText(this->HoTen);

    //Hiển thị tiền tại các danh mục



    //Hiển thị số tiền
    ui->label_GiaDinh_money->setText(FormatMoney(TienGD) + "đ");
    ui->label_SucKhoe_money->setText(FormatMoney(TienSK) + "đ");
    ui->label_MuaSam_money->setText(FormatMoney(TienMS) + "đ");
    ui->label_HocPhi_money->setText(FormatMoney(TienHP) + "đ");
    ui->label_HoaDon_money->setText(FormatMoney(TienHD) + "đ");
    ui->label_KinhDoanh_money->setText(FormatMoney(TienKD) + "đ");
    ui->label_Khac_money->setText(FormatMoney(TienOT) + "đ");
    ui->label_QuaTang_money->setText(FormatMoney(TienQT) + "đ");
    ui->label_DiChuyen_money->setText(FormatMoney(TienDC) + "đ");
    ui->label_GiaiTri_money->setText(FormatMoney(TienGT) + "đ");
    ui->label_BachHoa_money->setText(FormatMoney(TienBH) + "đ");


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
    qryModel = new QSqlQueryModel();
    qryModel->setQuery("SELECT Loai,Ten,SoDu,MoTa FROM dbo.TaiKhoan tk WHERE tk.TenChu = '"+TenDangNhap+"'");
    //Chỉnh độ rộng
    ui->tableView_page4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //Chỉnh tên cho cột
    qryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Loại"));
    qryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Tên"));
    qryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Số dư (VNĐ)"));
    qryModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Mô tả"));

    ui->tableView_page4->setModel(qryModel);
    ui->tableView_page4->update();
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

    this->HoTen = HoVaTen;

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
    this->resize(1361,951);
}

//Thay mã pin
void ExpenseTracker::on_pushButton_ThayMaPin_clicked()
{
    ChangePin ThayPin;
    ThayPin.TenDangNhap = TenDangNhap;
    ThayPin.setModal(true);
    ThayPin.exec();
}
// Page Tài Khoản

void ExpenseTracker::on_btn_page4_Them_clicked()
{
    //Pre Processing

    QString LoaiTaiKhoan, TenTaiKhoan, MoTa;
    int inTotal;
    lli SoDu;


    LoaiTaiKhoan = ui->comboBox_p4_LoaiTaiKhoan->currentText();
    TenTaiKhoan = ui->lineEdit_p4_TenTaiKhoan->text();
    MoTa = ui->textEdit_p4_MoTa->toPlainText();
    if( ui->radioButton_Co->isChecked() ) inTotal = 1;
    else inTotal = 0;

    //Kiểm tra hợp lệ số dư
    for ( int i = 0; i < ui->lineEdit_p4_SoDu->text().size(); ++i) {
        if(ui->lineEdit_p4_SoDu->text()[0] =='0') {
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số tiền nhập không hợp lệ chỉ gồm các chữ số"));
            return;
        }
        if( ui->lineEdit_p4_SoDu->text()[i] < 48 || ui->lineEdit_p4_SoDu->text()[i] > 57 ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số tiền nhập không hợp lệ chỉ gồm các chữ số"));
            return;
        }
    }

    //

    SoDu = (ui->lineEdit_p4_SoDu->text()).toLongLong();

    //qDebug()<<LoaiTaiKhoan<<" "<<TenTaiKhoan<<" "<<MoTa<<" "<<inTotal<<" "<<SoDu;

    QSqlQuery qry;

    qry.prepare("INSERT INTO TaiKhoan( Loai,Ten,SoDu,BaoGomTrongTongSoDu,TenChu,MoTa )" "VALUES( :Loai, :Ten, :SoDu, :BaoGomTrongTongSoDu, :TenChu, :MoTa)");

    qry.bindValue(":Loai", LoaiTaiKhoan);
    qry.bindValue(":Ten", TenTaiKhoan);
    qry.bindValue(":SoDu", SoDu);
    qry.bindValue(":BaoGomTrongTongSoDu", inTotal);
    qry.bindValue(":TenChu", TenDangNhap);
    qry.bindValue(":MoTa", MoTa);
    if( qry.exec() ){

        QMessageBox::information(this, QString::fromUtf8("Thông báo"), QString::fromUtf8("Bạn đã thêm tài khoản thành công!!"));

        qryModel = new QSqlQueryModel();
        qryModel->setQuery("SELECT Loai,Ten,SoDu,MoTa FROM dbo.TaiKhoan tk WHERE tk.TenChu = '"+TenDangNhap+"'");
        ui->tableView_page4->setModel(qryModel);
        //Chỉnh độ rộng
        ui->tableView_page4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //Chỉnh tên cho cột
        qryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Loại"));
        qryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Tên"));
        qryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Số dư (VNĐ)"));
        qryModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Mô tả"));

        ui->tableView_page4->update();

    }


    else{
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Không thể thêm tài khoản!!"));
        return;
    }
}

void ExpenseTracker::on_btn_GiaDinhPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Gia Đình"), TenDangNhap);
    WinChiTieu.setModal(true);
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_SucKhoePic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Sức Khoẻ"), TenDangNhap);
    WinChiTieu.setModal(true);
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_MuaSamPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Mua Sắm"), TenDangNhap);
    WinChiTieu.setModal(true);
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_HocPhiPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Học Phí"), TenDangNhap);
    WinChiTieu.setModal(true);
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_HoaDonPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Hoá Đơn"), TenDangNhap);
    WinChiTieu.setModal(true);
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_KinhDoanhPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Kinh Doanh"), TenDangNhap);
    WinChiTieu.setModal(true);
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_KhacPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Khác"), TenDangNhap);
    WinChiTieu.setModal(true);
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_QuaTangPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Quà Tặng"), TenDangNhap);
    WinChiTieu.setModal(true);
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_DiChuyenPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Di Chuyển"), TenDangNhap);
    WinChiTieu.setModal(true);
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_GiaiTriPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Giải Trí"), TenDangNhap);
    WinChiTieu.setModal(true);
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_BachHoaPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Bách Hoá"), TenDangNhap);
    WinChiTieu.setModal(true);
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_Refresh_clicked()
{
    ui->pushButton_TrangChinh->animateClick(2);
}

void ExpenseTracker::on_btn_ThemTaiKhoan_clicked()
{
    ui->pushButton_TaiKhoan->animateClick(2);
}
