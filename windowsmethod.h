#ifndef WINDOWSMETHOD_H
#define WINDOWSMETHOD_H
#include <QObject>
#include <QRect>
class windowsMethod : public QObject {
    Q_OBJECT
public:
    explicit windowsMethod(QObject *parent = nullptr);
    static long a();
    static void *GetWuXiaProcess();
    static QRect GetWinRect(void *windowHandle);
    static bool ClientPointToScreen(void *windowHandle, QPoint &p);
    static void KeybdEvent(unsigned char keyId, int keyState);
signals:
};
#endif // WINDOWSMETHOD_H
