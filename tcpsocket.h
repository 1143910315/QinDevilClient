#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QTcpSocket>
#include "bufferlist.h"
#include "aes.h"
int constexpr Version = -3;
int constexpr VersionInfoLength = 16;
class TcpSocket : public QTcpSocket {
    Q_OBJECT
public:
    explicit TcpSocket(BufferList *bufferList, QObject *parent = nullptr);
    bool setSocketDescriptor(qintptr socketDescriptor, QAbstractSocket::SocketState socketState = ConnectedState, QIODevice::OpenMode openMode = ReadWrite) override;
    Buffer *getSendBuffer(int signal, uint length);
    void writeBuffer(Buffer **buffer, int data);
    void writeBuffer(Buffer **buffer, char *data, int dataLength);
    void sendBuffer(Buffer *buffer);
    qint64 time;
protected slots:
    void receiveData();
private:
    BufferList *const bufferList;
    int dataLength = 0;
    int effectiveDataLength;
    Buffer *buffer;
    AES aes;
signals:
    void receive(int signal, char *data, int count);
    void version(int v);
};

#endif // TCPSOCKET_H
