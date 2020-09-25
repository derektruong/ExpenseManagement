#ifndef EXPENSETRACKER_H
#define EXPENSETRACKER_H

#include <QDialog>

#include <loginapp.h>
#include <changepin.h>
#include <quanlytaikhoan.h>
#include <quanlychitieu.h>
#include <quanlythunhap.h>
#include <chitieu.h>
#include <tietkiem.h>


#include <QString>
#include <QVector>
#include <QStack>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QSortFilterProxyModel>

typedef qint64 lli;

namespace Ui {
class ExpenseTracker;
}

class ExpenseTracker : public QDialog
{
    Q_OBJECT

public:
    explicit ExpenseTracker(QWidget *parent = nullptr);
    ~ExpenseTracker();

    friend class LoginAPP;

    friend class ChiTieu;

    QString FormatMoney(lli Tien);
    void FormatDate(QString& date);
    bool CheckMoneyInput(QString money);

    void UpdateTableP4();

    //void GetUserName(LoginAPP login);

protected:
    QString TenDangNhap;

private slots:
    void RefreshP1();
    void RefreshP2();
    void RefreshP3();
    void RefreshP4();

    void indexChanged(int index);

    void on_pushButton_TrangChinh_clicked();

    void on_pushButton_ChiTieu_clicked();

    void on_pushButton_ThuNhap_clicked();

    void on_pushButton_TaiKhoan_clicked();

    void on_pushButton_ThongKe_clicked();

    void on_pushButton_NguoiDung_clicked();

    void on_pushButton_minimize_clicked();

    void on_pushButton_ThayMaPin_clicked();

    void on_btn_page4_ThemTK_TX_clicked();

    void on_btn_page4_ThemTK_TK_clicked();

    void on_btn_page4_ThemTK_NO_clicked();

    void on_btn_page4_ThemSoDu_clicked();

    void on_btn_page4_XoaTaiKhoan_clicked();

    void on_btn_page4_CapNhat_XemBang_clicked();

    void on_btn_GiaDinhPic_clicked();

    void on_btn_SucKhoePic_clicked();

    void on_btn_MuaSamPic_clicked();

    void on_btn_HocPhiPic_clicked();

    void on_btn_HoaDonPic_clicked();

    void on_btn_KinhDoanhPic_clicked();

    void on_btn_KhacPic_clicked();

    void on_btn_QuaTangPic_clicked();

    void on_btn_DiChuyenPic_clicked();

    void on_btn_GiaiTriPic_clicked();

    void on_btn_BachHoaPic_clicked();

    void on_btn_Refresh_clicked();

    void on_btn_ThemTaiKhoan_clicked();

    void on_btn_p2_TimTheoNgay_clicked();

    void on_btn_p2_TimTheoThang_clicked();

    void on_btn_p2_TimTheoNam_clicked();

    void on_btn_p2_TimKiemChung_clicked();

    void on_btn_p3_XacNhan_clicked();

    void on_btn_p3_XacNhan_tab2_clicked();


private:
    Ui::ExpenseTracker *ui;

    QSqlDatabase myDB;
    QSqlQueryModel *qryModel;
    QString HoTen = "Username";
    QuanLyTaiKhoan TaiKhoanQL;
    QuanLyChiTieu DanhMucQL;
    QuanLyThuNhap ThuNhapQL;
    TietKiem TietKiemQL;
};

#endif // EXPENSETRACKER_H
