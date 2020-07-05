#ifndef WINDOWSMETHOD_H
#define WINDOWSMETHOD_H

#include <QObject>

class windowsMethod : public QObject {
    Q_OBJECT
public:
    explicit windowsMethod(QObject *parent = nullptr);
    static long a();
    static unsigned int GetWuXiaProcess();

signals:

};

#endif // WINDOWSMETHOD_H
