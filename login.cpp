#include "login.h"
#include "ui_login.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"
#include "QFile"
#include "QIODevice"
#include "QTextStream"
#include "mainwindow.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    // -- DATABASE INIT --
    DatabaseConnect();
}

Login::~Login()
{
    delete ui;
}

void Login::on_btn_submit_clicked()
{
    QString account = ui->le_account->text();
    QString password = ui->le_password->text();

    if(account.length() < 4 || password.length() < 4){
        QMessageBox::information(this,"错误","信息填写不完整，请重新检查","确定");
    }else{
        // writeToDb(account,password);
        // 验证输入的账号密码是否正确
        if(validLogin(account,password)){
            // 弹出主窗口

            Login::accept();
        }else{
            QMessageBox::information(this,"错误","账号或密码错误！请重新检查","确定");
        }
    }
}

void Login::on_btn_clear_clicked()
{
    ui->le_account->setText("");
    ui->le_password->setText("");
    this->ui->le_account->setFocus();
}

int Login::validLogin(QString account,QString password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE account=:account");
    query.bindValue(":account",account);
    if(!query.exec()){
        qWarning() << "Login::validLogin - ERROR: " << query.lastError().text();
    }else{

        if(query.first()){
            QString db_password = query.value(2).toString();
            if(db_password == password){
                return true;
            }
        }
    }
    return false;
}

void Login::writeToDb(QString account,QString password)
{
    QSqlQuery query;
    QString insert_sql = "INSERT INTO user(account,password) VALUES('" + account + "','" + password + "')";
    if(!query.exec(insert_sql)){
        qWarning() << "Login::writeToDb - ERROR: " << query.lastError().text();
    }
}

void Login::DatabaseConnect()
{
    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER)){
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

        db.setDatabaseName("data.db");

        if(!db.open()){
            qWarning() << "Login::DatabaseConnect - ERROR: " << db.lastError().text();
        }
    }else{
        qWarning() << "Login::DatabaseConnect - ERROR: no driver " << DRIVER << " available";
    }

    // 创建user表
    QSqlQuery query("CREATE TABLE IF NOT EXISTS user (id INTEGER PRIMARY KEY, account TEXT, password TEXT)");
    if(!query.isActive()){
        qWarning() << "Login::DatabaseConnect - ERROR: " << query.lastError().text();
    }
}





