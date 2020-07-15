#ifndef WINDOWSMETHOD_H
#define WINDOWSMETHOD_H

#include <QObject>
#include <QRect>

class windowsMethod : public QObject {
    Q_OBJECT
public:
    explicit windowsMethod(QObject *parent = nullptr);
    static long a();
    static unsigned int GetWuXiaProcess();
    static QRect GetWinRect(unsigned int windowHandle);
    static bool ClientPointToScreen(unsigned int windowHandle, QPoint &p);
    static void KeybdEvent(unsigned char keyId, int keyState);
signals:

};

#endif // WINDOWSMETHOD_H
