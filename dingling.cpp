#include "dingling.h"
#include "ui_dingling.h"

DingLing::DingLing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DingLing)
{
    ui->setupUi(this);
}

DingLing::~DingLing()
{
    delete ui;
}
