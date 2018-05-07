#include "login.h"
#include "ui_login.h"
#include "QString"
#include "QDebug"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btn_submit_clicked()
{
    QString account = ui->le_account->text();
    QString password = ui->le_password->text();

    qDebug() << account;
    qDebug() << password;
}

void Login::on_btn_clear_clicked()
{
    ui->le_account->setText("");
    ui->le_password->setText("");
}
