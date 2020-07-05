#include "dialog.h"
#include "ui_dialog.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog) {
    ui->setupUi(this);
    connect(ui->pushButton, &QAbstractButton::clicked, this, &Dialog::confirm);
}

Dialog::~Dialog() {
    delete ui;
}

QString Dialog::getName() {
    return userName;
}

void Dialog::confirm() {
    userName = ui->lineEdit->text().trimmed();
    if(userName.length() > 0) {
        //qDebug("%s", qPrintable(userName));
        done(1024);
    } else {
        ui->label->setText("请输入游戏ID：(不能输入空白)");
    }
}
