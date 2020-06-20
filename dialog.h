#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString getName();
protected slots:
    void confirm();
private:
    Ui::Dialog *ui;
    QString userName;
};

#endif // DIALOG_H
