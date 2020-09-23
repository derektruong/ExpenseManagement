#include "expensetracker.h"
#include "ui_expensetracker.h"

#include <changepin.h>
//#include <chitieu.h>

using namespace QtCharts;


ExpenseTracker::ExpenseTracker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpenseTracker)
{
    ui->setupUi(this);
    this->setFixedSize(1320,701);

    // Hiển thị trang chủ đầu tiên khi truy cập phần mềm

    ui->stackedWidget->setCurrentIndex(0);

    ui->pushButton_TrangChinh->animateClick(10);

    // Đặt title
    this->setWindowTitle(QString::fromUtf8("Quản lý chi tiêu"));

    // Đặt ngày dateEdit về ngày hiện tại

    QDate crrDate = QDate::currentDate();

    ui->dateEdit_p3_NgayThuNhap->setDate(crrDate);

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

void ExpenseTracker::RefreshP1(){
    ui->pushButton_TrangChinh->animateClick(5);
}

void ExpenseTracker::RefreshP2(){
    ui->pushButton_ChiTieu->animateClick(5);

}

void ExpenseTracker::RefreshP3(){
    ui->pushButton_ThuNhap->animateClick(5);

}

void ExpenseTracker::RefreshP4(){
    ui->pushButton_TaiKhoan->animateClick(5);
}

void ExpenseTracker::UpdateTableP4(){
    qryModel = new QSqlQueryModel();
    qryModel->setQuery("SELECT Loai,Ten,SoDu,MoTa FROM TaiKhoan WHERE TenChu = '"+TenDangNhap+"'");
    //Chỉnh độ rộng
    ui->tableView_page4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_page4->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //Chỉnh tên cho cột
    qryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Loại"));
    qryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Tên"));
    qryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Số dư (VNĐ)"));
    qryModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Mô tả"));

    ui->tableView_page4->setModel(qryModel);
    ui->tableView_page4->update();

    //delete qryModel;
}


void ExpenseTracker::on_pushButton_TrangChinh_clicked()
{
    // Làm mới trang chủ
    ui->stackedWidget->setCurrentIndex(0);
    ui->comboBox->clear();
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
    QPieSlice *slice;
    int cnt = 0;

    if( TienGD > 0 ){
        series->append("GD", TienGD);
        slice = series->slices().takeAt(cnt);
        slice->setColor(Qt::blue);
        slice->setLabelColor(Qt::white);
        cnt++;
    }

    if( TienSK > 0 ){
        series->append("SK", TienSK);
        slice = series->slices().takeAt(cnt);
        slice->setBrush(QColor::fromRgb(218, 44, 56));
        slice->setLabelColor(Qt::white);
        cnt++;
    }

    if( TienMS > 0 ){
        series->append("MS", TienMS);
        slice = series->slices().takeAt(cnt);
        slice->setBrush(QColor::fromRgb(33, 209, 159));
        slice->setLabelColor(Qt::white);
        cnt++;
    }
    if( TienHP > 0 ){
        series->append("HP", TienHP);
        slice = series->slices().takeAt(cnt);
        slice->setBrush(QColor::fromRgb(255, 188, 66));
        slice->setLabelColor(Qt::white);
        cnt++;
    }

    if( TienHD > 0 ){
        series->append("HD", TienHD);
        slice = series->slices().takeAt(cnt);
        slice->setBrush(QColor::fromRgb(250, 163, 129));
        slice->setLabelColor(Qt::white);
        cnt++;
    }

    if( TienKD > 0 ){
        series->append("KD", TienKD);
        slice = series->slices().takeAt(cnt);
        slice->setBrush(QColor::fromRgb(255, 184, 209));
        slice->setLabelColor(Qt::white);
        cnt++;
    }

    if( TienOT > 0 ){
        series->append("OT", TienOT);
        slice = series->slices().takeAt(cnt);
        slice->setBrush(QColor::fromRgb(128, 35, 146));
        slice->setLabelColor(Qt::white);
        cnt++;
    }

    if( TienQT > 0 ){
        series->append("QT", TienQT);
        slice = series->slices().takeAt(cnt);
        slice->setBrush(QColor::fromRgb(235, 245, 238));
        slice->setLabelColor(Qt::white);
        cnt++;
    }

    if( TienDC > 0 ){
        series->append("DC", TienDC);
        slice = series->slices().takeAt(cnt);
        slice->setBrush(QColor::fromRgb(144, 252, 249));
        slice->setLabelColor(Qt::white);
        cnt++;
    }

    if( TienGT > 0 ){
        series->append("GT", TienGT);
        slice = series->slices().takeAt(cnt);
        slice->setBrush(QColor::fromRgb(35, 46, 33));
        slice->setLabelColor(Qt::white);
        cnt++;
    }

    if( TienBH > 0 ){
        series->append("BH", TienBH);
        slice = series->slices().takeAt(cnt);
        slice->setBrush(QColor::fromRgb(55, 62, 64));
        slice->setLabelColor(Qt::white);
        cnt++;
    }


    //

    series->setHoleSize(0.35);
    series->setLabelsVisible(true);
    series->setPieSize(0.7);

    QChart *chart = new QChart();
    chart->addSeries(series);

    chart->setAnimationOptions(QChart::SeriesAnimations);
    ///Title
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setFont(font);
    chart->setTitle(QString::fromUtf8("Tương quan số tiền chi tiêu cho mỗi danh mục"));
    //chart->setTheme(QChart::ChartThemeBlueCerulean);
    //chart->setBackgroundVisible(false);
    chart->setBackgroundBrush(QColor::fromRgb(255, 252, 249, 120));


    QChartView *chartView = new QChartView(chart);

    chartView->setParent(ui->frame);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(761, 441);
    chartView->show();


    //Xử lý combobox
    ui->comboBox->addItem("Tổng số dư: " + TaiKhoanQL.TinhTongSoDu(TenDangNhap)+"đ");


    QVector<QString> DSTenTK = TaiKhoanQL.LayTenTaiKhoan(TenDangNhap);
    for ( int i = 0; i < DSTenTK.size(); ++i) {

            ui->comboBox->addItem(DSTenTK[i] + ": " + FormatMoney(TaiKhoanQL.LaySoDu(TenDangNhap, DSTenTK[i])) + "đ");
            //SetVisP1.insert(DSTenTK[i]);


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
    //
    ui->comboBox_p2_TenTaiKhoan->clear();

    ui->comboBox_p2_TenTaiKhoan->addItem("Tất Cả");

    QVector<QString> DSTenTK = TaiKhoanQL.LayTenTaiKhoan(TenDangNhap);

    if( ui->tab1_P2->isActiveWindow() ){

        if( !DSTenTK.size() ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có tài khoản nào!!"));
        }

        for ( int i = 0; i < DSTenTK.size(); ++i) {
            ui->comboBox_p2_TenTaiKhoan->addItem(DSTenTK[i]);
        }
    }

}

void ExpenseTracker::on_pushButton_ThuNhap_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

    ui->comboBox_p3_DenTaiKhoan_tab1->clear();
    ui->comboBox_p3_LoaiThuNhap_tab1->clear();

    QVector<QString> DSTenTK = TaiKhoanQL.LayTenTaiKhoan(TenDangNhap);
    QVector<QString> DSLoaiThuNhap = ThuNhapQL.LayTenThuNhap(TenDangNhap);

    if( ui->tab1_P3->isActiveWindow() ){
        //Thêm vào combobox TK
        if( !DSTenTK.size() ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có tài khoản nào!!"));
        }

        for ( int i = 0; i < DSTenTK.size(); ++i) {
            ui->comboBox_p3_DenTaiKhoan_tab1->addItem(DSTenTK[i]);
        }

        //Thêm vào combobox Thu Nhập
        if( !DSLoaiThuNhap.size() ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có loại thu nhập nào, vui lòng thêm thu nhập"));
        }

        for ( int i = 0; i < DSLoaiThuNhap.size(); ++i) {
            ui->comboBox_p3_LoaiThuNhap_tab1->addItem(DSLoaiThuNhap[i]);
        }

    }


    qryModel = new QSqlQueryModel();
    qryModel->setQuery("SELECT TOP 10 LoaiThuNhap AS N'Loại thu nhập', SoTien AS N'Số tiền', TenTaiKhoan AS N'Đến tài khoản', NgayThuNhap AS N'Thời gian', GhiChu AS N'Ghi chú'  FROM ThuNhap WHERE TenChu = '"+TenDangNhap+"' ");
    //Chỉnh độ rộng
    ui->tableView_page3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_page3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //

    ui->tableView_page3->setModel(qryModel);
    ui->tableView_page3->update();


}

void ExpenseTracker::on_pushButton_TaiKhoan_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ///

    UpdateTableP4();

    ui->comboBox_p4_TenTaiKhoan->clear();
    ui->comboBox_p4_TenTaiKhoan_Xoa->clear();

    ///

    QVector<QString> DSTenTK = TaiKhoanQL.LayTenTaiKhoan(TenDangNhap);
    // Tiền xử lý tab thêm số dư
    if( ui->tab_2->isActiveWindow() ){

        if( !DSTenTK.size() ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có tài khoản nào!!"));
        }

        for ( int i = 0; i < DSTenTK.size(); ++i) {
            ui->comboBox_p4_TenTaiKhoan->addItem(DSTenTK[i]);
        }
    }


    //

    // Tiền xử lý tab xoá tài khoản
    if( ui->tab_3->isActiveWindow() ){

        if( !DSTenTK.size() ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có tài khoản nào!!"));
        }

        for ( int i = 0; i < DSTenTK.size(); ++i) {
            ui->comboBox_p4_TenTaiKhoan_Xoa->addItem(DSTenTK[i]);
        }
    }


    //
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

//Thay mã pin
void ExpenseTracker::on_pushButton_ThayMaPin_clicked()
{
    ChangePin ThayPin;
    ThayPin.TenDangNhap = TenDangNhap;
    ThayPin.setModal(true);
    ThayPin.exec();
}
// Page Tài Khoản

void ExpenseTracker::on_btn_page4_ThemTK_clicked()
{
    //Pre Processing

    QString LoaiTaiKhoan, TenTaiKhoan, MoTa;
    int inTotal = -1;
    lli SoDu;


    LoaiTaiKhoan = ui->comboBox_p4_LoaiTaiKhoan->currentText();
    TenTaiKhoan = ui->lineEdit_p4_TenTaiKhoan->text();
    MoTa = ui->textEdit_p4_MoTa->toPlainText();
    if( ui->radioButton_Co->isChecked() ) inTotal = 1;
    else inTotal = 0;

    //Kiểm tra hợp lệ số dư
    for ( int i = 0; i < ui->lineEdit_p4_SoDu->text().size(); ++i) {
        if(ui->lineEdit_p4_SoDu->text()[0].unicode() - 48 < 0) {
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số tiền nhập không hợp lệ!"));
            return;
        }
        if( ui->lineEdit_p4_SoDu->text()[i] < 48 || ui->lineEdit_p4_SoDu->text()[i] > 57 ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số tiền nhập không hợp lệ chỉ gồm các chữ số"));
            return;
        }
    }

    //Kiểm tra hợp lệ nhập

    if(TenTaiKhoan == "" || inTotal == -1 || !ui->lineEdit_p4_SoDu->text().size() ){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Phải nhập đủ!"));
        return;
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

        RefreshP4();

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
    connect(&WinChiTieu,SIGNAL(buttonPressed()), this, SLOT(RefreshP1()));
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_SucKhoePic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Sức Khoẻ"), TenDangNhap);
    WinChiTieu.setModal(true);
    connect(&WinChiTieu,SIGNAL(buttonPressed()), this, SLOT(RefreshP1()));
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_MuaSamPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Mua Sắm"), TenDangNhap);
    WinChiTieu.setModal(true);
    connect(&WinChiTieu,SIGNAL(buttonPressed()), this, SLOT(RefreshP1()));
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_HocPhiPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Học Phí"), TenDangNhap);
    WinChiTieu.setModal(true);
    connect(&WinChiTieu,SIGNAL(buttonPressed()), this, SLOT(RefreshP1()));
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_HoaDonPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Hoá Đơn"), TenDangNhap);
    WinChiTieu.setModal(true);
    connect(&WinChiTieu,SIGNAL(buttonPressed()), this, SLOT(RefreshP1()));
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_KinhDoanhPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Kinh Doanh"), TenDangNhap);
    WinChiTieu.setModal(true);
    connect(&WinChiTieu,SIGNAL(buttonPressed()), this, SLOT(RefreshP1()));
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_KhacPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Khác"), TenDangNhap);
    WinChiTieu.setModal(true);
    connect(&WinChiTieu,SIGNAL(buttonPressed()), this, SLOT(RefreshP1()));
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_QuaTangPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Quà Tặng"), TenDangNhap);
    WinChiTieu.setModal(true);
    connect(&WinChiTieu,SIGNAL(buttonPressed()), this, SLOT(RefreshP1()));
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_DiChuyenPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Di Chuyển"), TenDangNhap);
    WinChiTieu.setModal(true);
    connect(&WinChiTieu,SIGNAL(buttonPressed()), this, SLOT(RefreshP1()));
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_GiaiTriPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Giải Trí"), TenDangNhap);
    WinChiTieu.setModal(true);
    connect(&WinChiTieu,SIGNAL(buttonPressed()), this, SLOT(RefreshP1()));
    WinChiTieu.exec();
}

void ExpenseTracker::on_btn_BachHoaPic_clicked()
{
    ChiTieu WinChiTieu(QString::fromUtf8("Bách Hoá"), TenDangNhap);
    WinChiTieu.setModal(true);
    connect(&WinChiTieu,SIGNAL(buttonPressed()), this, SLOT(RefreshP1()));
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

//page4_ThemSoDu
void ExpenseTracker::on_btn_page4_ThemSoDu_clicked()
{
    QString TenTaiKhoan, MoTa;
    lli SoTien;

    TenTaiKhoan = ui->comboBox_p4_TenTaiKhoan->currentText();

    MoTa = ui->textEdit_p4_MoTa_2->toPlainText();

    //Kiểm tra hợp lệ số tiền
    for ( int i = 0; i < ui->lineEdit_p4_SoTien->text().size(); ++i) {
        if(ui->lineEdit_p4_SoTien->text()[0] =='0') {
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số tiền nhập không hợp lệ chỉ gồm các chữ số"));
            return;
        }
        if( ui->lineEdit_p4_SoTien->text()[i] < 48 || ui->lineEdit_p4_SoTien->text()[i] > 57 ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số tiền nhập không hợp lệ chỉ gồm các chữ số"));
            return;
        }
    }

    SoTien = ui->lineEdit_p4_SoTien->text().toLongLong();

    if( SoTien < 0 ){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Nhập không hợp lệ !!"));
        return;
    }

    // Truy vấn DB
    QSqlQuery qry;

    lli SoDuTK = TaiKhoanQL.LaySoDu(TenDangNhap,TenTaiKhoan);

    SoDuTK += SoTien;

    if( MoTa != "" ) qry.prepare("UPDATE TaiKhoan SET SoDu = :SoDuTK, MoTa = :MoTa  WHERE Ten = :TenTaiKhoan AND TenChu = :Username; ");
    else qry.prepare("UPDATE TaiKhoan SET SoDu = :SoDuTK WHERE Ten = :TenTaiKhoan AND TenChu = :Username; ");
    qry.bindValue(":SoDuTK", SoDuTK);
    if( MoTa != "" ) qry.bindValue(":MoTa", MoTa);
    qry.bindValue(":TenTaiKhoan", TenTaiKhoan);
    qry.bindValue(":Username", TenDangNhap);

    if( qry.exec() ){
        RefreshP4();
    }
    else{
        QMessageBox::warning(this,"Lỗi",QString::fromUtf8("Thêm không thành công!!"));
    }

    //done

}
//page4_XoaTaiKhoan
void ExpenseTracker::on_btn_page4_XoaTaiKhoan_clicked()
{
    QString TenTaiKhoan;
    TenTaiKhoan = ui->comboBox_p4_TenTaiKhoan_Xoa->currentText();

    if( TenTaiKhoan == ""){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Không có thẻ nào được chọn !!"));
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Cảnh báo", "Bạn có chắc muốn xoá tài khoản "+TenTaiKhoan+" không", QMessageBox::Yes|QMessageBox::No);

    if( reply == QMessageBox::Yes ){
        QSqlQuery qry;

        qry.prepare("DELETE FROM TaiKhoan WHERE TenChu = :Username AND TaiKhoan.Ten = :TenTaiKhoan ");

        qry.bindValue(":TenTaiKhoan", TenTaiKhoan);
        qry.bindValue(":Username", TenDangNhap);

        if( qry.exec() ){
            RefreshP4();
        }
        else QMessageBox::warning(this,"Lỗi",QString::fromUtf8("Xoá không thành công !!"));
    }

    else return;


}

void ExpenseTracker::on_btn_p2_TimTheoNgay_clicked()
{
    QString Ngay;

    Ngay = ui->calendarWidget_p2->selectedDate().toString("yyyy-MM-dd");

    if( Ngay == ""){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Lỗi không xác nhận được ngày !!"));
        return;
    }

    //qDebug()<<Ngay;

    //Truy vấn DB

    QSqlQuery qry;

    qry.prepare("SELECT TOP 10  SoTien AS N'Số tiền(VNĐ)', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản' FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND NgayChiTieu = '"+Ngay+"' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
    if( qry.exec() ){

        int count = 0;
        while( qry.next() ){
            count++;
        }

        if( count < 1 ){
            QMessageBox::warning(this,"Thông báo",QString::fromUtf8("Không có ngày nào được tìm thấy!!"));
            return;
        }

    }

    qryModel = new QSqlQueryModel();
    qryModel->setQuery(qry);
    //Chỉnh độ rộng
    ui->tableView_page2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_page2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_page2->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    //

    ui->tableView_page2->setModel(qryModel);
    ui->tableView_page2->update();


}


void ExpenseTracker::on_btn_p2_TimTheoThang_clicked()
{
    QString Thang;

    Thang = ui->calendarWidget_p2->selectedDate().toString("MM");

    if( Thang == ""){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Lỗi không xác nhận được tháng !!"));
        return;
    }

    //qDebug()<<Ngay;

    //Truy vấn DB

    QSqlQuery qry;

    qry.prepare("SELECT TOP 10  SoTien AS N'Số tiền(VNĐ)', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản' FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND Month(NgayChiTieu) = '"+Thang+"' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
    if( qry.exec() ){

        int count = 0;
        while( qry.next() ){
            count++;
        }

        if( count < 1 ){
           QMessageBox::warning(this,"Thông báo",QString::fromUtf8("Không có tháng nào được tìm thấy!!"));
           return;
        }

    }

    qryModel = new QSqlQueryModel();
    qryModel->setQuery(qry);
    //Chỉnh độ rộng
    ui->tableView_page2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_page2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //

    ui->tableView_page2->setModel(qryModel);
    ui->tableView_page2->update();
}

void ExpenseTracker::on_btn_p2_TimTheoNam_clicked()
{
    QString Nam;

    Nam = ui->calendarWidget_p2->selectedDate().toString("yyyy");

    if( Nam == ""){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Lỗi không xác nhận được năm !!"));
        return;
    }

    //qDebug()<<Ngay;

    //Truy vấn DB

    QSqlQuery qry;

    qry.prepare("SELECT TOP 10  SoTien AS N'Số tiền(VNĐ)', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản' FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND Year(NgayChiTieu) = '"+Nam+"' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
    if( qry.exec() ){

        int count = 0;
        while( qry.next() ){
            count++;
        }

        if( count < 1 ){
           QMessageBox::warning(this,"Thông báo",QString::fromUtf8("Không có năm nào được tìm thấy!!"));
           return;
        }

    }

    qryModel = new QSqlQueryModel();
    qryModel->setQuery(qry);
    //Chỉnh độ rộng
    ui->tableView_page2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_page2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //

    ui->tableView_page2->setModel(qryModel);
    ui->tableView_page2->update();
}

void ExpenseTracker::on_btn_p2_TimKiemChung_clicked()
{
    QString TenDanhMuc, MaDanhMuc, TenTaiKhoan, Key;

    TenDanhMuc = ui->comboBox_p2_TenDanhMuc->currentText();
    TenTaiKhoan = ui->comboBox_p2_TenTaiKhoan->currentText();
    Key = ui->lineEdit_p2_MoTa->text();

    if( TenDanhMuc == "Gia Đình" ) MaDanhMuc = "GD";
    if( TenDanhMuc == "Sức Khoẻ" ) MaDanhMuc = "SK";
    if( TenDanhMuc == "Mua Sắm" ) MaDanhMuc = "MS";
    if( TenDanhMuc == "Học Phí" ) MaDanhMuc = "HP";
    if( TenDanhMuc == "Hoá Đơn" ) MaDanhMuc = "HD";
    if( TenDanhMuc == "Kinh Doanh" ) MaDanhMuc = "KD";
    if( TenDanhMuc == "Khác" ) MaDanhMuc = "OT";
    if( TenDanhMuc == "Quà Tặng" ) MaDanhMuc = "QT";
    if( TenDanhMuc == "Di Chuyển" ) MaDanhMuc = "DC";
    if( TenDanhMuc == "Giải Trí" ) MaDanhMuc = "GT";
    if( TenDanhMuc == "Bách Hoá" ) MaDanhMuc = "BH";


    QSqlQuery qry;

    if( TenDanhMuc == "Tất Cả" && TenTaiKhoan == "Tất Cả" ){
        qry.prepare("SELECT TOP 10 SoTien AS N'Số tiền', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản'  FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND GhiChu LIKE N'%"+Key+"%' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
    }

    if( TenDanhMuc != "Tất Cả" && TenTaiKhoan == "Tất Cả" ){
        qry.prepare("SELECT TOP 10 SoTien AS N'Số tiền', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản'  FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND MaDanhMuc = '"+MaDanhMuc+"'  AND GhiChu LIKE N'%"+Key+"%' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
    }

    if( TenDanhMuc == "Tất Cả" && TenTaiKhoan != "Tất Cả" ){
        qry.prepare("SELECT TOP 10 SoTien AS N'Số tiền', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản'  FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND TenTaiKhoan = N'"+TenTaiKhoan+"' AND GhiChu LIKE N'%"+Key+"%' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
    }

    if( TenDanhMuc != "Tất Cả" && TenTaiKhoan != "Tất Cả" ){
        qry.prepare("SELECT TOP 10 SoTien AS N'Số tiền', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản'  FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND MaDanhMuc = '"+MaDanhMuc+"' AND TenTaiKhoan = N'"+TenTaiKhoan+"' AND GhiChu LIKE N'%"+Key+"%' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
    }

    if( qry.exec() ){

        int count = 0;
        while( qry.next() ){
            count++;
        }

        if( count < 1 ){
           QMessageBox::warning(this,"Thông báo",QString::fromUtf8("Không có thông tin nào khớp với kết quả được tìm thấy hoặc bạn nhập không đủ dấu!!"));
           return;
        }

    }

    qryModel = new QSqlQueryModel();
    qryModel->setQuery(qry);

    //Chỉnh độ rộng
    ui->tableView_page2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_page2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //

    ui->tableView_page2->setModel(qryModel);
    ui->tableView_page2->sortByColumn(0,Qt::DescendingOrder);
    ui->tableView_page2->update();

}

//Xác nhận thêm tiền vào loại thu nhập đã có
void ExpenseTracker::on_btn_p3_XacNhan_clicked()
{
    QString LoaiThuNhap, TenTaiKhoan, NgayThuNhap, GhiChu;
    lli SoTien;

    LoaiThuNhap = ui->comboBox_p3_LoaiThuNhap_tab1->currentText();
    TenTaiKhoan = ui->comboBox_p3_DenTaiKhoan_tab1->currentText();
    GhiChu = ui->textEdit_p3_GhiChu->toPlainText();

    //Kiểm tra hợp lệ số tiền
    for ( int i = 0; i < ui->lineEdit_p3_SoTien->text().size(); ++i) {
        if(ui->lineEdit_p3_SoTien->text()[0] =='0') {
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số tiền nhập không hợp lệ chỉ gồm các chữ số"));
            return;
        }
        if( ui->lineEdit_p3_SoTien->text()[i] < 48 || ui->lineEdit_p3_SoTien->text()[i] > 57 ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số tiền nhập không hợp lệ chỉ gồm các chữ số"));
            return;
        }
    }

    //

    SoTien = ui->lineEdit_p3_SoTien->text().toLongLong();

    if( LoaiThuNhap == "" || TenTaiKhoan == "" || SoTien < 0){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Nhập không hợp lệ !!"));
        return;
    }

    NgayThuNhap = ui->dateEdit_p3_NgayThuNhap->text();

    //Định dạng lại format date cho phù hợp với DBase
    QStack<QString> st;

    int s = 0;

    for ( int i = 0; i < NgayThuNhap.size(); ++i) {
        if( NgayThuNhap[i] == '/' ){
            st.push(QString::number(s));
            st.push("/");
            s = 0;
            continue;
        }
        s = s*10 + (NgayThuNhap[i].unicode() - 48);

    }

    st.push(QString::number(s));

    NgayThuNhap = "";

    while ( !st.empty() ) {
        NgayThuNhap+=st.top();
        st.pop();
    }
    //done

    // Truy vấn DB

    QSqlQuery qry;

    /// Cộng tiền vào tài khoản

    lli SoDuTK = TaiKhoanQL.LaySoDu(TenDangNhap,TenTaiKhoan);

    SoDuTK += SoTien;

    qry.prepare("UPDATE TaiKhoan SET SoDu = :SoDuTK  WHERE Ten = :TenTaiKhoan AND TenChu = :Username; ");

    qry.bindValue(":SoDuTK", SoDuTK);
    qry.bindValue(":TenTaiKhoan", TenTaiKhoan);
    qry.bindValue(":Username", TenDangNhap);

    if( qry.exec() ){
        qDebug()<<"Đã thêm thành công!";
    }
    else QMessageBox::warning(this,"Lỗi",QString::fromUtf8("Thêm không thành công !!"));

    /// done

    /// Thêm vào thu nhập

    qry.prepare("INSERT ThuNhap ( LoaiThuNhap, SoTien, GhiChu, TenChu, TenTaiKhoan, NgayThuNhap )" "VALUES ( :LoaiThuNhap, :SoTien, :GhiChu, :TenChu, :TenTaiKhoan, :NgayThuNhap )");

    qry.bindValue(":LoaiThuNhap", LoaiThuNhap);
    qry.bindValue(":SoTien", SoTien);
    qry.bindValue(":GhiChu", GhiChu);
    qry.bindValue(":TenChu", TenDangNhap);
    qry.bindValue(":TenTaiKhoan", TenTaiKhoan);
    qry.bindValue(":NgayThuNhap", NgayThuNhap);

    if( qry.exec() ){
        RefreshP3();
    }
    else QMessageBox::warning(this,"Lỗi",QString::fromUtf8("Thêm không thành công !!"));

    /// done

}

//Xác nhận thêm loại thu nhập
void ExpenseTracker::on_btn_p3_XacNhan_tab2_clicked()
{
    QString LoaiThuNhap, GhiChu;

    LoaiThuNhap = ui->lineEdit_p3_LoaiThuNhap_tab2->text();
    GhiChu = ui->textEdit_p3_GhiChu_tab2->toPlainText();

    if( LoaiThuNhap == "" ){
        QMessageBox::information(this,"Chú ý","Bạn phải nhập loại thu nhập");
        return;
    }

    // Truy vấn DB

    QSqlQuery qry;

    qry.prepare("INSERT LoaiThuNhap ( LoaiThuNhap, GhiChu, TenChu )" "VALUES (  :LoaiThuNhap,  :GhiChu,  :TenChu  ) ");

    qry.bindValue(":LoaiThuNhap", LoaiThuNhap);;
    qry.bindValue(":GhiChu", GhiChu);
    qry.bindValue(":TenChu", TenDangNhap);

    if( qry.exec() ){
        RefreshP3();
    }
    else QMessageBox::warning(this,"Lỗi",QString::fromUtf8("Thêm không thành công !!"));

}
