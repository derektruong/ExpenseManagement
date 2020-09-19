#ifndef CHITIEU_H
#define CHITIEU_H

#include <QDialog>
#include <quanlytaikhoan.h>
#include <expensetracker.h>
#include <quanlychitieu.h>


#include <QString>
#include <QStack>
#include <QVector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>

typedef long long int lli;

namespace Ui {
class ChiTieu;
}

class ChiTieu : public QDialog
{
    Q_OBJECT

public:
    explicit ChiTieu(QString DanhMuc="", QString username="",QWidget *parent = nullptr);
    ~ChiTieu();

    friend class ExpenseTracker;

protected:
    QString Username;
    QString DanhMuc;

private slots:
    void on_btn_OK_clicked();

    void on_btn_Huy_clicked();

private:
    Ui::ChiTieu *ui;
    QuanLyTaiKhoan TaiKhoanQL;
    QuanLyChiTieu DanhMucQL;
};

#endif // CHITIEU_H
