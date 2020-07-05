#ifndef DOUBLECLICKLINEEDIT_H
#define DOUBLECLICKLINEEDIT_H

#include <QLineEdit>

class DoubleClickLineEdit : public QLineEdit {
    Q_OBJECT
public:
    explicit DoubleClickLineEdit(QWidget *parent = nullptr);
    explicit DoubleClickLineEdit(const QString &contents, QWidget *parent = nullptr);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
signals:
    void mouseDoubleClick();
};

#endif // DOUBLECLICKLINEEDIT_H
