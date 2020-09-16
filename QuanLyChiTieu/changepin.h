#ifndef CHANGEPIN_H
#define CHANGEPIN_H

#include <QDialog>

namespace Ui {
class ChangePin;
}

class ChangePin : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePin(QWidget *parent = nullptr);
    ~ChangePin();

private:
    Ui::ChangePin *ui;
};

#endif // CHANGEPIN_H
