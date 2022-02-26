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
    bool GetDeviceContext(void *hwnd);
    bool CacheRegion(const QRect &rect);
    QColor GetPointColor(int x, int y);
private:
    void *handleDeviceContext = 0;
    void *handleWindow = 0;
    void *handleCompatibleDeviceContext = 0;
    QRect cacheRect = QRect();
    QVector<QColor> colors;
signals:
};
#endif // DEVICECONTEXT_H
