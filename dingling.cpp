#include "dingling.h"
#include "ui_dingling.h"

DingLing::DingLing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DingLing)
{
    ui->setupUi(this);
}

DingLing::~DingLing()
{
    delete ui;
}
