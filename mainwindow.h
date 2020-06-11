#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpsocket.h"
QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected slots:
    void connected();
    void receive(int signal, char *data, int count);
    void version(int v);
    void error(QAbstractSocket::SocketError socketError);
    void disconnected();
private:
    Ui::MainWindow *ui;
    BufferList bufferList;
    TcpSocket *client;
};
#endif // MAINWINDOW_H
