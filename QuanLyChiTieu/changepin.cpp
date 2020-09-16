#include "changepin.h"
#include "ui_changepin.h"

ChangePin::ChangePin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePin)
{
    ui->setupUi(this);
}

ChangePin::~ChangePin()
{
    delete ui;
}
