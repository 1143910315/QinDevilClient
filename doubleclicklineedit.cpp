#include "doubleclicklineedit.h"

DoubleClickLineEdit::DoubleClickLineEdit(QWidget *parent) : QLineEdit(parent) {
}

DoubleClickLineEdit::DoubleClickLineEdit(const QString &contents, QWidget *parent): QLineEdit(contents, parent) {
}

void DoubleClickLineEdit::mouseDoubleClickEvent(QMouseEvent *event) {
    (void)event;
    emit mouseDoubleClick();
}
