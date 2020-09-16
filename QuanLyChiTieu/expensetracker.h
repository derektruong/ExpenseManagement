#ifndef EXPENSETRACKER_H
#define EXPENSETRACKER_H

#include <QDialog>
#include <loginapp.h>
#include <QString>

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

    //void GetUserName(LoginAPP login);

protected:
    QString TenDangNhap;

private slots:
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

private:
    Ui::ExpenseTracker *ui;
};

#endif // EXPENSETRACKER_H
