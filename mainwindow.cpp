#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\\QinDevilCommonStructure\\commonstructure.h"
constexpr auto ipHost = "127.0.0.1";
constexpr auto ipPort = 12580;
#if Power
#else
    #define PowerLevel 0
    #define Line 0
#endif
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    client = new TcpSocket(&bufferList, this);
    connect(client, &TcpSocket::connected, this, &MainWindow::connected);
    connect(client, &TcpSocket::receive, this, &MainWindow::receive);
    connect(client, &TcpSocket::version, this, &MainWindow::version);
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    connect(client, &TcpSocket::disconnected, this, &MainWindow::disconnected);
    client->connectToHost(ipHost, ipPort);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connected() {
}

void MainWindow::receive(int signal, char *data, int count) {
}

void MainWindow::version(int v) {
    if(v != Version) {
        close();
    } else {
        structure_initData d;
        d.powerLevel = PowerLevel;
        d.line = Line;
        Buffer *sendBuff = client->getSendBuffer(0, sizeof(d));
        client->writeBuffer(&sendBuff, (char *)&d, sizeof(d));
        client->sendBuffer(sendBuff);
    }
}

void MainWindow::error(QAbstractSocket::SocketError socketError) {
    (void)socketError;
    //client->connectToHost(ipHost, ipPort);
    qDebug("error:%d", socketError);
}

void MainWindow::disconnected() {
    //client->connectToHost(ipHost, ipPort);
    qDebug("disconnected");
}

