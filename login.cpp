#include "login.h"
#include "ui_login.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"
#include "QFile"
#include "QIODevice"
#include "QTextStream"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    // -- DATABASE INIT --
    DatabaseConnect();
    DatabaseInit();
    DatabasePopulate();
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
        writeToFile(cnt);
    }
}

void Login::on_btn_clear_clicked()
{
    ui->le_account->setText("");
    ui->le_password->setText("");
    this->ui->le_account->setFocus();
}

void Login::writeToFile(QString cnt)
{
    QFile file("./aaaaa.txt");
    if(!file.open(QIODevice::Append | QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息未保存！","确认");
        return;
    }

    QTextStream out(&file);
    out << cnt;
    file.close();
}


void Login::DatabaseConnect()
{
    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

        db.setDatabaseName("memory.db");

        if(!db.open())
            qWarning() << "MainWindow::DatabaseConnect - ERROR: " << db.lastError().text();
    }
    else
        qWarning() << "MainWindow::DatabaseConnect - ERROR: no driver " << DRIVER << " available";

}

void Login::DatabaseInit()
{
    QSqlQuery query("CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT)");

    if(!query.isActive())
        qWarning() << "Login::DatabaseInit - ERROR: " << query.lastError().text();

}

void Login::DatabasePopulate()
{
    QSqlQuery query;

    if(!query.exec("INSERT INTO people(name) VALUES('Eddie Guerrero')"))
        qWarning() << "Login::DatabasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Gordon Ramsay')"))
        qWarning() << "Login::DatabasePopulate - ERROR: " << query.lastError().text();
}






