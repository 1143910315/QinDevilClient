#include "logdialog.h"
#include "ui_logdialog.h"

LogDialog::LogDialog(const QVector<QString> *log, QWidget *parent): QDialog(parent), ui(new Ui::LogDialog), log(log) {
    ui->setupUi(this);
    current = log->count() - 1;
    showLog();
    connect(ui->pushButton, &QPushButton::clicked, [ = ](bool checked) {
        Q_UNUSED(checked);
        if(current > 0) {
            current--;
        }
        showLog();
    });
    connect(ui->pushButton_2, &QPushButton::clicked, [ = ](bool checked) {
        Q_UNUSED(checked);
        if(current < log->count() - 1) {
            current++;
        }
        showLog();
    });
}

LogDialog::~LogDialog() {
    delete ui;
}

void LogDialog::showLog() {
    ui->label->setText(QString::asprintf("第%d页，共%d页", current + 1, log->count()));
    ui->plainTextEdit->setPlainText(log->at(current));
    QTextCursor t;
    t.movePosition(QTextCursor::End);
    ui->plainTextEdit->setTextCursor(t);
}
