#ifndef PASSWORD_H
#define PASSWORD_H

#include <QDialog>

namespace Ui {
    class Password;
}

class Password : public QDialog {
    Q_OBJECT

public:
    explicit Password(QWidget *parent = nullptr);
    int port = 0;
    ~Password();

private:
    Ui::Password *ui;
};

#endif // PASSWORD_H
