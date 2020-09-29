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
    this->setWindowIcon(QIcon(":/Images\\Icon\\cash-icon.png"));

    // Hiển thị trang chủ đầu tiên khi truy cập phần mềm

    ui->stackedWidget->setCurrentIndex(0);

    ui->pushButton_TrangChinh->animateClick(10);

    // Đặt title
    this->setWindowTitle(QString::fromUtf8("Quản lý chi tiêu"));

    // Đặt ngày dateEdit về ngày hiện tại

    QDate crrDate = QDate::currentDate();

    ui->dateEdit_p3_NgayThuNhap->setDate(crrDate);

    ui->dateEdit_p3_KyHan_NO->setDate(crrDate);
    ui->dateEdit_p5_ThangThuChi_tab1->setDate(crrDate);
    ui->dateEdit_P5_ThoiGian_tab2->setDate(crrDate);
    ui->dateEdit_P5_ThoiGian_tab3->setDate(crrDate);

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
    if( Tien < 0 && res[1] == '.') res.replace(1,1,"");
    //qDebug()<<res;

    return  res;
}


bool ExpenseTracker::CheckMoneyInput(QString money){
    for ( int i = 0; i < money.size(); ++i) {
        if(money[0].unicode() - 48 < 0) {
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số liệu nhập không hợp lệ!"));
            return false;
        }
        if( money[i] < 48 || money[i] > 57 ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Số liệu nhập không hợp lệ chỉ gồm các chữ số"));
            return false;
        }
    }
    return true;
}
//Slot tab1 P5
void ExpenseTracker::SetToolTipThuNhap(bool status,int index){
    if( status )
        QToolTip::showText(QCursor::pos(), FormatMoney( Thu[index+1]) + "đ",nullptr,QRect(),3000);
}

void ExpenseTracker::SetToolTipChiTieu(bool status,int index){
    if( status )

        QToolTip::showText(QCursor::pos(), FormatMoney(Chi[index+1]) + "đ");
}

void ExpenseTracker::SetToolTipCanDoi(int index){
    ui->label_P5_CanDoi_tab1->setText("Cân đối: " + FormatMoney(CanDoi[index+1]) + "đ");
    ui->label_P5_CanDoi_tab1->setStyleSheet("font-weight: bold; font: 75 18pt Segoe UI Black; color: #495d63;");
    ui->label_P5_CanDoi_tab1->setAlignment(Qt::AlignCenter);

    if( CanDoi[index+1] < 0 ){
        QMessageBox::information(this,"Thông báo",QString::fromUtf8("Vào thời điểm này thu nhập của bạn thấp hơn chi tiêu. Hãy lập kế hoạch tiết kiệm ngay nhé!!"));
    }
}

//done
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
    qryModel->setQuery("SELECT Loai, Ten, format(SoDu, 'N0' ) ,MoTa FROM TaiKhoan WHERE TenChu = '"+TenDangNhap+"'");
    //Chỉnh độ rộng
    ui->tableView_page4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_page4->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //Chỉnh tên cho cột
    qryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Loại"));
    qryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Tên"));
    qryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Số dư (VNĐ)"));
    qryModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Mô tả"));

    ui->tableView_page4->setModel(qryModel);
    ui->tableView_page4->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->tableView_page4->update();

    //delete qryModel;
}

void ExpenseTracker::indexChanged(int index){
    for (int i = 0; i < 3; ++i) {
        if( i == index ){
            ui->tabWidget_3->setTabEnabled(i, true);
            ui->tabWidget_3->setCurrentIndex(index);
            continue;
        }
        ui->tabWidget_3->setTabEnabled(i, false);
    }
}


void ExpenseTracker::on_pushButton_TrangChinh_clicked()
{
    // Làm mới trang chủ
    ui->stackedWidget->setCurrentIndex(0);
    ui->comboBox->clear();

    ui->pushButton_ChiTieu->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_ThuNhap->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_TaiKhoan->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_ThongKe->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_NguoiDung->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
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
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
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

    ui->pushButton_ChiTieu->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: rgb(48, 165, 255); font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_ThuNhap->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_TaiKhoan->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_ThongKe->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_NguoiDung->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");



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

    ui->pushButton_ThuNhap->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: rgb(48, 165, 255); font: 75 15pt 'MS Shell Dlg 2';");

    ui->pushButton_ChiTieu->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_TaiKhoan->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_ThongKe->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_NguoiDung->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");

    ui->comboBox_p3_DenTaiKhoan_tab1->clear();
    ui->comboBox_p3_LoaiThuNhap_tab1->clear();
    ui->comboBox_p3_LoaiThuNhap_tab3->clear();

    //ui->tabWidget_P3->setCurrentIndex(0);

    QVector<QString> DSTenTatCaTK = TaiKhoanQL.LayTenTatCaTaiKhoan(TenDangNhap);
    QVector<QString> DSLoaiThuNhap = ThuNhapQL.LayTenThuNhap(TenDangNhap);

    if( ui->tab1_P3->isActiveWindow() ){
        //Thêm vào combobox TK
        if( !DSTenTatCaTK.size() ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có tài khoản nào!!"));
        }

        for ( int i = 0; i < DSTenTatCaTK.size(); ++i) {
            ui->comboBox_p3_DenTaiKhoan_tab1->addItem(DSTenTatCaTK[i]);
        }

        //Thêm vào combobox Thu Nhập
        if( !DSLoaiThuNhap.size() ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có loại thu nhập nào, vui lòng thêm thu nhập"));
        }

        for ( int i = 0; i < DSLoaiThuNhap.size(); ++i) {
            ui->comboBox_p3_LoaiThuNhap_tab1->addItem(DSLoaiThuNhap[i]);
        }

    }

    if( ui->tab3_P3->isActiveWindow() ){
        //Thêm vào combobox Thu Nhập
        if( !DSLoaiThuNhap.size() ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có loại thu nhập nào, vui lòng thêm nguồn thu nhập"));
        }

        for ( int i = 0; i < DSLoaiThuNhap.size(); ++i) {
            ui->comboBox_p3_LoaiThuNhap_tab3->addItem(DSLoaiThuNhap[i]);
        }
    }


    qryModel = new QSqlQueryModel();
    qryModel->setQuery("SELECT TOP 50 LoaiThuNhap AS N'Loại thu nhập', format(SoTien, 'N0' ) AS N'Số tiền(VNĐ)', TenTaiKhoan AS N'Đến tài khoản', NgayThuNhap AS N'Thời gian', GhiChu AS N'Ghi chú'  FROM ThuNhap WHERE TenChu = '"+TenDangNhap+"' ");
    //Chỉnh độ rộng
    ui->tableView_page3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_page3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //

    ui->tableView_page3->setModel(qryModel);
    ui->tableView_page3->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->tableView_page3->update();


}

