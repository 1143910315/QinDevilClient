#ifndef DEVICECONTEXT_H
#define DEVICECONTEXT_H

#include <QColor>
#include <QObject>
#include <QRect>
#include <QVector>

class DeviceContext : public QObject {
    Q_OBJECT
public:
    explicit DeviceContext(QObject *parent = nullptr);
    ~DeviceContext();
    bool GetDeviceContext(unsigned int hwnd);
    bool CacheRegion(const QRect &rect);
    QColor GetPointColor(int x, int y);
private:
    unsigned int handleDeviceContext = 0;
    unsigned int handleWindow = 0;
    unsigned int handleCompatibleDeviceContext = 0;
    QRect cacheRect = QRect();
    QVector<QColor> colors;
signals:

};

#endif // DEVICECONTEXT_H
