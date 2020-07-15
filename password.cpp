#include "password.h"
#include "ui_password.h"

Password::Password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Password) {
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, [&]() {
        bool resulte = false;
        int p = ui->lineEdit->text().toInt(&resulte);
        if(resulte) {
            this->port = p;
        }
        this->close();
    });
}

Password::~Password() {
    delete ui;
}