void ExpenseTracker::on_pushButton_TaiKhoan_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

    ui->pushButton_TaiKhoan->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: rgb(48, 165, 255); font: 75 15pt 'MS Shell Dlg 2';");

    ui->pushButton_ChiTieu->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_ThuNhap->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_ThongKe->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_NguoiDung->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");


    ///Cap nhat bang page 4

    UpdateTableP4();

    //Xoá comboBox
    ui->comboBox_p4_TenTaiKhoan->clear();
    ui->comboBox_p4_TenTaiKhoan_Xoa->clear();

    //Vô hiệu hoá tabWidget
    ui->comboBox_p4_LoaiTaiKhoan->setCurrentIndex(0);
    ui->tabWidget_3->setTabEnabled(0, true);
    ui->tabWidget_3->setTabEnabled(1, false);
    ui->tabWidget_3->setTabEnabled(2, false);

    ///

    QVector<QString> DSTenTK = TaiKhoanQL.LayTenTaiKhoan(TenDangNhap);
    QVector<QString> DSTenTatCaTK = TaiKhoanQL.LayTenTatCaTaiKhoan(TenDangNhap);
    // Tiền xử lý tab thêm số dư
    if( ui->tab_2->isActiveWindow() ){
        for ( int i = 0; i < DSTenTK.size(); ++i) {
            ui->comboBox_p4_TenTaiKhoan->addItem(DSTenTK[i]);
        }
    }


    //

    // Tiền xử lý tab xoá tài khoản
    if( ui->tab_3->isActiveWindow() ){

        if( !DSTenTatCaTK.size() ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có tài khoản nào!!"));
        }

        for ( int i = 0; i < DSTenTatCaTK.size(); ++i) {
            ui->comboBox_p4_TenTaiKhoan_Xoa->addItem(DSTenTatCaTK[i]);
        }
    }

    connect(ui->comboBox_p4_LoaiTaiKhoan, SIGNAL(currentIndexChanged(int)),this, SLOT(indexChanged(int)));


    //
}

void ExpenseTracker::on_pushButton_ThongKe_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

    ui->pushButton_ThongKe->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: rgb(48, 165, 255); font: 75 15pt 'MS Shell Dlg 2';");

    ui->pushButton_ChiTieu->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_TaiKhoan->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_ThuNhap->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_NguoiDung->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");

    //
    ui->comboBox_P5_TenTaiKhoan_tab2->clear();
    ui->comboBox_P5_NguonThuNhap_tab3->clear();
    ui->comboBox_P5_DenTaiKhoan_tab3->clear();

    QVector<QString> DSTenTK = TaiKhoanQL.LayTenTaiKhoan(TenDangNhap);
    QVector<QString> DSLoaiThuNhap = ThuNhapQL.LayTenThuNhap(TenDangNhap);
    ui->comboBox_P5_TenTaiKhoan_tab2->addItem("Tất Cả");
    ui->comboBox_P5_DenTaiKhoan_tab3->addItem("Tất Cả");
    ui->comboBox_P5_NguonThuNhap_tab3->addItem("Tất Cả");

    if( ui->tab2_P5->isActiveWindow() ){
        for ( int i = 0; i < DSTenTK.size(); ++i) {
            ui->comboBox_P5_TenTaiKhoan_tab2->addItem(DSTenTK[i]);
        }
    }
    if( ui->tab3_P5->isActiveWindow() ){
        for ( int i = 0; i < DSTenTK.size(); ++i) {
            ui->comboBox_P5_DenTaiKhoan_tab3->addItem(DSTenTK[i]);
        }
        //Thêm vào combobox Thu Nhập
        if( !DSLoaiThuNhap.size() ){
            QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có loại thu nhập nào, vui lòng thêm nguồn thu nhập"));
        }

        for ( int i = 0; i < DSLoaiThuNhap.size(); ++i) {
            ui->comboBox_P5_NguonThuNhap_tab3->addItem(DSLoaiThuNhap[i]);
        }
    }



    ui->btn_P5_TheoThang_tab1->animateClick(5);
    ui->btn_P5_CapNhat_tab2->animateClick(5);
    ui->TabWidget_P5->setCurrentIndex(0);
}

void ExpenseTracker::on_pushButton_NguoiDung_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->pushButton_NguoiDung->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: rgb(48, 165, 255); font: 75 15pt 'MS Shell Dlg 2';");

    ui->pushButton_ChiTieu->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_TaiKhoan->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_ThongKe->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");
    ui->pushButton_ThuNhap->setStyleSheet("border-radius: 15px; color: rgb(255, 255, 255); background-color: #161925; font: 75 15pt 'MS Shell Dlg 2';");


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

void ExpenseTracker::on_btn_page4_ThemTK_TX_clicked()
{
    //Pre Processing

    QString LoaiTaiKhoan, TenTaiKhoan, MoTa;
    lli SoDu;
    int inTotal = 1;


    LoaiTaiKhoan = ui->comboBox_p4_LoaiTaiKhoan->currentText();
    TenTaiKhoan = ui->lineEdit_p4_TenTaiKhoan_TX->text();
    MoTa = ui->textEdit_p4_MoTa_TX->toPlainText();

    //Kiểm tra hợp lệ số dư
    if( !CheckMoneyInput(ui->lineEdit_p4_SoDu_TX->text()) ) return;

    //Kiểm tra hợp lệ nhập

    if(TenTaiKhoan == "" || !ui->lineEdit_p4_SoDu_TX->text().size() ){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Phải nhập đủ!"));
        return;
    }

    //

    SoDu = (ui->lineEdit_p4_SoDu_TX->text()).toLongLong();

    QSqlQuery qry;

    qry.prepare("INSERT INTO TaiKhoan( Loai,Ten,SoDu,BaoGomTrongTongSoDu,TenChu,MoTa )" "VALUES( :Loai, :Ten, :SoDu, :BaoGomTrongTongSoDu, :TenChu, :MoTa)");

    qry.bindValue(":Loai", LoaiTaiKhoan);
    qry.bindValue(":Ten", TenTaiKhoan);
    qry.bindValue(":SoDu", SoDu);
    qry.bindValue(":BaoGomTrongTongSoDu", inTotal);
    qry.bindValue(":TenChu", TenDangNhap);
    qry.bindValue(":MoTa", MoTa);
    if( !qry.exec() ){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Không thể thêm tài khoản hoặc tên tài khoản bị trùng!!"));
        return;
    }
    QMessageBox::information(this, QString::fromUtf8("Thông báo"), QString::fromUtf8("Bạn đã thêm tài khoản thành công!!"));

    RefreshP4();
}

