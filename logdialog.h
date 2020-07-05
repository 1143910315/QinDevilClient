#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>
#include <QVector>
namespace Ui {
    class LogDialog;
}

class LogDialog : public QDialog {
    Q_OBJECT

public:
    explicit LogDialog(const QVector<QString> *log, QWidget *parent = nullptr);
    ~LogDialog();

private:
    Ui::LogDialog *ui;
    const QVector<QString> *log;
    int current = 0;
    void showLog();
};

#endif // LOGDIALOG_H
