#include "login.h"
#include <QApplication>
#include "mainwindow.h"
#include "QDebug"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mw;
    Login login;

    int is_test = true; // true:调试模式 或者 false:正常模式

    if(is_test){
        mw.show();
    }else{
        if(login.exec() == QDialog::Accepted){
            qDebug() << "abc";
            mw.show();
        }
    }

    return a.exec();
}
