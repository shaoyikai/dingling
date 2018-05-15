#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    int validLogin(QString account,QString password);
    void writeToDb(QString account,QString password);
    // 数据库操作
    void DatabaseConnect();

private slots:
    void on_btn_submit_clicked();

    void on_btn_clear_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