void ExpenseTracker::on_btn_page4_ThemTK_TK_clicked()
{
    QString LoaiTaiKhoan, TenTaiKhoan, MoTa;
    lli SoDu = 0, MucTieu = 0;
    int inTotal = 1;

    LoaiTaiKhoan = ui->comboBox_p4_LoaiTaiKhoan->currentText();
    TenTaiKhoan = ui->lineEdit_p4_TenTaiKhoan_TK->text();
    MoTa = ui->textEdit_p4_MoTa_TK->toPlainText();

    if( !CheckMoneyInput(ui->lineEdit_p4_SoDu_TK->text()) ) return;
    if( !CheckMoneyInput(ui->lineEdit_p4_MucTieu_TK->text()) ) return;

    SoDu = ui->lineEdit_p4_SoDu_TK->text().toLongLong();
    MucTieu = ui->lineEdit_p4_MucTieu_TK->text().toLongLong();

    if(TenTaiKhoan == "" || !ui->lineEdit_p4_MucTieu_TK->text().size() ){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Phải nhập đủ!"));
        return;
    }

    //Truy vấn DB

    /// Insert bảng TaiKhoan

    QSqlQuery qry;

    qry.prepare("INSERT INTO TaiKhoan( Loai,Ten,SoDu,BaoGomTrongTongSoDu,TenChu,MoTa )" "VALUES( :Loai, :Ten, :SoDu, :BaoGomTrongTongSoDu, :TenChu, :MoTa)");

    qry.bindValue(":Loai", LoaiTaiKhoan);
    qry.bindValue(":Ten", TenTaiKhoan);
    qry.bindValue(":SoDu", SoDu);
    qry.bindValue(":BaoGomTrongTongSoDu", inTotal);
    qry.bindValue(":TenChu", TenDangNhap);
    qry.bindValue(":MoTa", MoTa);

    if( !qry.exec() ){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Không thể thêm tài khoản hoặc tên tài khoản bị trùng!!"));
        return;
    }

    /// done
    ///
    /// Insert bảng TietKiem
    int MTK = TaiKhoanQL.LayMaTaiKhoan(TenDangNhap, TenTaiKhoan);

    TietKiemQL.ThemTietKiem(TenDangNhap, TenTaiKhoan, SoDu, MucTieu, MTK);

    QMessageBox::information(this, QString::fromUtf8("Thông báo"), QString::fromUtf8("Bạn đã thêm tài khoản thành công!!"));

    RefreshP4();

    ///done

}

void ExpenseTracker::on_btn_page4_ThemTK_NO_clicked()
{
    QString LoaiTaiKhoan, TenTaiKhoan, KyHan, MoTa;
    lli TienNo;
    int inTotal = 0;

    LoaiTaiKhoan = ui->comboBox_p4_LoaiTaiKhoan->currentText();
    TenTaiKhoan = ui->lineEdit_p4_TenTaiKhoan_NO->text();
    MoTa = ui->textEdit_p4_MoTa_NO->toPlainText();

    if( !CheckMoneyInput(ui->lineEdit_p4_TienNo_NO->text()) ) return;

    TienNo = ui->lineEdit_p4_TienNo_NO->text().toLongLong();

    KyHan = ui->dateEdit_p3_KyHan_NO->date().toString("yyyy/MM/dd");

    if(TenTaiKhoan == "" || !ui->lineEdit_p4_TienNo_NO->text().size() ){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Phải nhập đủ!"));
        return;
    }

    //Truy vấn DB

    /// Insert bảng TaiKhoan

    QSqlQuery qry;

    qry.prepare("INSERT INTO TaiKhoan( Loai,Ten,SoDu,BaoGomTrongTongSoDu,TenChu,MoTa )" "VALUES( :Loai, :Ten, :SoDu, :BaoGomTrongTongSoDu, :TenChu, :MoTa)");

    qry.bindValue(":Loai", LoaiTaiKhoan);
    qry.bindValue(":Ten", TenTaiKhoan);
    qry.bindValue(":SoDu", TienNo);
    qry.bindValue(":BaoGomTrongTongSoDu", inTotal);
    qry.bindValue(":TenChu", TenDangNhap);
    qry.bindValue(":MoTa", MoTa);

    if( !qry.exec() ){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Không thể thêm tài khoản hoặc tên tài khoản bị trùng!!"));
        return;
    }

    /// done

    /// Insert bảng Loan
    int MTK = TaiKhoanQL.LayMaTaiKhoan(TenDangNhap, TenTaiKhoan);

    NoQL.ThemNo(TenDangNhap, TenTaiKhoan, TienNo, KyHan, MTK);

    ///done

    QMessageBox::information(this, QString::fromUtf8("Thông báo"), QString::fromUtf8("Bạn đã thêm tài khoản thành công!!"));

    RefreshP4();

    ///done


}

