#include "lesskeyvalidator.h"

LessKeyValidator::LessKeyValidator(QObject *parent): QValidator(parent) {
}

QValidator::State LessKeyValidator::validate(QString &str, int &index) const {
    (void)index;
    QChar c1, c2, c3;
    if(str.length() > 3) {
        return QValidator::State::Invalid;
    }
    if(str.length() >= 1) {
        c1 = str[0];
        if(c1 != '1' && c1 != '2' && c1 != '3' && c1 != '4' && c1 != '5') {
            return QValidator::State::Invalid;
        }
    }
    if(str.length() >= 2) {
        c2 = str[1];
        if(c2 != '1' && c2 != '2' && c2 != '3' && c2 != '4' && c2 != '5') {
            return QValidator::State::Invalid;
        }
        if(c1 == c2) {
            return QValidator::State::Invalid;
        }
    }
    if(str.length() == 3) {
        c3 = str[2];
        if(c3 != '1' && c3 != '2' && c3 != '3' && c3 != '4' && c3 != '5') {
            return QValidator::State::Invalid;
        }
        if(c1 == c3 || c2 == c3) {
            return QValidator::State::Invalid;
        }
    }
    return QValidator::State::Acceptable;
}
