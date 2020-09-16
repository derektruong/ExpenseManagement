#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include <loginapp.h>

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    ~AddUser();

private slots:
    void on_pushButton_DangKy_AddUser_clicked();

private:
    Ui::AddUser *ui;
    LoginAPP *login;
};

#endif // ADDUSER_H
