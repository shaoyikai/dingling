#include "login.h"
#include "ui_login.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"

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

    if(account.length() < 6 || password.length() < 8){
        QMessageBox::critical(this,"错误","信息填写不完整，请重新检查","确定");
    }else{
        QString content = account + "\n" + password;
        QMessageBox::question(this,"请确认信息",content,"确认","取消");
    }
}

void Login::on_btn_clear_clicked()
{
    ui->le_account->setText("");
    ui->le_password->setText("");
    this->ui->le_account->setFocus();
}
