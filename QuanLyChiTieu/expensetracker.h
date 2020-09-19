#ifndef EXPENSETRACKER_H
#define EXPENSETRACKER_H

#include <QDialog>

#include <loginapp.h>
#include <changepin.h>
#include <quanlytaikhoan.h>
#include <quanlychitieu.h>
#include <chitieu.h>


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

typedef long long int lli;

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

    //void GetUserName(LoginAPP login);

protected:
    QString TenDangNhap;

private slots:
    QString FormatMoney(lli Tien);

    void on_pushButton_TrangChinh_clicked();

    void on_pushButton_ChiTieu_clicked();

    void on_pushButton_ThuNhap_clicked();

    void on_pushButton_TaiKhoan_clicked();

    void on_pushButton_ThongKe_clicked();

    void on_pushButton_NguoiDung_clicked();

    void on_pushButton_minimize_clicked();

    void on_pushButton_fullscreen_clicked();

    void on_pushButton_restoredown_clicked();

    void on_pushButton_ThayMaPin_clicked();

    void on_btn_page4_Them_clicked();

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

private:
    Ui::ExpenseTracker *ui;

    QSqlDatabase myDB;
    QSqlQueryModel *qryModel;
    QString HoTen = "Username";
    QuanLyTaiKhoan TaiKhoanQL;
    QuanLyChiTieu DanhMucQL;
    int countMain = 0;
};

#endif // EXPENSETRACKER_H