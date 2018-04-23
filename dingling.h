#ifndef DINGLING_H
#define DINGLING_H

#include <QMainWindow>

namespace Ui {
class DingLing;
}

class DingLing : public QMainWindow
{
    Q_OBJECT

public:
    explicit DingLing(QWidget *parent = 0);
    ~DingLing();

private:
    Ui::DingLing *ui;
};

#endif // DINGLING_H