//page4_ThemSoDu
void ExpenseTracker::on_btn_page4_ThemSoDu_clicked()
{
    QString TenTaiKhoan, MoTa;
    lli SoTien;

    TenTaiKhoan = ui->comboBox_p4_TenTaiKhoan->currentText();

    MoTa = ui->textEdit_p4_MoTa_2->toPlainText();

    //Kiểm tra hợp lệ số tiền
    if( !CheckMoneyInput(ui->lineEdit_p4_SoTien->text()) ) return;

    SoTien = ui->lineEdit_p4_SoTien->text().toLongLong();

    if( SoTien < 0 ){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Nhập không hợp lệ !!"));
        return;
    }

    //Lấy mã tài khoản
    int MTK = TaiKhoanQL.LayMaTaiKhoan(TenDangNhap, TenTaiKhoan);

    // Truy vấn DB
    QSqlQuery qry;

    lli SoDuTK = TaiKhoanQL.LaySoDu(TenDangNhap,TenTaiKhoan);

    SoDuTK += SoTien;

    //Thêm trong bảng TietKiem nếu có
    if( TaiKhoanQL.LayLoaiTaiKhoan(TenDangNhap, TenTaiKhoan) == "Tiết kiệm" ){
        TietKiemQL.CapNhatSoDu(TenDangNhap, MTK, SoDuTK);
    }
    //done

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

    int MTK = TaiKhoanQL.LayMaTaiKhoan(TenDangNhap, TenTaiKhoan);

    if( TenTaiKhoan == ""){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Không có thẻ nào được chọn !!"));
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Cảnh báo", "Bạn có chắc muốn xoá tài khoản "+TenTaiKhoan+"? Mọi chi tiêu, thu nhập liên quan đến tài khoản này sẽ bị xoá vĩnh viễn!!", QMessageBox::Yes|QMessageBox::No);

    if( reply == QMessageBox::Yes ){
        QSqlQuery qry;

        //Xoá trong bảng TietKiem nếu có
        if( TaiKhoanQL.LayLoaiTaiKhoan(TenDangNhap, TenTaiKhoan) == "Tiết kiệm" ){
            TietKiemQL.XoaTietKiem(TenDangNhap, MTK);
        }
        //done
        //Xoá trong bảng Loan nếu có
        if( TaiKhoanQL.LayLoaiTaiKhoan(TenDangNhap, TenTaiKhoan) == "Nợ" ){
            NoQL.XoaNo(TenDangNhap, MTK);
        }
        //done

        //Xoá mọi thứ trong việc chi tiêu liên quan đến tài khoản này

        DanhMucQL.XoaTaiKhoanInChiTieu(TenDangNhap, TenTaiKhoan);

        //done

        //Xoá mọi thứ trong việc thu nhập liên quan đến tài khoản này
            ThuNhapQL.XoaTaiKhoanInThuNhap(TenDangNhap, TenTaiKhoan);

        //done

        // Xoá trong bảng TaiKhoan
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

void ExpenseTracker::on_btn_page4_CapNhat_XemBang_clicked()
{
    QString LoaiTaiKhoan;

    LoaiTaiKhoan = ui->comboBox_p4_LoaiTaiKhoan_XemBang->currentText();

    if( LoaiTaiKhoan == "Thường xuyên(Thẻ, tiền mặt,...)" ){
        qryModel = new QSqlQueryModel();
        qryModel->setQuery("SELECT Ten AS N'Tên thẻ', format(SoDu, 'N0' ) AS N'Số dư(VNĐ)' , MoTa AS N'Mô tả' FROM TaiKhoan WHERE TenChu = '"+TenDangNhap+"' AND Loai = N'Thường xuyên(Thẻ, tiền mặt,...)'");
        //Chỉnh độ rộng
        ui->tableView_page4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView_page4->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        ui->tableView_page4->setModel(qryModel);
        ui->tableView_page4->show();
    }

    if( LoaiTaiKhoan == "Tiết kiệm" ){
        qryModel = new QSqlQueryModel();
        qryModel->setQuery("SELECT tk1.TenTietKiem AS N'Tên tiết kiệm', format(tk1.SoDu, 'N0' ) AS N'Số dư tiết kiệm(VNĐ)', format(tk1.MucTieu, 'N0' ) AS N'Mục tiêu', tk2.MoTa AS N'Mô Tả' FROM TietKiem tk1 INNER JOIN dbo.TaiKhoan tk2 ON tk1.MaTaiKhoan = tk2.MaTaiKhoan AND tk1.TenChu = '"+TenDangNhap+"' AND tk2.TenChu = '"+TenDangNhap+"' ");
        //Chỉnh độ rộng
        ui->tableView_page4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView_page4->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        ui->tableView_page4->setModel(qryModel);
        ui->tableView_page4->show();
    }

    if( LoaiTaiKhoan == "Nợ" ){
        qryModel = new QSqlQueryModel();
        qryModel->setQuery("SELECT tk1.TenNo AS N'Tên khoản nợ', format(tk1.TienNo, 'N0' ) AS N'Tiền nợ(VNĐ)', format(tk1.KyHan,'dd/MM/yyyy') AS N'Kỳ hạn', tk2.MoTa AS N'Mô tả' FROM Loan tk1 INNER JOIN dbo.TaiKhoan tk2 ON tk1.MaTaiKhoan = tk2.MaTaiKhoan AND tk1.TenChu = '"+TenDangNhap+"' AND tk2.TenChu = '"+TenDangNhap+"' ");
        //Chỉnh độ rộng
        ui->tableView_page4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView_page4->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        ui->tableView_page4->setModel(qryModel);
        ui->tableView_page4->show();
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
    ui->pushButton_ThuNhap->animateClick(2);
    ui->tabWidget_P3->setCurrentIndex(0);
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

    qry.prepare("SELECT TOP 10  format(SoTien, 'N0' ) AS N'Số tiền(VNĐ)', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản' FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND NgayChiTieu = '"+Ngay+"' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
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
    ui->tableView_page2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
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

    qry.prepare("SELECT format(SoTien, 'N0' ) AS N'Số tiền(VNĐ)', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản' FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND Month(NgayChiTieu) = '"+Thang+"' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
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
    ui->tableView_page2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
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

    qry.prepare("SELECT TOP 10  format(SoTien, 'N0' ) AS N'Số tiền(VNĐ)', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản' FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND Year(NgayChiTieu) = '"+Nam+"' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
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
    ui->tableView_page2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
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
        qry.prepare("SELECT format(SoTien, 'N0' ) AS N'Số tiền(VNĐ)', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản'  FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND GhiChu LIKE N'%"+Key+"%' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
    }

    if( TenDanhMuc != "Tất Cả" && TenTaiKhoan == "Tất Cả" ){
        qry.prepare("SELECT TOP 15 format(SoTien, 'N0' ) AS N'Số tiền(VNĐ)', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản'  FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND MaDanhMuc = '"+MaDanhMuc+"'  AND GhiChu LIKE N'%"+Key+"%' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
    }

    if( TenDanhMuc == "Tất Cả" && TenTaiKhoan != "Tất Cả" ){
        qry.prepare("SELECT TOP 15 format(SoTien, 'N0' ) AS N'Số tiền(VNĐ)', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản'  FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND TenTaiKhoan = N'"+TenTaiKhoan+"' AND GhiChu LIKE N'%"+Key+"%' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
    }

    if( TenDanhMuc != "Tất Cả" && TenTaiKhoan != "Tất Cả" ){
        qry.prepare("SELECT TOP 15 format(SoTien, 'N0' ) AS N'Số tiền(VNĐ)', GhiChu AS N'Mô tả', format(NgayChiTieu,'dd/MM/yyyy') AS N'Thời gian', TenTaiKhoan AS N'Tên tài khoản'  FROM KhoanChi WHERE TenChu = '"+TenDangNhap+"' AND MaDanhMuc = '"+MaDanhMuc+"' AND TenTaiKhoan = N'"+TenTaiKhoan+"' AND GhiChu LIKE N'%"+Key+"%' ORDER BY Year(NgayChiTieu) DESC, Month(NgayChiTieu) DESC, Day(NgayChiTieu) DESC ");
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
    ui->tableView_page2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->tableView_page2->update();

}

//Xác nhận thêm tiền vào loại thu nhập đã có
void ExpenseTracker::on_btn_p3_XacNhan_clicked()
{
    QString LoaiThuNhap, TenTaiKhoan, NgayThuNhap, GhiChu, ThoiGianThongKe;
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

    //Cập nhật thông tin thu nhập cho bảng ThongKe
    ThoiGianThongKe = ui->dateEdit_p3_NgayThuNhap->date().toString("yyyy-MM-dd");
    ThongKeQL.CapNhatTongThu(TenDangNhap, ThoiGianThongKe, SoTien);

    //done

    //Continue..

    if( LoaiThuNhap == "" || TenTaiKhoan == "" || SoTien < 0){
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Nhập không hợp lệ !!"));
        return;
    }

    NgayThuNhap = ui->dateEdit_p3_NgayThuNhap->date().toString("yyyy/MM/dd");


    // Truy vấn DB

    QSqlQuery qry;

    //Lấy mã tài khoản
    int MTK = TaiKhoanQL.LayMaTaiKhoan(TenDangNhap, TenTaiKhoan);


    lli SoDuTK = TaiKhoanQL.LaySoDu(TenDangNhap,TenTaiKhoan);

    SoDuTK += SoTien;

    //Thêm trong bảng TietKiem nếu có
    if( TaiKhoanQL.LayLoaiTaiKhoan(TenDangNhap, TenTaiKhoan) == "Tiết kiệm" ){
        TietKiemQL.CapNhatSoDu(TenDangNhap, MTK, SoDuTK);

        if( TietKiemQL.KiemTraMucTieu(TenDangNhap, MTK) >= 0 ){
            bool check = false; //Kiểm tra nếu mục tiêu mới hợp lệ

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Chúc mừng", "Bạn đã đạt mục tiêu tiết kiệm, bạn có muốn nối dài mục tiêu không?", QMessageBox::Yes|QMessageBox::No);

            lli MucTieuMoi = 0;
            if( reply == QMessageBox::Yes ){
                QString MucTieuMoiText = QInputDialog::getText(this,"Nhập vào đây", "Mục tiêu mới: ");

                if( !CheckMoneyInput(MucTieuMoiText) ) check = true;

                MucTieuMoi = MucTieuMoiText.toLongLong();

                if( !check &&  MucTieuMoi <= SoDuTK ) check = true;


            }

            if( check ) QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn nhập không hợp lệ hoặc mục tiêu mới không lớn hơn số dư tiết kiệm!\n Mục tiêu sẽ không đổi!"));
            else TietKiemQL.CapNhatMucTieu(TenDangNhap, MTK, MucTieuMoi);

        }
    }

    //done

    //Trừ trong bảng Loan nếu có
    if( TaiKhoanQL.LayLoaiTaiKhoan(TenDangNhap, TenTaiKhoan) == "Nợ" ){
        SoDuTK -= SoTien*2;
        NoQL.CapNhatDuNo(TenDangNhap, MTK, SoDuTK);

        if( NoQL.KiemTraDuNo(TenDangNhap, MTK) <= 0 ){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Thông báo", "Bạn đã hết nợ trong "+TenTaiKhoan+", Bạn có muốn xoá khoản nợ này không?", QMessageBox::Yes|QMessageBox::No);

            if( reply == QMessageBox::Yes ){
                //Xoá trong bảng Loan nếu có
                if( TaiKhoanQL.LayLoaiTaiKhoan(TenDangNhap, TenTaiKhoan) == "Nợ" ){
                    NoQL.XoaNo(TenDangNhap, MTK);
                }
                //done

                // Xoá trong bảng TaiKhoan
                qry.prepare("DELETE FROM TaiKhoan WHERE TenChu = :Username AND TaiKhoan.Ten = :TenTaiKhoan ");

                qry.bindValue(":TenTaiKhoan", TenTaiKhoan);
                qry.bindValue(":Username", TenDangNhap);

                if( ! qry.exec() ){
                    QMessageBox::warning(this,"Lỗi",QString::fromUtf8("Xoá không thành công !!"));
                }
                //done
                return;

            }
        }
    }

    //

    /// Cộng tiền vào tài khoản
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

void ExpenseTracker::on_btn_p3_XacNhan_tab3_clicked()
{
    QString LoaiThuNhap;

    LoaiThuNhap = ui->comboBox_p3_LoaiThuNhap_tab3->currentText();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Cảnh báo", "Bạn có chắc muốn xoá loại thu nhập "+LoaiThuNhap+"? Mọi đợt thu nhập liên quan cũng sẽ bị xoá vĩnh viễn!!", QMessageBox::Yes|QMessageBox::No);

    if( reply == QMessageBox::Yes ){
        ThuNhapQL.XoaLoaiThuNhap(TenDangNhap, LoaiThuNhap);
    }

    RefreshP3();
}

void ExpenseTracker::on_btn_P5_TheoThang_tab1_clicked()
{
    QString Thang, Nam;


    Thang = ui->dateEdit_p5_ThangThuChi_tab1->date().toString("MM");
    Nam = ui->dateEdit_p5_ThangThuChi_tab1->date().toString("yyyy");

    Thu = ThongKeQL.LayDuLieuTongThuTheoTuan(TenDangNhap, Thang, Nam );
    Chi = ThongKeQL.LayDuLieuTongChiTheoTuan(TenDangNhap, Thang, Nam );
    CanDoi = ThongKeQL.LayDuLieuCanDoiTheoTuan(TenDangNhap, Thang, Nam);

    lli Max = Thu[1] , Min = Chi[1];

    for (int i = 1; i < 9; ++i) {
        if( Thu[i] > Max ) Max = Thu[i];
        if( Chi[i] < Min ) Min = Chi[i];
    }

    QBarSet *set0 = new QBarSet("Thu Nhập");
    QBarSet *set1 = new QBarSet("Chi Tiêu");

    *set0 << Thu[1] << Thu[2] << Thu[3] << Thu[4] << Thu[5] << Thu[6] << Thu[7] << Thu[8];
    *set1 << Chi[1] << Chi[2] << Chi[3] << Chi[4] << Chi[5] << Chi[6] << Chi[7] << Chi[8];

    QStackedBarSeries *series = new QStackedBarSeries();

    series->append(set0);
    series->append(set1);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Biểu đồ cân đối thu chi vào tháng "+Thang+" năm "+Nam+"");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categ;

    categ << "1 - 4" << "5 - 8" << "9 - 12" << "13 - 16" <<"17 - 20" << "21 - 24" << "25 - 28" <<"29 - 31";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();

    axisX->append(categ);
    axisX->setTitleText("Các khoảng ngày trong tháng "+Thang+"");
    chart->addAxis(axisX, Qt::AlignBottom);


    QValueAxis *axisY = new QValueAxis();

    axisY->setRange(Min + Min/4, Max + Max/4);
    axisY->setTickCount(11);
    axisY->setTitleText("Tiền thu/ chi (VNĐ)");

    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setBackgroundVisible(false);


    QChartView *chartView = new QChartView(chart);
    chartView->setParent(ui->frame_P5_tab1);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->resize(1201, 631);
    chartView->setRubberBand(QChartView::RectangleRubberBand);
    //chartView->setRubberBand(QChartView::VerticalRubberBand);

    chartView->show();

    this->setMouseTracking(true);

    connect(set0, SIGNAL(hovered(bool, int)), this, SLOT(SetToolTipThuNhap(bool, int)));
    connect(set1, SIGNAL(hovered(bool, int)), this, SLOT(SetToolTipChiTieu(bool, int)));
    connect(set0, SIGNAL(clicked(int)), this, SLOT(SetToolTipCanDoi(int)));
    connect(set1, SIGNAL(clicked(int)), this, SLOT(SetToolTipCanDoi(int)));


}



void ExpenseTracker::on_btn_P5_TheoNam_tab1_clicked()
{
    QString Nam;

    Nam = ui->dateEdit_p5_ThangThuChi_tab1->date().toString("yyyy");

    Thu = ThongKeQL.LayDuLieuTongThuTheoNam(TenDangNhap, Nam );
    Chi = ThongKeQL.LayDuLieuTongChiTheoNam(TenDangNhap, Nam );
    CanDoi = ThongKeQL.LayDuLieuCanDoiTheoNam(TenDangNhap, Nam);
    lli Max = Thu[1] , Min = Chi[1];

    for (int i = 1; i < 13; ++i) {
        if( Thu[i] > Max ) Max = Thu[i];
        if( Chi[i] < Min ) Min = Chi[i];
    }

    QBarSet *set0 = new QBarSet("Thu Nhập");
    QBarSet *set1 = new QBarSet("Chi Tiêu");

    *set0 << Thu[1] << Thu[2] << Thu[3] << Thu[4] << Thu[5] << Thu[6] << Thu[7] << Thu[8] << Thu[9] << Thu[10] << Thu[11] << Thu[12];
    *set1 << Chi[1] << Chi[2] << Chi[3] << Chi[4] << Chi[5] << Chi[6] << Chi[7] << Chi[8] << Chi[9] << Chi[10] << Chi[11] << Chi[12];



    QStackedBarSeries *series = new QStackedBarSeries();

    series->append(set0);
    series->append(set1);


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Biểu đồ cân đối chi tiêu vào năm "+Nam+"");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categ;

    categ << "Jan" << "Feb" << "Mar" << "Apr" <<"May" << "Jun" << "Jul" <<"Aug" << "Sep" << "Oct" << "Nov" <<"Dec";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();

    axisX->append(categ);
    axisX->setTitleText("Các tháng trong năm "+Nam+"");
    chart->addAxis(axisX, Qt::AlignBottom);


    QValueAxis *axisY = new QValueAxis();

    axisY->setRange(Min + Min/4, Max + Max/4);
    axisY->setTickCount(11);
    axisY->setTitleText("Tiền thu/ chi (VNĐ)");

    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setBackgroundVisible(false);


    QChartView *chartView = new QChartView(chart);
    chartView->setParent(ui->frame_P5_tab1);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->resize(1201, 631);
    chartView->setRubberBand(QChartView::RectangleRubberBand);
    //chartView->setRubberBand(QChartView::VerticalRubberBand);

    chartView->show();

    this->setMouseTracking(true);

    connect(set0, SIGNAL(hovered(bool, int)), this, SLOT(SetToolTipThuNhap(bool, int)));
    connect(set1, SIGNAL(hovered(bool, int)), this, SLOT(SetToolTipChiTieu(bool, int)));
    connect(set0, SIGNAL(clicked(int)), this, SLOT(SetToolTipCanDoi(int)));
    connect(set1, SIGNAL(clicked(int)), this, SLOT(SetToolTipCanDoi(int)));

}


void ExpenseTracker::on_btn_P5_CapNhat_tab2_clicked()
{
    QString TenDanhMuc, TenTaiKhoan, Ngay, Thang, Nam, KhoangThoiGian;

    TenDanhMuc = ui->comboBox_P5_TenDanhMuc_tab2->currentText();
    TenTaiKhoan = ui->comboBox_P5_TenTaiKhoan_tab2->currentText();
    Ngay = ui->dateEdit_P5_ThoiGian_tab2->date().toString("dd");
    Thang = ui->dateEdit_P5_ThoiGian_tab2->date().toString("MM");
    Nam = ui->dateEdit_P5_ThoiGian_tab2->date().toString("yyyy");

    KhoangThoiGian = ui->comboBox_P5_KhoangThoiGian_tab2->currentText();

    if( TenTaiKhoan == "" )
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có tài khoản nào, hãy lập tài khoảng ngay!!"));

    //
    ///Tạo đối tượng biểu đồ


    //Xử lý biểu đồ
    ///7 ngày trước
    if( KhoangThoiGian == "7 ngày trước" ){
        QVector<QVector<lli>> Chi = DanhMucQL.LayThongKe7NgayTruoc(TenDangNhap, TenDanhMuc, TenTaiKhoan, Ngay, Thang, Nam);

        lli Max = Chi[1][2];
        for (int i = 2; i < 8; ++i) {
            if( Chi[i][2] > Max ) Max = Chi[i][2];
        }

        QLineSeries *series = new QLineSeries();
        series->setName(TenDanhMuc);
        series->append(0, Chi[1][2]);
        series->append(3, Chi[2][2]);
        series->append(6, Chi[3][2]);
        series->append(9, Chi[4][2]);
        series->append(12, Chi[5][2]);
        series->append(15, Chi[6][2]);
        series->append(18, Chi[7][2]);

        QChart *chart = new QChart();
        //chart->legend()->hide();
        chart->addSeries(series);
        //chart->createDefaultAxes();

        chart->setAnimationOptions(QChart::SeriesAnimations);
        // Customize series
        QPen pen(QRgb(0xfdb157));
        pen.setWidth(5);
        series->setPen(pen);

        // Customize chart title
        QFont font;
        font.setPixelSize(20);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitle("Biểu đồ chi tiêu vào 7 ngày gần nhất");

        QStringList categ;

        for ( int i = 1; i < 8; ++i ) {
           categ << QString::number(Chi[i][0])+"/"+QString::number(Chi[i][1]);
           //qDebug()<<Chi[i][2]<<" ";
        }

        QBarCategoryAxis *axisX = new QBarCategoryAxis();

        axisX->append(categ);
        axisX->setTitleText("Các ngày trong 7 ngày trước");

        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();

        axisY->setRange(0, Max + Max/5);
        axisY->setTickCount(8);
        axisY->setTitleText("Tiền chi tiêu (VNĐ)");

        chart->addAxis(axisY, Qt::AlignLeft);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setBackgroundVisible(false);

        QChartView *chartView = new QChartView(chart);
        chartView->setParent(ui->frame_P5_tab2);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->resize(1001, 671);

        chartView->show();


    }
    ///done
    /// 30 ngày trước

    else if( KhoangThoiGian == "30 ngày trước" ){
        QVector<QVector<lli>> Chi = DanhMucQL.LayThongKe30NgayTruoc(TenDangNhap, TenDanhMuc, TenTaiKhoan, Ngay, Thang, Nam);

        lli Max = Chi[1][3];
        for (int i = 2; i < 11; ++i) {
            if( Chi[i][3] > Max ) Max = Chi[i][3];
        }

        QLineSeries *series = new QLineSeries();
        series->setName(TenDanhMuc);
        series->append(0, Chi[1][3]);
        series->append(3, Chi[2][3]);
        series->append(6, Chi[3][3]);
        series->append(9, Chi[4][3]);
        series->append(12, Chi[5][3]);
        series->append(15, Chi[6][3]);
        series->append(18, Chi[7][3]);
        series->append(21, Chi[8][3]);
        series->append(24, Chi[9][3]);
        series->append(27, Chi[10][3]);

        QChart *chart = new QChart();
        //chart->legend()->hide();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // Customize series
        QPen pen(QRgb(0xfdb157));
        pen.setWidth(5);
        series->setPen(pen);

        // Customize chart title
        QFont font;
        font.setPixelSize(20);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitle("Biểu đồ chi tiêu vào 30 ngày gần nhất");

        QStringList categ;

        for ( int i = 1; i < 11; ++i ) {
           categ << QString::number(Chi[i][0])+"-"+QString::number(Chi[i][1])+"/"+QString::number(Chi[i][2]);
        }

        QBarCategoryAxis *axisX = new QBarCategoryAxis();

        axisX->append(categ);
        axisX->setTitleText("Các ngày trong 7 ngày trước");

        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();

        axisY->setRange(0, Max + Max/5);
        axisY->setTickCount(8);
        axisY->setTitleText("Tiền chi tiêu (VNĐ)");

        chart->addAxis(axisY, Qt::AlignLeft);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setBackgroundVisible(false);

        QChartView *chartView = new QChartView(chart);
        chartView->setParent(ui->frame_P5_tab2);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->resize(1001, 671);

        chartView->show();
    }

    ///done
    else if( KhoangThoiGian == "3 tháng trước" ){
        QVector<QVector<lli>> Chi = DanhMucQL.LayThongKe3ThangTruoc(TenDangNhap, TenDanhMuc, TenTaiKhoan, Ngay, Thang, Nam);

        lli Max = Chi[1][3];
        for (int i = 2; i < 11; ++i) {
            if( Chi[i][3] > Max ) Max = Chi[i][3];
        }

        QLineSeries *series = new QLineSeries();
        series->setName(TenDanhMuc);
        series->append(0, Chi[1][3]);
        series->append(3, Chi[2][3]);
        series->append(6, Chi[3][3]);
        series->append(9, Chi[4][3]);
        series->append(12, Chi[5][3]);
        series->append(15, Chi[6][3]);
        series->append(18, Chi[7][3]);
        series->append(21, Chi[8][3]);
        series->append(24, Chi[9][3]);
        series->append(27, Chi[10][3]);

        QChart *chart = new QChart();
        //chart->legend()->hide();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // Customize series
        QPen pen(QRgb(0xfdb157));
        pen.setWidth(5);
        series->setPen(pen);

        // Customize chart title
        QFont font;
        font.setPixelSize(20);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitle("Biểu đồ chi tiêu vào quý gần nhất");

        QStringList categ;

        for ( int i = 1; i < 11; ++i ) {
           categ << QString::number(Chi[i][0])+"-"+QString::number(Chi[i][1])+"/"+QString::number(Chi[i][2]);
        }

        QBarCategoryAxis *axisX = new QBarCategoryAxis();

        axisX->append(categ);
        axisX->setTitleText("Các khoảng ngày trong tháng trước");

        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();

        axisY->setRange(0, Max + Max/5);
        axisY->setTickCount(8);
        axisY->setTitleText("Tiền chi tiêu (VNĐ)");

        chart->addAxis(axisY, Qt::AlignLeft);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setBackgroundVisible(false);

        QChartView *chartView = new QChartView(chart);
        chartView->setParent(ui->frame_P5_tab2);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->resize(1001, 671);

        chartView->show();
    }
    else if( KhoangThoiGian == "Năm này" ){
        QVector<lli> Chi = DanhMucQL.LayThongKe1Nam(TenDangNhap, TenDanhMuc, TenTaiKhoan, Nam);

        lli Max = Chi[1];
        for (int i = 2; i < 13; ++i) {
            if( Chi[i] > Max ) Max = Chi[i];
        }

        QLineSeries *series = new QLineSeries();
        series->setName(TenDanhMuc);
        series->append(0, Chi[1]);
        series->append(3, Chi[2]);
        series->append(6, Chi[3]);
        series->append(9, Chi[4]);
        series->append(12, Chi[5]);
        series->append(15, Chi[6]);
        series->append(18, Chi[7]);
        series->append(21, Chi[8]);
        series->append(24, Chi[9]);
        series->append(27, Chi[10]);
        series->append(30, Chi[11]);
        series->append(33, Chi[12]);

        QChart *chart = new QChart();
        //chart->legend()->hide();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        // Customize series
        QPen pen(QRgb(0xfdb157));
        pen.setWidth(5);
        series->setPen(pen);

        // Customize chart title
        QFont font;
        font.setPixelSize(20);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitle("Biểu đồ chi tiêu vào năm "+Nam+"");

        QStringList categ;

        categ << "Jan" << "Feb" << "Mar" << "Apr" <<"May" << "Jun" << "Jul" <<"Aug" << "Sep" << "Oct" << "Nov" <<"Dec";

        QBarCategoryAxis *axisX = new QBarCategoryAxis();

        axisX->append(categ);
        axisX->setTitleText("Các tháng trong năm "+Nam+"");

        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();

        axisY->setRange(0, Max + Max/5);
        axisY->setTickCount(8);
        axisY->setTitleText("Tiền chi tiêu (VNĐ)");

        chart->addAxis(axisY, Qt::AlignLeft);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setBackgroundVisible(false);

        QChartView *chartView = new QChartView(chart);
        chartView->setParent(ui->frame_P5_tab2);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->resize(1001, 671);

        chartView->show();
    }

}


////Cập nhật thu nhập
void ExpenseTracker::on_btn_P5_CapNhat_tab3_clicked()
{
    QString LoaiThuNhap, TenTaiKhoan, Ngay, Thang, Nam, KhoangThoiGian;

    LoaiThuNhap = ui->comboBox_P5_NguonThuNhap_tab3->currentText();
    TenTaiKhoan = ui->comboBox_P5_DenTaiKhoan_tab3->currentText();
    Ngay = ui->dateEdit_P5_ThoiGian_tab3->date().toString("dd");
    Thang = ui->dateEdit_P5_ThoiGian_tab3->date().toString("MM");
    Nam = ui->dateEdit_P5_ThoiGian_tab3->date().toString("yyyy");

    KhoangThoiGian = ui->comboBox_P5_KhoangThoiGian_tab3->currentText();

    if( TenTaiKhoan == "" )
        QMessageBox::warning(this,"Chú ý",QString::fromUtf8("Bạn chưa có tài khoản nào, hãy lập tài khoảng ngay!!"));


    //Xử lý biểu đồ
    ///7 ngày trước
    if( KhoangThoiGian == "7 ngày trước" ){
        QVector<QVector<lli>> Thu = ThuNhapQL.LayThongKe7NgayTruoc(TenDangNhap, LoaiThuNhap, TenTaiKhoan, Ngay, Thang, Nam);

        lli Max = Thu[1][2];
        for (int i = 2; i < 8; ++i) {
            if( Thu[i][2] > Max ) Max = Thu[i][2];
        }

        QLineSeries *series = new QLineSeries();
        series->setName(LoaiThuNhap);
        series->append(0, Thu[1][2]);
        series->append(3, Thu[2][2]);
        series->append(6, Thu[3][2]);
        series->append(9, Thu[4][2]);
        series->append(12, Thu[5][2]);
        series->append(15, Thu[6][2]);
        series->append(18, Thu[7][2]);

        QChart *chart = new QChart();
        //chart->legend()->hide();
        chart->addSeries(series);
        //chart->createDefaultAxes();

        chart->setAnimationOptions(QChart::SeriesAnimations);
        // Customize series
        QPen pen(QRgb(0xefca08));
        pen.setWidth(5);
        series->setPen(pen);

        // Customize chart title
        QFont font;
        font.setPixelSize(20);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitle("Biểu đồ thu nhập vào 7 ngày gần nhất");

        QStringList categ;

        for ( int i = 1; i < 8; ++i ) {
           categ << QString::number(Thu[i][0])+"/"+QString::number(Thu[i][1]);
           //qDebug()<<Chi[i][2]<<" ";
        }

        QBarCategoryAxis *axisX = new QBarCategoryAxis();

        axisX->append(categ);
        axisX->setTitleText("Các ngày trong 7 ngày trước");

        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();

        axisY->setRange(0, Max + Max/5);
        axisY->setTickCount(8);
        axisY->setTitleText("Tiền thu nhập (VNĐ)");

        chart->addAxis(axisY, Qt::AlignLeft);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setBackgroundVisible(false);

        QChartView *chartView = new QChartView(chart);
        chartView->setParent(ui->frame_P5_tab3);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->resize(1001, 671);

        chartView->show();


    }
    ///done
    /// 30 ngày trước

    else if( KhoangThoiGian == "30 ngày trước" ){
        QVector<QVector<lli>> Thu = ThuNhapQL.LayThongKe30NgayTruoc(TenDangNhap, LoaiThuNhap, TenTaiKhoan, Ngay, Thang, Nam);

        lli Max = Thu[1][3];
        for (int i = 2; i < 11; ++i) {
            if( Thu[i][3] > Max ) Max = Thu[i][3];
        }

        QLineSeries *series = new QLineSeries();
        series->setName(LoaiThuNhap);
        series->append(0, Thu[1][3]);
        series->append(3, Thu[2][3]);
        series->append(6, Thu[3][3]);
        series->append(9, Thu[4][3]);
        series->append(12, Thu[5][3]);
        series->append(15, Thu[6][3]);
        series->append(18, Thu[7][3]);
        series->append(21, Thu[8][3]);
        series->append(24, Thu[9][3]);
        series->append(27, Thu[10][3]);

        QChart *chart = new QChart();
        //chart->legend()->hide();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // Customize series
        QPen pen(QRgb(0xefca08));
        pen.setWidth(5);
        series->setPen(pen);

        // Customize chart title
        QFont font;
        font.setPixelSize(20);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitle("Biểu đồ thu nhập vào 30 ngày gần nhất");

        QStringList categ;

        for ( int i = 1; i < 11; ++i ) {
           categ << QString::number(Thu[i][0])+"-"+QString::number(Thu[i][1])+"/"+QString::number(Thu[i][2]);
        }

        QBarCategoryAxis *axisX = new QBarCategoryAxis();

        axisX->append(categ);
        axisX->setTitleText("Các khoảng ngày trong 30 ngày trước");

        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();

        axisY->setRange(0, Max + Max/5);
        axisY->setTickCount(8);
        axisY->setTitleText("Tiền thu nhập (VNĐ)");

        chart->addAxis(axisY, Qt::AlignLeft);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setBackgroundVisible(false);

        QChartView *chartView = new QChartView(chart);
        chartView->setParent(ui->frame_P5_tab3);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->resize(1001, 671);

        chartView->show();
    }

    ///done
    else if( KhoangThoiGian == "3 tháng trước" ){
        QVector<QVector<lli>> Thu = ThuNhapQL.LayThongKe3ThangTruoc(TenDangNhap, LoaiThuNhap, TenTaiKhoan, Ngay, Thang, Nam);

        lli Max = Thu[1][3];
        for (int i = 2; i < 11; ++i) {
            if( Thu[i][3] > Max ) Max = Thu[i][3];
        }

        QLineSeries *series = new QLineSeries();
        series->setName(LoaiThuNhap);
        series->append(0, Thu[1][3]);
        series->append(3, Thu[2][3]);
        series->append(6, Thu[3][3]);
        series->append(9, Thu[4][3]);
        series->append(12, Thu[5][3]);
        series->append(15, Thu[6][3]);
        series->append(18, Thu[7][3]);
        series->append(21, Thu[8][3]);
        series->append(24, Thu[9][3]);
        series->append(27, Thu[10][3]);

        QChart *chart = new QChart();
        //chart->legend()->hide();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // Customize series
        QPen pen(QRgb(0xefca08));
        pen.setWidth(5);
        series->setPen(pen);

        // Customize chart title
        QFont font;
        font.setPixelSize(20);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitle("Biểu đồ thu nhập vào quý gần nhất");

        QStringList categ;

        for ( int i = 1; i < 11; ++i ) {
           categ << QString::number(Thu[i][0])+"-"+QString::number(Thu[i][1])+"/"+QString::number(Thu[i][2]);
        }

        QBarCategoryAxis *axisX = new QBarCategoryAxis();

        axisX->append(categ);
        axisX->setTitleText("Các khoảng ngày trong quý trước");

        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();

        axisY->setRange(0, Max + Max/5);
        axisY->setTickCount(8);
        axisY->setTitleText("Tiền thu nhập (VNĐ)");

        chart->addAxis(axisY, Qt::AlignLeft);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setBackgroundVisible(false);

        QChartView *chartView = new QChartView(chart);
        chartView->setParent(ui->frame_P5_tab3);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->resize(1001, 671);

        chartView->show();
    }
    else if( KhoangThoiGian == "Năm này" ){
        QVector<lli> Thu = ThuNhapQL.LayThongKe1Nam(TenDangNhap, LoaiThuNhap, TenTaiKhoan, Nam);

        lli Max = Thu[1];
        for (int i = 2; i < 13; ++i) {
            //qDebug()<<Thu[i]<<" ";
            if( Thu[i] > Max ) Max = Thu[i];
        }

        QLineSeries *series = new QLineSeries();
        series->setName(LoaiThuNhap);
        series->append(0, Thu[1]);
        series->append(3, Thu[2]);
        series->append(6, Thu[3]);
        series->append(9, Thu[4]);
        series->append(12, Thu[5]);
        series->append(15, Thu[6]);
        series->append(18, Thu[7]);
        series->append(21, Thu[8]);
        series->append(24, Thu[9]);
        series->append(27, Thu[10]);
        series->append(30, Thu[11]);
        series->append(33, Thu[12]);

        QChart *chart = new QChart();
        //chart->legend()->hide();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        // Customize series
        QPen pen(QRgb(0xefca08));
        pen.setWidth(5);
        series->setPen(pen);

        // Customize chart title
        QFont font;
        font.setPixelSize(20);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitle("Biểu đồ thu nhập vào năm "+Nam+"");

        QStringList categ;

        categ << "Jan" << "Feb" << "Mar" << "Apr" <<"May" << "Jun" << "Jul" <<"Aug" << "Sep" << "Oct" << "Nov" <<"Dec";

        QBarCategoryAxis *axisX = new QBarCategoryAxis();

        axisX->append(categ);
        axisX->setTitleText("Các tháng trong năm "+Nam+"");

        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();

        axisY->setRange(0, Max + Max/5);
        axisY->setTickCount(8);
        axisY->setTitleText("Tiền thu nhập (VNĐ)");

        chart->addAxis(axisY, Qt::AlignLeft);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setBackgroundVisible(false);

        QChartView *chartView = new QChartView(chart);
        chartView->setParent(ui->frame_P5_tab3);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->resize(1001, 671);

        chartView->show();
    }
}
