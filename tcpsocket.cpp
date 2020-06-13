#include "tcpsocket.h"

TcpSocket::TcpSocket(BufferList *bufferList, QObject *parent) : QTcpSocket(parent), bufferList(bufferList) {
    connect(this, &TcpSocket::readyRead, this, &TcpSocket::receiveData);
}

bool TcpSocket::setSocketDescriptor(qintptr socketDescriptor, QAbstractSocket::SocketState socketState, QIODevice::OpenMode openMode) {
    return QTcpSocket::setSocketDescriptor(socketDescriptor, socketState, openMode);
}

Buffer *TcpSocket::getSendBuffer(int signal, uint length) {
    uint mod = length & 0xFFFFFFF0;
    if(mod != length) {
        length = mod + 16;
    }
    Buffer *buffer = bufferList->getBuffer(length + 8);
    int *bufferPointer = (int *)buffer->buffer;
    bufferPointer[0] = 4;
    bufferPointer[1] = signal;
    return buffer;
}

void TcpSocket::writeBuffer(Buffer **buffer, int data) {
    Buffer *b = *buffer;
    int *bufferPointer = (int *)b->buffer;
    int bufferActualLength = bufferPointer[0];
    if(bufferActualLength + 4 + sizeof(data) <= b->length) {
        bufferPointer[0] = bufferActualLength + sizeof(data);
        int *wr = (int *)(b->buffer + bufferActualLength + 4);
        wr[0] = data;
    } else {
        Buffer *newb = bufferList->getBuffer(b->length + 16);
        char *newbuffer = newb->buffer;
        char *oldbuffer = b->buffer;
        for(int i = 0; i < bufferActualLength + 4; i++) {
            newbuffer[i] = oldbuffer[i];
        }
        bufferList->setBuffer(b);
        *buffer = newb;
        writeBuffer(buffer, data);
    }
}

void TcpSocket::writeBuffer(Buffer **buffer, char *data, int dataLength) {
    Buffer *b = *buffer;
    uint *bufferPointer = (uint *)b->buffer;
    uint bufferActualLength = bufferPointer[0];
    if(bufferActualLength + 4 + dataLength > b->length) {
        uint length = bufferActualLength - 4 + dataLength;
        uint mod = length & 0xFFFFFFF0;
        if(mod != length) {
            length = mod + 16;
        }
        Buffer *newb = bufferList->getBuffer(length + 8);
        char *newbuffer = newb->buffer;
        char *oldbuffer = b->buffer;
        for(uint i = 0; i < bufferActualLength + 4; i++) {
            newbuffer[i] = oldbuffer[i];
        }
        *buffer = newb;
        bufferList->setBuffer(b);
        b = newb;
        bufferPointer = (uint *)b->buffer;
    }
    bufferPointer[0] = bufferActualLength + dataLength;
    char *wr = b->buffer + bufferActualLength + 4;
    for(int i = 0; i < dataLength; i++) {
        wr[i] = data[i];
    }
}

void TcpSocket::sendBuffer(Buffer *buffer) {
    char *bufferPointer = buffer->buffer;
    int actualLength = ((int *)bufferPointer)[0];
    uint length = actualLength - 4;
    uint mod = length & 0xFFFFFFF0;
    if(mod != length) {
        length = mod + 16;
    }
    aes.code(bufferPointer + 8, length);
    write(bufferPointer, length + 8);
}

void TcpSocket::receiveData() {
    qint64 localBytesAvailable = bytesAvailable();
    while(localBytesAvailable > 0) {
        if(dataLength == 0) {
            if(localBytesAvailable >= sizeof(dataLength)) {
                localBytesAvailable -= read((char *)&effectiveDataLength, sizeof(effectiveDataLength));
                if(effectiveDataLength < 0) {
                    if(effectiveDataLength != Version) {
                        emit version(effectiveDataLength);
                    } else {
                        dataLength = VersionInfoLength;
                        buffer = bufferList->getBuffer(VersionInfoLength);
                    }
                } else {
                    effectiveDataLength = effectiveDataLength - 4;
                    int mod = effectiveDataLength & 0xFFFFFFF0;
                    if(mod != effectiveDataLength) {
                        dataLength = mod + 16 + 4;
                    } else {
                        dataLength = effectiveDataLength + 4;
                    }
                    buffer = bufferList->getBuffer(dataLength);
                }
            } else {
                break;
            }
        } else if(effectiveDataLength == Version) {
            if(localBytesAvailable >= VersionInfoLength) {
                char key[VersionInfoLength];
                localBytesAvailable -= read(key, VersionInfoLength);
                //qDebug("%u %u %u %u", ((int *)key)[0], ((int *)key)[1], ((int *)key)[2], ((int *)key)[3]);
                aes.setKey(key);
                emit version(Version);
                dataLength = 0;
            } else {
                break;
            }
        } else {
            char *localData = buffer->buffer;
            localData += buffer->length - dataLength;
            qint64 localRead = read(localData, dataLength);
            localBytesAvailable -= localRead;
            dataLength -= localRead;
            if(dataLength == 0) {
                aes.decode(buffer->buffer + 4, buffer->length - 4);
                emit receive(*((int *)buffer->buffer), buffer->buffer + 4, effectiveDataLength);
                bufferList->setBuffer(buffer);
            }
        }
    }
}
