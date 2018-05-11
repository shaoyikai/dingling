#include "login.h"
#include "ui_login.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"
#include "QFile"
#include "QIODevice"
#include "QTextStream"

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

    if(account.length() < 6 || password.length() < 8){
        QMessageBox::critical(this,"错误","信息填写不完整，请重新检查","确定");
    }else{
        QString cnt = account + " " + password + "\n";
        writeToDb(account,password);
    }
}

void Login::on_btn_clear_clicked()
{
    ui->le_account->setText("");
    ui->le_password->setText("");
    this->ui->le_account->setFocus();
    Login::readFromDb();
}

void Login::writeToDb(QString account,QString password)
{
    QSqlQuery query;
    QString insert_sql = "INSERT INTO user(account,password) VALUES('" + account + "','" + password + "')";
    if(!query.exec(insert_sql)){
        qWarning() << "Login::writeToDb - ERROR: " << query.lastError().text();
    }
}

void Login::readFromDb()
{
    QSqlQuery query;
    QString select_sql = "SELECT * FROM user";
    if(!query.exec(select_sql)) {
        qWarning() << "Login::readFromDb - ERROR: " << query.lastError().text();
    } else {
        while(query.next()) {
            QString account = query.value(1).toString();
            QString password = query.value(2).toString();
            qDebug()<<QString("account:%1    password:%2").arg(account).arg(password);
        }
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





