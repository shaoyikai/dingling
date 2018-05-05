#ifndef DINGLING_H
#define DINGLING_H

#include <QDialog>

namespace Ui {
class DingLing;
}

class DingLing : public QDialog
{
    Q_OBJECT

public:
    explicit DingLing(QWidget *parent = 0);
    ~DingLing();

private:
    Ui::DingLing *ui;
};

#endif // DINGLING_H
