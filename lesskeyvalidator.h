#ifndef LESSKEYVALIDATOR_H
#define LESSKEYVALIDATOR_H
#include <QValidator>

class LessKeyValidator: public QValidator {
public:
    explicit LessKeyValidator(QObject *parent = nullptr);
    State validate(QString &str, int &index) const;
};

#endif // LESSKEYVALIDATOR_H
